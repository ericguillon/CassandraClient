#ifndef RECEIVEDTRANSFEROPERATIONFACTORY_H
#define RECEIVEDTRANSFEROPERATIONFACTORY_H
#include <SepaOperationFactory.h>

class ReceivedTransferOperationFactory : public SepaOperationFactory
{
public:
    Operation* buildOperation(XmlNode* node);
    ReceivedTransferOperationFactory(OperationStatusFactory* operationStatusFactory)
    : SepaOperationFactory(operationStatusFactory)
    {}
protected:
};

#endif // RECEIVEDTRANSFEROPERATIONFACTORY_H
