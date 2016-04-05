/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseDAO.cpp
 * Author: eric
 * 
 * Created on 23 mars 2016, 11:09
 */
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Decimal.h"
#include "Logger.h"
#include "CassandraSession.h"
#include "BaseDAO.h"

BaseDAO::BaseDAO()
: session(CassandraSession::getInstance()->getSession())
{
}

BaseDAO::~BaseDAO()
{
}

CassError BaseDAO::cass_statement_bind(CassStatement* statement, std::size_t index, const char* value)
{
    return cass_statement_bind_string(statement, index, value);
}

CassError BaseDAO::cass_statement_bind(CassStatement* statement, std::size_t index, const std::string& value)
{
    return cass_statement_bind_string(statement, index, value.c_str());
}

CassError BaseDAO::cass_statement_bind(CassStatement* statement, std::size_t index, const Decimal& decimal)
{
    return cass_statement_bind_decimal(statement, index, decimal);
}

CassError BaseDAO::cass_statement_bind(CassStatement* statement, std::size_t index, CassCollection* collection)
{
    return cass_statement_bind_collection(statement, index, collection);
}

CassError BaseDAO::cass_statement_bind(CassStatement* statement, std::size_t index, const CassCollection* collection)
{
    return cass_statement_bind_collection(statement, index, collection);
}

CassError BaseDAO::cass_statement_bind(CassStatement* statement, std::size_t index, bool value)
{
    return cass_statement_bind_bool(statement, index, (value ? cass_true : cass_false));
}

CassError BaseDAO::cass_statement_bind(CassStatement* statement, std::size_t index, const boost::posix_time::ptime& date)
{
    return cass_statement_bind_int64(statement, index, boost::posix_time::to_time_t(date));
}

CassError BaseDAO::cass_collection_append(CassCollection* collection, const unsigned char* value)
{
    return cass_collection_append_string(collection, reinterpret_cast<const char*>(value));
}

CassError BaseDAO::cass_collection_append(CassCollection* collection, const char* value)
{
    return cass_collection_append_string(collection, value);
}

CassError BaseDAO::cass_collection_append(CassCollection* collection, const std::string& value)
{
    return cass_collection_append_string(collection, value.c_str());
}

CassError BaseDAO::cass_value_get_string(const CassValue* value, std::string& destination)
{
    const char* status;
    size_t status_length;
    CassError result = ::cass_value_get_string(value, &status, &status_length);
    if (result == CASS_OK)
    {
        destination = std::string(status, status_length);
    }
    return result;
}

CassError BaseDAO::cass_value_get_bool(const CassValue* value, bool& destination)
{
    cass_bool_t cassBool;
    CassError result = ::cass_value_get_bool(value, &cassBool);
    destination = cassBool == cass_true;
    return result;
}

CassError BaseDAO::cass_value_get(const CassValue* value, boost::posix_time::ptime& date)
{
    cass_int64_t timestamp;
    cass_value_get_int64(value, &timestamp);
    date = boost::posix_time::from_time_t(timestamp);
}

CassError BaseDAO::cass_value_get(const CassValue* value, cassandra_exemple::OperationCanal& canal)
{
    std::string strCanal;
    CassError result = cass_value_get(value, strCanal);
    if (result == CASS_OK)
    {
        canal = cassandra_exemple::getOperationCanal(strCanal);
    }
    return result;
}

CassError BaseDAO::cass_value_get(const CassValue* value, cassandra_exemple::OperationSubCanal& subCanal)
{
    std::string strSubCanal;
    CassError result = cass_value_get(value, strSubCanal);
    if (result == CASS_OK)
    {
        subCanal = cassandra_exemple::getOperationSubCanal(strSubCanal);
    }
    return result;
}

CassError BaseDAO::cass_value_get(const CassValue* value, cassandra_exemple::OperationDirection& direction)
{
    std::string strDirection;
    CassError result = cass_value_get(value, strDirection);
    if (result == CASS_OK)
    {
        direction = cassandra_exemple::getOperationDirection(strDirection);
    }
    return result;
}

CassError BaseDAO::cass_value_get(const CassValue* value, cassandra_exemple::OperationType& type)
{
    std::string strType;
    CassError result = cass_value_get(value, strType);
    if (result == CASS_OK)
    {
        type = cassandra_exemple::getOperationType(strType);
    }
    return result;
}

void BaseDAO::displayError(CassFuture* resultFuture, const std::string& displayMessage)
{
    const char* message;
    size_t message_length;
    cass_future_error_message(resultFuture, &message, &message_length);
    BOOST_LOG_TRIVIAL(error) << displayMessage << ". Error: " << message;
}




