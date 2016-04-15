#ifndef COMMANDIMPL_H
#define COMMANDIMPL_H

#include "OperationDAO.h"
#include "EventDAO.h"
#include "ClientDAO.h"
#include "enums.h"

class OperationFactory;
class OperationStatusFactory;

class CommandImpl
{
protected:
    CommandImpl(OperationFactory* factory, OperationStatusFactory* statusFactory);
    ~CommandImpl();

    bool isOperationInserted(Operation* operation);

    void initializeEvent(Event* event, Operation* operation);
    void initializeStatusEvent(Operation* operation);
    void initializeBalanceEvent(Operation* operation, Client* client);

    bool checkClientAccount(Client* client, cassandra_exemple::AccountStatus validAccountStatus);
    bool checkCorrespondentAccount(Operation* operation);
    bool isIbanBlacklisted(const std::string& iban) const;
    bool isBicBlacklisted(const std::string& bic) const;
    bool isCountryBlacklisted(const std::string& country) const;

    void updateOperation(Operation* operation);
    void insertOperation(Operation* operation);

    void rejectOperation(Operation* operation, cassandra_exemple::RejectionCode code, const std::string& cause);
    OperationStatus* initializeRejectedStatus(cassandra_exemple::RejectionCode code, const std::string& cause);

protected:
    StatusEvent* statusEvent;
    BalanceEvent* balanceEvent;
    //OperationFactory* factory;
    OperationStatusFactory* statusFactory;

    OperationDAO operationDAO;
    EventDAO eventDAO;
    ClientDAO clientDAO;
};

#endif // COMMANDIMPL_H
