#ifndef RECEIVEDTRANSFERONHOLDCOMMAND_H
#define RECEIVEDTRANSFERONHOLDCOMMAND_H

#include "SepaCommonCommand.h"
#include "ReceivedTransferOnHoldCommandImpl.h"

class OperationHandler;
class ReceivedTransferOnHoldCommand: public SepaCommonCommand<ReceivedTransferOnHoldCommand, ReceivedTransferOnHoldCommandImpl>
{
public:
    ReceivedTransferOnHoldCommand();
};

#endif // RECEIVEDTRANSFERONHOLDCOMMAND_H
