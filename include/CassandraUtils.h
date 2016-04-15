#ifndef CASSANDRAUTILS_H
#define CASSANDRAUTILS_H
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cassandra.h>
#include "enums.h"

class CassandraUtils
{
protected:
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

};

#endif // CASSANDRAUTILS_H
