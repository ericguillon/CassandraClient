#ifndef SEPACOMMONCOMMAND_H
#define SEPACOMMONCOMMAND_H

#include "OperationHandler.h"
#include "BaseCommand.h"
#include "enums.h"
#include "CassandraOperationFactory.h"

template <typename DerivedClass, typename JobImpl>
class SepaCommonCommand : public BaseCommand<DerivedClass, CassandraOperationFactory>,
                          public JobImpl
{
public:
    SepaCommonCommand()
    : JobImpl(this->factory, BaseCommand<DerivedClass, CassandraOperationFactory>::statusFactory)
    {
    }

    void execute()
    {
        Operation* operation = this->factory->buildOperation(row, type, status);
        handler->setDone();
        JobImpl::processOperation(operation);
        this->factory->release(operation);
    }

    friend class MultiThreadedCommandFactory;
protected:
    OperationStatus* getOperationStatus(cassandra_exemple::OperationStatus status)
    {
        return this->statusFactory->getOperationStatus(status);
    }

protected:
    const CassRow* row;
    cassandra_exemple::OperationType type;
    cassandra_exemple::OperationStatus status;
    OperationHandler* handler;
};

#endif // SEPACOMMONCOMMAND_H
