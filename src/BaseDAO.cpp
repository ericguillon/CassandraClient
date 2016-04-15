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

void BaseDAO::displayError(CassFuture* resultFuture, const std::string& displayMessage)
{
    const char* message;
    size_t message_length;
    cass_future_error_message(resultFuture, &message, &message_length);
    BOOST_LOG_TRIVIAL(error) << displayMessage << ". Error: " << message;
}




