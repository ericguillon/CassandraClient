#ifndef RECEIVEDTRANSFERCOMMANDIMPL_H
#define RECEIVEDTRANSFERCOMMANDIMPL_H
#include "CommandImpl.h"

class ReceivedTransferCommandImpl : public CommandImpl
{
public:
    ReceivedTransferCommandImpl(OperationFactory* factory, OperationStatusFactory* statusFactory)
    : CommandImpl(factory, statusFactory)
    {}
    void processOperation(Operation* operation);
    void createClient(const std::string& iban);
};

#endif // RECEIVEDTRANSFERCOMMANDIMPL_H
