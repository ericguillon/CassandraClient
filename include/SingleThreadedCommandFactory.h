#ifndef SINGLETHREADEDCOMMANDFACTORY_H
#define SINGLETHREADEDCOMMANDFACTORY_H

#include "CommandFactory.h"

class OperationStatusFactory;
class ReceivedTransferOperationFactory;
class ReceivedTransferCommandImpl;

class SingleThreadedCommandFactory : public CommandFactory
{
public:
    SingleThreadedCommandFactory();
    ~SingleThreadedCommandFactory();
    void addCommand(rapidxml::xml_node<>* node,
                    boost::shared_ptr<SepaHeader> sepaHeader);
    void addCommand(const CassRow* row,
                    cassandra_exemple::OperationType type,
                    cassandra_exemple::OperationStatus status,
                    OnHoldOperationHandler* handler){}
    void addCommand(const CassRow* row,
                    cassandra_exemple::OperationType type,
                    cassandra_exemple::OperationStatus status,
                    ProvionedOperationHandler* handler){}
    void flush(bool stop = false){}

protected:
    OperationStatusFactory* statusFactory;
    ReceivedTransferOperationFactory* factory;
    ReceivedTransferCommandImpl* receivedTransferCommandImpl;
};

#endif // SINGLETHREADEDCOMMANDFACTORY_H
