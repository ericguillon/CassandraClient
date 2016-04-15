#include "SepaHeader.h"
#include "OperationStatusFactory.h"
#include "ReceivedTransferOperationFactory.h"
#include "ReceivedTransferCommandImpl.h"
#include "SingleThreadedCommandFactory.h"

SingleThreadedCommandFactory::SingleThreadedCommandFactory()
{
    statusFactory = new OperationStatusFactory;
    factory = new ReceivedTransferOperationFactory(statusFactory);
    receivedTransferCommandImpl = new ReceivedTransferCommandImpl(factory, statusFactory);
}

SingleThreadedCommandFactory::~SingleThreadedCommandFactory()
{
    delete receivedTransferCommandImpl;
    delete factory;
    delete statusFactory;
}

void SingleThreadedCommandFactory::addCommand(rapidxml::xml_node<>* node,
                                              boost::shared_ptr<SepaHeader> sepaHeader)
{
    Operation* operation = factory->buildOperation(node);
    operation->setMessageId(sepaHeader->messageId);
    operation->setSettlementDate(sepaHeader->settlementDate);
    receivedTransferCommandImpl->processOperation(operation);
    factory->release(operation);
}
