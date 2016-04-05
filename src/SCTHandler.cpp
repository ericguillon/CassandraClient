/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTHandler.cpp
 * Author: eric
 * 
 * Created on 24 mars 2016, 16:13
 */
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>
#include "constants.h"
#include "Logger.h"
#include "SepaHeader.h"
#include "enums.h"
#include "Operation.h"
#include "OperationStatus.h"
#include "Event.h"
#include "SCTHandler.h"
#include "Client.h"

SCTHandler::SCTHandler()
{
}

SCTHandler::SCTHandler(const SCTHandler& orig)
{
}

SCTHandler::~SCTHandler()
{
}

Operation* SCTHandler::buildOperation(XmlNode* receivedTransferNode)
{
    Operation* operation = getOperation();
    operation->setCanal(cassandra_exemple::OperationCanal::sepa);
    operation->setSubCanal(cassandra_exemple::OperationSubCanal::sepa_received_transfer);
    operation->setType(cassandra_exemple::OperationType::sepa_received_transfer_operation);
    operation->setStatus(getOperationStatus(cassandra_exemple::OperationStatus::reserved));
    operation->setDirection(cassandra_exemple::OperationDirection::credit);
    operation->setInsertionDate(boost::posix_time::second_clock::local_time());
    fillCompte(operation->getClientCompte(), creditorAgent, receivedTransferNode);
    fillCompte(operation->getCorrespondentCompte(), debtorAgent, receivedTransferNode);
    fillIds(operation, receivedTransferNode);
    if (XmlNode* node = receivedTransferNode->first_node(Constants::INTERBANK_SETTLEMENT_AMOUNT))
    {
        char* amount;
        decodeField(amount, node);
        Decimal localAmount(atof(amount));
        operation->setAmount(localAmount);
        operation->setFee(Decimal(-0.0));
        operation->setAuthorizedAmount(operation->getAmount() + operation->getFee());
    }
    return operation;
}
    
void SCTHandler::onDocCreated(const rapidxml::xml_document<>& document)
{
    if (XmlNode* documentNode = document.first_node(Constants::XML_DOCUMENT))
    {
        if (XmlNode* node = documentNode->first_node(Constants::FI_TO_FI_CUSTOMER_CREDIT_TRANSFER))
        {
            XmlNode* headerNode = node->first_node(Constants::HEADER);
            SepaHeader* sepaHeader = buildHeader(headerNode);
            BOOST_LOG_TRIVIAL(info) << "Sepa header created ";
            BOOST_LOG_TRIVIAL(info) << "Creation date " << boost::posix_time::to_iso_extended_string(sepaHeader->creationDate);
            BOOST_LOG_TRIVIAL(info) << "Settlement date " << boost::posix_time::to_iso_extended_string(sepaHeader->settlementDate);
            
            XmlNode* siblingNode = node->next_sibling(Constants::CREDIT_TRANSFER_TRANSACTION_INFORMATION);
            
            XmlNode* receivedTransferNode = node->first_node(Constants::CREDIT_TRANSFER_TRANSACTION_INFORMATION);
            int nbOperation = 0;
            while (receivedTransferNode)
            {
                Operation* operation = buildOperation(receivedTransferNode);
                operation->setMessageId(sepaHeader->messageId);
                operation->setSettlementDate(sepaHeader->settlementDate);
                ++nbOperation;
                processOperation(operation);
                releaseOperation(operation);
                receivedTransferNode = receivedTransferNode->next_sibling(Constants::CREDIT_TRANSFER_TRANSACTION_INFORMATION);
            }
            
            BOOST_LOG_TRIVIAL(info) << "Processed " << nbOperation << " received transfer operations";
            delete sepaHeader;
        }
        else
        {
            BOOST_LOG_TRIVIAL(error) << "Cannot retrieve node " << Constants::FI_TO_FI_CUSTOMER_CREDIT_TRANSFER;
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Cannot retrieve node " << Constants::XML_DOCUMENT;
    }
}

void SCTHandler::processOperation(Operation* operation)
{
    BOOST_LOG_TRIVIAL(info) << "Processing operation " << operation->getTransactionId() << "...";
    OperationStatus* oldOperationStatus = operation->getStatus();
    bool operationInserted = isOperationInserted(operation);
    if (!operationInserted)
    {
        insertOperation(operation);
    }
    const Compte& clientCompte = operation->getClientCompte();
    if (Client* client = clientDAO.getClient(clientCompte.iban))
    {
        if (checkClientAccount(client, cassandra_exemple::debitBlocked))
        {
            checkCorrespondentAccount(operation);
        }
        else
        {
            rejectOperation(operation, cassandra_exemple::client_status, client->getStatus() + " " + clientCompte.iban);
        }
    }
    else
    {
        rejectOperation(operation, cassandra_exemple::client_status, "Unknown account " + clientCompte.iban);
    }
    
    if (operation->getStatus()->getStatus() == cassandra_exemple::rejected)
    {
        updateOperation(operation);
    }
}

void SCTHandler::processOnHoldOperations()
{
//    std::vector<cassandra_exemple::OperationStatus> statuses {cassandra_exemple::reserved, cassandra_exemple::onHold};
    std::vector<cassandra_exemple::OperationStatus> statuses;
    statuses.push_back(cassandra_exemple::reserved);
    statuses.push_back(cassandra_exemple::onHold);
    BOOST_FOREACH(cassandra_exemple::OperationStatus status, statuses)
    {
        std::vector<Operation*> operations;
        operationDAO.getOperation(cassandra_exemple::sepa_received_transfer_operation, status, operations);
        BOOST_LOG_TRIVIAL(info) << "Processing " << operations.size() << " " << cassandra_exemple::toString(status) << " operations..." ;
        BOOST_FOREACH(Operation* operation, operations)
        {
            const Compte& clientCompte = operation->getClientCompte();
            Client* client = clientDAO.getClient(clientCompte.iban);
            if (client)
            {
                if (checkClientAccount(client, cassandra_exemple::debitBlocked))
                {
                    if (client->getBalanceLimit().isSet())
                    {
                        if (client->getBalance() + operation->getAmount() - operation->getFee() > client->getBalanceLimit())
                        {
                            rejectOperation(operation, cassandra_exemple::limit_reached, "Client balance reached");
                        }
                    }
                    if (operation->getStatus()->getStatus() != cassandra_exemple::rejected)
                    {
                        checkCorrespondentAccount(operation);
                    }
                }
                else
                {
                    rejectOperation(operation, cassandra_exemple::client_status, client->getStatus() + " " + clientCompte.iban);
                }
            }
            else
            {
                rejectOperation(operation, cassandra_exemple::client_status, "Unknown account " + clientCompte.iban);
            }
            
            if (operation->getStatus()->getStatus() != cassandra_exemple::rejected)
            {
                BOOST_LOG_TRIVIAL(info) << "Acknowledging operation " <<  cassandra_exemple::toString(operation->getType())
                                        << " id " << operation->getId()
                                        << " transaction id" << operation->getTransactionId()
                                        << " status " << cassandra_exemple::toString(operation->getStatus()->getStatus())
                                        << " for client " << client->getIban();
                const Decimal& fee = operation->getFee();
                Decimal amount = operation->getAmount() * operation->getDirection();
                if (fee.isSet())
                {
                    amount -= fee;
                }
                client->updateBalance(amount);
                if (clientDAO.updateClientBalance(client))
                {
                    operation->setStatus(getOperationStatus(cassandra_exemple::provisioned));
                    updateOperation(operation);
                    initializeBalanceEvent(operation, client);
                    eventDAO.insertBalanceEvent(balanceEvent);
                }
            }
            operationDAO.release(operation);
        }
    }
}

void SCTHandler::processRejectedOperations()
{
    processRejectedOperations(cassandra_exemple::sepa_received_transfer_operation);
}

void SCTHandler::processProvisionedOperations()
{
    processProvisionedOperations(cassandra_exemple::sepa_received_transfer_operation);
}
