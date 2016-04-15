#include "Operation.h"
#include "SepaHeader.h"
#include "OperationStatusFactory.h"
#include "ReceivedTransferCommand.h"

void ReceivedTransferCommand::execute()
{
    Operation* operation = factory->buildOperation(node);
    operation->setMessageId(sepaHeader->messageId);
    operation->setSettlementDate(sepaHeader->settlementDate);
    processOperation(operation);
    factory->release(operation);
}
