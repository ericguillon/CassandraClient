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
#include "enums.h"


struct SepaHeader;
typedef rapidxml::xml_node<>    XmlNode;

class Operation;
class Client;
class Event;
class StatusEvent;
class BalanceEvent;

struct Compte;
class CommandFactory;

class SepaHandler
{
protected:
    SepaHandler();
    void decodeField(char*& field, XmlNode* node);
    void decodeField(std::string& field, XmlNode* node);
    void decodeField(boost::posix_time::ptime& dateField, XmlNode* node);
    SepaHeader* buildHeader(XmlNode* headerNode);

    void processRejectedOperations(cassandra_exemple::OperationType operationType);
    void processProvisionedOperations(cassandra_exemple::OperationType operationType,
                                      CommandFactory* factory);
protected:
    OperationDAO operationDAO;
};

#endif /* SEPAHANDLER_H */

