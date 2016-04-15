#ifndef CASSANDRAOPERATIONFACTORY_H
#define CASSANDRAOPERATIONFACTORY_H
#include <cassandra.h>
#include "OperationFactory.h"
#include "CassandraUtils.h"
#include "enums.h"

class Operation;

class CassandraOperationFactory : public CassandraUtils,
                                  public OperationFactory
{
public:
    CassandraOperationFactory(OperationStatusFactory* operationStatusFactory)
    : OperationFactory(operationStatusFactory)
    {}
    Operation* buildOperation(const CassRow* row,
                                cassandra_exemple::OperationType type,
                                cassandra_exemple::OperationStatus status);

};

#endif // CASSANDRAOPERATIONFACTORY_H
