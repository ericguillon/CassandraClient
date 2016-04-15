#ifndef RECEIVEDTRANSFERCOMMAND_H
#define RECEIVEDTRANSFERCOMMAND_H

#include "BaseCommand.h"
#include "ReceivedTransferOperationFactory.h"
#include "ReceivedTransferCommandImpl.h"

class ReceivedTransferCommand: public BaseCommand<ReceivedTransferCommand, ReceivedTransferOperationFactory>,
                               public ReceivedTransferCommandImpl
{
public:
    ReceivedTransferCommand()
    : ReceivedTransferCommandImpl(factory, BaseCommand<ReceivedTransferCommand, ReceivedTransferOperationFactory>::statusFactory)
    {}
    void execute();
    friend class MultiThreadedCommandFactory;
protected:
    XmlNode* node;
    boost::shared_ptr<SepaHeader> sepaHeader;
};

#endif // RECEIVEDTRANSFERCOMMAND_H
