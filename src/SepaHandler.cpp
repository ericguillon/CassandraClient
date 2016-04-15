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
#include "ProvionedOperationHandler.h"
#include "SepaHandler.h"

SepaHandler::SepaHandler()
: operationDAO(0,0)
{
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

void SepaHandler::processRejectedOperations(cassandra_exemple::OperationType operationType)
{
//    std::vector<Operation*> operations;
//    operationDAO.getRejectedOperations(operations);
//    BOOST_LOG_TRIVIAL(info) << "Sending " << operations.size() << " " << toString(operationType) <<  " rejection(s) to SAB...";
//    BOOST_FOREACH(Operation* operation, operations)
//    {
//        operationDAO.release(operation);
//    }
}

void SepaHandler::processProvisionedOperations(cassandra_exemple::OperationType operationType,
                                               CommandFactory* factory)
{
    ProvionedOperationHandler handler(factory);
    BOOST_LOG_TRIVIAL(info) << "Accounting " << toString(operationType) <<  " operations...";
    operationDAO.getOperation(operationType, cassandra_exemple::provisioned, &handler);
}
