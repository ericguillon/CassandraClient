#include "boost/date_time/posix_time/posix_time.hpp"
#include "Event.h"
#include "Logger.h"
#include "constants.h"
#include "Operation.h"
#include "OperationStatusFactory.h"
#include "SepaHeader.h"
#include "Utils.h"
#include "Client.h"
#include "GlobalConfig.h"
#include "CommandImpl.h"

CommandImpl::CommandImpl(OperationFactory* factory, OperationStatusFactory* statusFactory_)
: statusFactory(statusFactory_)
, statusEvent(new StatusEvent)
, balanceEvent(new BalanceEvent)
, operationDAO(factory, statusFactory)
{
}

CommandImpl::~CommandImpl()
{
    delete statusEvent;
    delete balanceEvent;
}

bool CommandImpl::isOperationInserted(Operation* operation)
{
    return operationDAO.isOperationInserted(operation);
}


void CommandImpl::initializeEvent(Event* event, Operation* operation)
{
    event->setId(Utils::getUUId());
    event->setCreationDate(boost::posix_time::second_clock::local_time());
    event->setOperation(operation);
    event->setType(cassandra_exemple::sepa_integration);
}

void CommandImpl::initializeStatusEvent(Operation* operation)
{
    statusEvent->setOldStatus(statusEvent->getNewStatus());
    initializeEvent(statusEvent, operation);
}

void CommandImpl::initializeBalanceEvent(Operation* operation, Client* client)
{
    initializeEvent(balanceEvent, operation);
    cassandra_exemple::OperationStatus status = operation->getStatus()->getStatus();
    const Decimal& oldBalance = (status == cassandra_exemple::OperationStatus::provisioned ? client->getBalance() : client->getBalanceErp());
    balanceEvent->setOldBalance(oldBalance);
    balanceEvent->setBalanceImpact(operation->getAmount().getValue() * operation->getDirection());
}

bool CommandImpl::checkClientAccount(Client* client, cassandra_exemple::AccountStatus validAccountStatus)
{
    cassandra_exemple::AccountStatus clientStatus = cassandra_exemple::getAccountStatus(client->getStatus());
    return (clientStatus == cassandra_exemple::opened || clientStatus == validAccountStatus );
}

bool CommandImpl::isIbanBlacklisted(const std::string& iban) const
{
    return GlobalConfig::getInstance()->isIbanBlacklisted(iban);
}

bool CommandImpl::isBicBlacklisted(const std::string& bic) const
{
    return GlobalConfig::getInstance()->isBicBlacklisted(bic);
}

bool CommandImpl::isCountryBlacklisted(const std::string& country) const
{
    return GlobalConfig::getInstance()->isCountryBlacklisted(country);
}

void CommandImpl::updateOperation(Operation* operation)
{
    BOOST_LOG_TRIVIAL(info) << "Updating operation " << operation->getTransactionId()
                            << " status " << cassandra_exemple::toString(operation->getStatus()->getStatus())
                            << " for client " << operation->getClientCompte().iban;
    operationDAO.updateOperation(operation);
    initializeStatusEvent(operation);
    eventDAO.insertEvent(statusEvent);
}

void CommandImpl::insertOperation(Operation* operation)
{
    BOOST_LOG_TRIVIAL(info) << "Inserting operation " << operation->getTransactionId()
                        << " status " << cassandra_exemple::toString(operation->getStatus()->getStatus())
                        << " for client " << operation->getClientCompte().iban;
    operationDAO.insertOperation(operation);
    initializeStatusEvent(operation);
    eventDAO.insertEvent(statusEvent);
}

bool CommandImpl::checkCorrespondentAccount(Operation* operation)
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

void CommandImpl::rejectOperation(Operation* operation, cassandra_exemple::RejectionCode code, const std::string& cause)
{
    OperationStatus* rejectedStatus = initializeRejectedStatus(code, cause);
    operation->setStatus(rejectedStatus);
}

OperationStatus* CommandImpl::initializeRejectedStatus(cassandra_exemple::RejectionCode code, const std::string& cause)
{
    RejectedStatus* rejectedStatus = static_cast<RejectedStatus*>(statusFactory->getOperationStatus(cassandra_exemple::rejected));
    rejectedStatus->setCode(code);
    rejectedStatus->setCause(cause);
    rejectedStatus->setFpeRejected(true);
    rejectedStatus->setSabRejected(false);
    rejectedStatus->setNotifySab(true);
    return rejectedStatus;
}
