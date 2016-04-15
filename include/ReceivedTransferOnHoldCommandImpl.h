#ifndef RECEIVEDTRANSFERONHOLDCOMMANDIMPL_H
#define RECEIVEDTRANSFERONHOLDCOMMANDIMPL_H
#include "CommandImpl.h"

class ReceivedTransferOnHoldCommandImpl: public CommandImpl
{
public:
    ReceivedTransferOnHoldCommandImpl(OperationFactory* factory, OperationStatusFactory* statusFactory)
    : CommandImpl(factory, statusFactory)
    {}
    void processOperation(Operation* operation);
};

#endif // RECEIVEDTRANSFERONHOLDCOMMANDIMPL_H
