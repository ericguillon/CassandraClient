#include "CassandraUtils.h"

CassError CassandraUtils::cass_collection_append(CassCollection* collection, const unsigned char* value)
{
    return cass_collection_append_string(collection, reinterpret_cast<const char*>(value));
}

CassError CassandraUtils::cass_collection_append(CassCollection* collection, const char* value)
{
    return cass_collection_append_string(collection, value);
}

CassError CassandraUtils::cass_collection_append(CassCollection* collection, const std::string& value)
{
    return cass_collection_append_string(collection, value.c_str());
}

CassError CassandraUtils::cass_value_get_string(const CassValue* value, std::string& destination)
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

CassError CassandraUtils::cass_value_get_bool(const CassValue* value, bool& destination)
{
    cass_bool_t cassBool;
    CassError result = ::cass_value_get_bool(value, &cassBool);
    destination = cassBool == cass_true;
    return result;
}

CassError CassandraUtils::cass_value_get(const CassValue* value, boost::posix_time::ptime& date)
{
    cass_int64_t timestamp;
    cass_value_get_int64(value, &timestamp);
    date = boost::posix_time::from_time_t(timestamp);
}

CassError CassandraUtils::cass_value_get(const CassValue* value, cassandra_exemple::OperationCanal& canal)
{
    std::string strCanal;
    CassError result = cass_value_get(value, strCanal);
    if (result == CASS_OK)
    {
        canal = cassandra_exemple::getOperationCanal(strCanal);
    }
    return result;
}

CassError CassandraUtils::cass_value_get(const CassValue* value, cassandra_exemple::OperationSubCanal& subCanal)
{
    std::string strSubCanal;
    CassError result = cass_value_get(value, strSubCanal);
    if (result == CASS_OK)
    {
        subCanal = cassandra_exemple::getOperationSubCanal(strSubCanal);
    }
    return result;
}

CassError CassandraUtils::cass_value_get(const CassValue* value, cassandra_exemple::OperationDirection& direction)
{
    std::string strDirection;
    CassError result = cass_value_get(value, strDirection);
    if (result == CASS_OK)
    {
        direction = cassandra_exemple::getOperationDirection(strDirection);
    }
    return result;
}

CassError CassandraUtils::cass_value_get(const CassValue* value, cassandra_exemple::OperationType& type)
{
    std::string strType;
    CassError result = cass_value_get(value, strType);
    if (result == CASS_OK)
    {
        type = cassandra_exemple::getOperationType(strType);
    }
    return result;
}
