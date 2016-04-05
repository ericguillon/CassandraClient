/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SepaHandler.cpp
 * Author: eric
 * 
 * Created on 24 mars 2016, 16:53
 */
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Event.h"
#include "Logger.h"
#include "constants.h"
#include "Operation.h"
#include "SepaHeader.h"
#include "Utils.h"
#include "Client.h"
#include "GlobalConfig.h"
#include "SepaHandler.h"

SepaHandler::SepaHandler()
: statusEvent(new StatusEvent)
, balanceEvent(new BalanceEvent)
{
    creditorAgent.type = Constants::CREDITOR_AGENT;
    creditorAgent.name = Constants::CREDITOR;
    creditorAgent.account = Constants::CREDITOR_ACCOUNT;

    debtorAgent.type = Constants::DEBTOR_AGENT;
    debtorAgent.name = Constants::DEBTOR;
    debtorAgent.account = Constants::DEBTOR_ACCOUNT;
}

SepaHandler::~SepaHandler()
{
    delete statusEvent;
    delete balanceEvent;
}

void SepaHandler::initializeEvent(Event* event, Operation* operation)
{
    event->setId(Utils::getUUId());
    event->setCreationDate(boost::posix_time::second_clock::local_time());
    event->setOperation(operation);
    event->setType(cassandra_exemple::sepa_integration);
}

void SepaHandler::initializeStatusEvent(Operation* operation)
{
    statusEvent->setOldStatus(statusEvent->getNewStatus());
    initializeEvent(statusEvent, operation);
}

void SepaHandler::initializeBalanceEvent(Operation* operation, Client* client)
{
    initializeEvent(balanceEvent, operation);
    cassandra_exemple::OperationStatus status = operation->getStatus()->getStatus();
    const Decimal& oldBalance = (status == cassandra_exemple::OperationStatus::provisioned ? client->getBalance() : client->getBalanceErp());
    balanceEvent->setOldBalance(oldBalance);
    balanceEvent->setBalanceImpact(operation->getAmount().getValue() * operation->getDirection());
}

bool SepaHandler::isOperationInserted(Operation* operation)
{
    return operationDAO.isOperationInserted(operation);
}

bool SepaHandler::checkClientAccount(Client* client, cassandra_exemple::AccountStatus validAccountStatus)
{
    cassandra_exemple::AccountStatus clientStatus = cassandra_exemple::getAccountStatus(client->getStatus());
    return (clientStatus == cassandra_exemple::opened || clientStatus == validAccountStatus );
}

bool SepaHandler::isIbanBlacklisted(const std::string& iban) const
{
    return GlobalConfig::getInstance()->isIbanBlacklisted(iban);
}

bool SepaHandler::isBicBlacklisted(const std::string& bic) const
{
    return GlobalConfig::getInstance()->isBicBlacklisted(bic);
}

bool SepaHandler::isCountryBlacklisted(const std::string& country) const
{
    return GlobalConfig::getInstance()->isCountryBlacklisted(country);
}

void SepaHandler::updateOperation(Operation* operation)
{
    BOOST_LOG_TRIVIAL(info) << "Updating operation " << operation->getTransactionId()
                            << " status " << cassandra_exemple::toString(operation->getStatus()->getStatus())
                            << " for client " << operation->getClientCompte().iban;
    operationDAO.updateOperation(operation);
    initializeStatusEvent(operation);
    eventDAO.insertEvent(statusEvent);
}

void SepaHandler::insertOperation(Operation* operation)
{
    BOOST_LOG_TRIVIAL(info) << "Inserting operation " << operation->getTransactionId()
                        << " status " << cassandra_exemple::toString(operation->getStatus()->getStatus())
                        << " for client " << operation->getClientCompte().iban;
    operationDAO.insertOperation(operation);
    initializeStatusEvent(operation);
    eventDAO.insertEvent(statusEvent);
}
    
bool SepaHandler::checkCorrespondentAccount(Operation* operation)
{
    bool result = false;
    const Compte& correspondent = operation->getCorrespondentCompte();
    if (correspondent.iban.size() < 4)
    {
        BOOST_LOG_TRIVIAL(error) << "Correspondent iban " << correspondent.iban << "is incorrect";
        rejectOperation(operation, cassandra_exemple::client_status, "iban_incorrect " + correspondent.iban);
    }
    else
    {
        if (isIbanBlacklisted(correspondent.iban))
        {
            BOOST_LOG_TRIVIAL(error) << "Correspondent iban " << correspondent.iban << "is blacklisted";
            rejectOperation(operation, cassandra_exemple::client_status, "iban_blacklisted " + correspondent.iban);
        }
        else
        {
            if (isBicBlacklisted(correspondent.bic))
            {
                BOOST_LOG_TRIVIAL(error) << "Correspondent bic " << correspondent.bic << "is blacklisted";
                rejectOperation(operation, cassandra_exemple::client_status, "bic_blacklisted " + correspondent.bic);
            }
            else
            {
                if (isCountryBlacklisted(correspondent.country))
                {
                    BOOST_LOG_TRIVIAL(error) << "Correspondent country " << correspondent.country << "is blacklisted";
                    rejectOperation(operation, cassandra_exemple::client_status, "country_blacklisted " + correspondent.country);
                }
                else
                {
                    result = true;
                }
            }
        }
    }
    return result;
}



void SepaHandler::rejectOperation(Operation* operation, cassandra_exemple::RejectionCode code, const std::string& cause)
{
    OperationStatus* rejectedStatus = initializeRejectedStatus(code, cause);
    operation->setStatus(rejectedStatus);
}

OperationStatus* SepaHandler::initializeRejectedStatus(cassandra_exemple::RejectionCode code, const std::string& cause)
{
    RejectedStatus* rejectedStatus = static_cast<RejectedStatus*>(getOperationStatus(cassandra_exemple::rejected));
    rejectedStatus->setCode(code);
    rejectedStatus->setCause(cause);
    rejectedStatus->setFpeRejected(true);
    rejectedStatus->setSabRejected(false);
    rejectedStatus->setNotifySab(true);
    return rejectedStatus;
}

Operation* SepaHandler::getOperation()
{
    return operationDAO.get();
}

OperationStatus* SepaHandler::getOperationStatus(cassandra_exemple::OperationStatus operationStatus) const
{
    return operationDAO.getOperationStatus(operationStatus);
}

void SepaHandler::releaseOperation(Operation* operation)
{
    operationDAO.release(operation);
}

void SepaHandler::decodeField(char*& field, XmlNode* node)
{
    field = node->value();
}

void SepaHandler::decodeField(std::string& field, XmlNode* node)
{
    field = node->value();
}
    
void SepaHandler::decodeField(boost::posix_time::ptime& dateField, XmlNode* node)
{
    std::string value(node->value());
    if (node->value_size() == Constants::DATE_STRING_FORMAT_SIZE)
    {
        value += "T00:00:00";
    }
    dateField = boost::date_time::parse_delimited_time<boost::posix_time::ptime>(value, 'T');
}

SepaHeader* SepaHandler::buildHeader(XmlNode* headerNode)
{
    SepaHeader* sepaHeader = new SepaHeader();
    if (XmlNode* creationDateNode = headerNode->first_node(Constants::CREATION_DATE))
    {
        decodeField(sepaHeader->creationDate, creationDateNode);
    }
    else
    {
        sepaHeader->creationDate = boost::posix_time::second_clock::local_time();
    }
    
    if (XmlNode* settlementDateNode = headerNode->first_node(Constants::INTERBANK_SETTLEMENT_DATE))
    {
        decodeField(sepaHeader->settlementDate, settlementDateNode);
    }
    else
    {
        sepaHeader->settlementDate = boost::posix_time::second_clock::local_time();
    }
    
    if (XmlNode* messageIdNode = headerNode->first_node(Constants::MESSAGE_ID))
    {
        decodeField(sepaHeader->messageId, messageIdNode);
    }
    return sepaHeader;
}
    
void SepaHandler::fillCompte(Compte& compte, const Agent& agent, XmlNode* node)
{
    if (XmlNode* agentTypeNode = node->first_node(agent.type))
    {
        if (XmlNode* financialInstitutionNode = agentTypeNode->first_node(Constants::FINANCIAL_INSTITUTION_ID))
        {
            if (XmlNode* bicNode = financialInstitutionNode->first_node(Constants::BIC))
            {
                decodeField(compte.bic, bicNode);
            }
        }
    }

    if (XmlNode* agentAccountNode = node->first_node(agent.account))
    {
        if (XmlNode* idNode = agentAccountNode->first_node(Constants::ID))
        {
            if (XmlNode* ibanNode = idNode->first_node(Constants::IBAN))
            {
                decodeField(compte.iban, ibanNode);
            }
        }
    }
}

void SepaHandler::fillIds(Operation* operation, XmlNode* node)
{
    if (XmlNode* paymentIdenticationNode = node->first_node(Constants::PAYMENT_ID))
    {
        if (XmlNode* node = paymentIdenticationNode->first_node(Constants::TRANSACTION_ID))
        {
            std::string transactionId;
            decodeField(transactionId, node);
            operation->setTransactionId(transactionId);
        }
    }
}

void SepaHandler::processRejectedOperations(cassandra_exemple::OperationType operationType)
{
    std::vector<Operation*> operations;
    operationDAO.getRejectedOperations(operations);
    BOOST_LOG_TRIVIAL(info) << "Sending " << operations.size() << " " << toString(operationType) <<  " rejection(s) to SAB...";
    BOOST_FOREACH(Operation* operation, operations)
    {
        operationDAO.release(operation);
    }
}

void SepaHandler::processProvisionedOperations(cassandra_exemple::OperationType operationType)
{
    std::vector<Operation*> operations;
    operationDAO.getOperation(operationType, cassandra_exemple::provisioned, operations);
    BOOST_LOG_TRIVIAL(info) << "Accounting " << operations.size() << " " << toString(operationType) <<  " operation(s)...";
    BOOST_FOREACH(Operation* operation, operations)
    {
        Client* client = clientDAO.getClient(operation->getClientCompte().iban);
        const Decimal& fee = operation->getFee();
        Decimal amount = operation->getAmount() * operation->getDirection();
        if (fee.isSet())
        {
            amount -= fee;
        }
        client->updateBalanceErp(amount);
        if (clientDAO.updateClientBalanceErp(client))
        {
            operation->setStatus(getOperationStatus(cassandra_exemple::accounted));
            updateOperation(operation);
            initializeBalanceEvent(operation, client);
            eventDAO.insertBalanceErpEvent(balanceEvent);
        }
        clientDAO.release(client);
        operationDAO.release(operation);
    }
}
