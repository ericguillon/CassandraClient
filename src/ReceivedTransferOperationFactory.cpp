#include "Operation.h"
#include "OperationStatus.h"
#include "OperationStatusFactory.h"
#include "enums.h"
#include "constants.h"
#include "ReceivedTransferOperationFactory.h"

Operation* ReceivedTransferOperationFactory::buildOperation(XmlNode* receivedTransferNode)
{
    Operation* operation = get();
    operation->setCanal(cassandra_exemple::OperationCanal::sepa);
    operation->setSubCanal(cassandra_exemple::OperationSubCanal::sepa_received_transfer);
    operation->setType(cassandra_exemple::OperationType::sepa_received_transfer_operation);
    operation->setStatus(operationStatusFactory->getOperationStatus(cassandra_exemple::OperationStatus::reserved));
    operation->setDirection(cassandra_exemple::OperationDirection::credit);
    operation->setInsertionDate(boost::posix_time::second_clock::local_time());
    fillCompte(operation->getClientCompte(), creditorAgent, receivedTransferNode);
    fillCompte(operation->getCorrespondentCompte(), debtorAgent, receivedTransferNode);
    fillIds(operation, receivedTransferNode);
    if (XmlNode* node = receivedTransferNode->first_node(Constants::INTERBANK_SETTLEMENT_AMOUNT))
    {
        char* amount;
        decodeField(amount, node);
        Decimal localAmount(atof(amount));
        operation->setAmount(localAmount);
        operation->setFee(Decimal(-0.0));
        operation->setAuthorizedAmount(operation->getAmount() + operation->getFee());
    }
    return operation;
}
