/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SepaHandler.h
 * Author: eric
 *
 * Created on 24 mars 2016, 16:53
 */

#ifndef SEPAHANDLER_H
#define SEPAHANDLER_H
#include <rapidxml.hpp>
#include "OperationDAO.h"
#include "EventDAO.h"
#include "enums.h"
#include "ClientDAO.h"

struct SepaHeader;
typedef rapidxml::xml_node<>    XmlNode;

class Operation;
class Client;
class Event;
class StatusEvent;
class BalanceEvent;

struct Compte;

struct Agent
{
    const char* type;
    const char* name;
    const char* account;
};

class SepaHandler
{
public:
    SepaHandler();
    ~SepaHandler();

protected:
    void decodeField(char*& field, XmlNode* node);
    void decodeField(std::string& field, XmlNode* node);
    void decodeField(boost::posix_time::ptime& dateField, XmlNode* node);
    SepaHeader* buildHeader(XmlNode* headerNode);
    Operation* getOperation();
    OperationStatus* getOperationStatus(cassandra_exemple::OperationStatus operationStatus) const;
    void releaseOperation(Operation* operation);
    void fillIds(Operation* operation, XmlNode* node);
    void fillCompte(Compte& compte, const Agent& agent, XmlNode* node);
    void initializeEvent(Event* event, Operation* operation);
    void initializeStatusEvent(Operation* operation);
    void initializeBalanceEvent(Operation* operation, Client* client);
    
    bool isOperationInserted(Operation* operation);
    bool checkClientAccount(Client* client, cassandra_exemple::AccountStatus validAccountStatus);
    bool checkCorrespondentAccount(Operation* operation);
    bool isIbanBlacklisted(const std::string& iban) const;
    bool isBicBlacklisted(const std::string& bic) const;
    bool isCountryBlacklisted(const std::string& country) const;
    
    void updateOperation(Operation* operation);
    void insertOperation(Operation* operation);

    void rejectOperation(Operation* operation, cassandra_exemple::RejectionCode code, const std::string& cause);
    OperationStatus* initializeRejectedStatus(cassandra_exemple::RejectionCode code, const std::string& cause);
    
    void processRejectedOperations(cassandra_exemple::OperationType operationType);
    void processProvisionedOperations(cassandra_exemple::OperationType operationType);
protected:
    StatusEvent* statusEvent;
    BalanceEvent* balanceEvent;
    
    Agent creditorAgent;
    Agent debtorAgent;
    
    OperationDAO operationDAO;
    EventDAO eventDAO;
    ClientDAO clientDAO;

private:
    SepaHandler(const SepaHandler& orig);
};

#endif /* SEPAHANDLER_H */

