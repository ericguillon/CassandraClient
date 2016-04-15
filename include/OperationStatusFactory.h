#ifndef OPERATIONSTATUSFACTORY_H
#define OPERATIONSTATUSFACTORY_H
#include <vector>
#include <cassandra.h>
#include "CassandraUtils.h"
#include "enums.h"

class OperationStatus;

class OperationStatusFactory : public CassandraUtils
{
public:
    OperationStatusFactory();
    ~OperationStatusFactory();
    OperationStatus* getOperationStatus(cassandra_exemple::OperationStatus operationStatus) const;

    template <typename T>
    void initializeOperationStatus(T* operationStatus, const CassRow* row);

protected:
    std::vector<OperationStatus*> operationStatuses;
};

template <typename T>
void OperationStatusFactory::initializeOperationStatus(T* status, const CassRow* row)
{
}

#endif // OPERATIONSTATUSFACTORY_H
