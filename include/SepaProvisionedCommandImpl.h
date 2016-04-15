#ifndef SEPAPROVISIONEDCOMMANDIMPL_H
#define SEPAPROVISIONEDCOMMANDIMPL_H
#include "CommandImpl.h"

class OperationStatus;

class SepaProvisionedCommandImpl : public CommandImpl
{
public:
    SepaProvisionedCommandImpl(OperationFactory* factory, OperationStatusFactory* statusFactory)
    : CommandImpl(factory, statusFactory)
    {}
    void processOperation(Operation* operation);
};

#endif // SEPAPROVISIONEDCOMMANDIMPL_H
