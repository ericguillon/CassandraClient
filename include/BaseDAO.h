/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseDAO.h
 * Author: eric
 *
 * Created on 23 mars 2016, 11:09
 */

#ifndef BASEDAO_H
#define BASEDAO_H

#include <string>
#include <cassandra.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "enums.h"
#include "TypeTraits.h"

class Decimal;
class BaseDAO
{
public:
    BaseDAO();
    ~BaseDAO();
    
protected:
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, const char* value);
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, const std::string& value);
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, const Decimal& decimal);
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, CassCollection* collection);
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, const CassCollection* collection);
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, bool value);
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, const boost::posix_time::ptime& date);
    template <typename T>
    CassError cass_statement_bind(CassStatement* statement, std::size_t index, T value)
    {
        return cass_statement_bind(statement, index, cassandra_exemple::toString(value));
    }

    CassError cass_collection_append(CassCollection* collection, const char* value);
    CassError cass_collection_append(CassCollection* collection, const unsigned char* value);
    CassError cass_collection_append(CassCollection* collection, const std::string& value);
    template <typename T>
    CassError cass_collection_append(CassCollection* collection, T value)
    {
        return cass_collection_append(collection, cassandra_exemple::toString(value));
    }
    
    CassError cass_value_get_string(const CassValue* value, std::string& destination);
    CassError cass_value_get_bool(const CassValue* value, bool& destination);
    CassError cass_value_get(const CassValue* value, bool& destination)
    {
        return cass_value_get_bool(value, destination);
    }
    CassError cass_value_get(const CassValue* value, std::string& destination)
    {
        return cass_value_get_string(value, destination);
    }
    CassError cass_value_get(const CassValue* value, boost::posix_time::ptime& date);
    CassError cass_value_get(const CassValue* value, cassandra_exemple::OperationCanal& canal);
    CassError cass_value_get(const CassValue* value, cassandra_exemple::OperationSubCanal& subCanal);
    CassError cass_value_get(const CassValue* value, cassandra_exemple::OperationDirection& direction);
    CassError cass_value_get(const CassValue* value, cassandra_exemple::OperationType& type);
    
    template <typename T1>
    CassFuture* session_execute(CassStatement* statement,
                                typename CallTraits<T1>::Type param)
    {
        cass_statement_bind(statement, 0, param);
        return cass_session_execute(session, statement);
    }
    
    template <typename T1, typename T2>
    CassFuture* session_execute(CassStatement* statement,
                                typename CallTraits<T1>::Type param1,
                                typename CallTraits<T2>::Type param2)
    {
        cass_statement_bind(statement, 0, param1);
        cass_statement_bind(statement, 1, param2);
        return cass_session_execute(session, statement);
    }
    
    template <typename T1, typename T2, typename T3>
    CassFuture* session_execute(CassStatement* statement,
                                typename CallTraits<T1>::Type param1,
                                typename CallTraits<T2>::Type param2,
                                typename CallTraits<T3>::Type param3)
    {
        cass_statement_bind(statement, 0, param1);
        cass_statement_bind(statement, 1, param2);
        cass_statement_bind(statement, 2, param3);
        return cass_session_execute(session, statement);
    }
    
    template <typename T1, typename T2, typename T3, typename T4>
    CassFuture* session_execute(CassStatement* statement,
                                typename CallTraits<T1>::Type param1,
                                typename CallTraits<T2>::Type param2,
                                typename CallTraits<T3>::Type param3,
                                typename CallTraits<T4>::Type param4)
    {
        cass_statement_bind(statement, 0, param1);
        cass_statement_bind(statement, 1, param2);
        cass_statement_bind(statement, 2, param3);
        cass_statement_bind(statement, 3, param4);
        return cass_session_execute(session, statement);
    }
    
    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    CassFuture* session_execute(CassStatement* statement,
                                typename CallTraits<T1>::Type param1,
                                typename CallTraits<T2>::Type param2,
                                typename CallTraits<T3>::Type param3,
                                typename CallTraits<T4>::Type param4,
                                typename CallTraits<T5>::Type param5)
    {
        cass_statement_bind(statement, 0, param1);
        cass_statement_bind(statement, 1, param2);
        cass_statement_bind(statement, 2, param3);
        cass_statement_bind(statement, 3, param4);
        cass_statement_bind(statement, 4, param5);
        return cass_session_execute(session, statement);
    }
    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    CassFuture* session_execute(CassStatement* statement,
                                typename CallTraits<T1>::Type param1,
                                typename CallTraits<T2>::Type param2,
                                typename CallTraits<T3>::Type param3,
                                typename CallTraits<T4>::Type param4,
                                typename CallTraits<T5>::Type param5,
                                typename CallTraits<T6>::Type param6)
    {
        cass_statement_bind(statement, 0, param1);
        cass_statement_bind(statement, 1, param2);
        cass_statement_bind(statement, 2, param3);
        cass_statement_bind(statement, 3, param4);
        cass_statement_bind(statement, 4, param5);
        cass_statement_bind(statement, 5, param6);
        return cass_session_execute(session, statement);
    }
    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    CassFuture* session_execute(CassStatement* statement,
                                typename CallTraits<T1>::Type param1,
                                typename CallTraits<T2>::Type param2,
                                typename CallTraits<T3>::Type param3,
                                typename CallTraits<T4>::Type param4,
                                typename CallTraits<T5>::Type param5,
                                typename CallTraits<T6>::Type param7,
                                typename CallTraits<T7>::Type param8,
                                typename CallTraits<T8>::Type param9,
                                typename CallTraits<T9>::Type param10,
                                typename CallTraits<T10>::Type param6,
                                typename CallTraits<T11>::Type param11)
    {
        cass_statement_bind(statement, 0, param1);
        cass_statement_bind(statement, 1, param2);
        cass_statement_bind(statement, 2, param3);
        cass_statement_bind(statement, 3, param4);
        cass_statement_bind(statement, 4, param5);
        cass_statement_bind(statement, 5, param6);
        cass_statement_bind(statement, 6, param7);
        cass_statement_bind(statement, 7, param8);
        cass_statement_bind(statement, 8, param9);
        cass_statement_bind(statement, 9, param10);
        cass_statement_bind(statement, 10, param11);
        return cass_session_execute(session, statement);
    }
    void displayError(CassFuture* resultFuture, const std::string& message);

protected:
    CassSession* session;

private:
    BaseDAO(const BaseDAO& orig);
};

#endif /* BASEDAO_H */

