#include "Logger.h"
#include "Client.h"
#include "Decimal.h"
#include "Operation.h"
#include "OperationStatus.h"
#include "OperationStatusFactory.h"
#include "SepaProvisionedCommandImpl.h"

void SepaProvisionedCommandImpl::processOperation(Operation* operation)
{
    Client* client = clientDAO.getClient(operation->getClientCompte().iban);
    const Decimal& fee = operation->getFee();
    Decimal amount = operation->getAmount() * operation->getDirection();
    if (fee.isSet())
    {
        amount -= fee;
    }
    client->updateBalanceErp(amount);
    if (clientDAO.updateClientBalanceErp(client))
    {
        operation->setStatus(statusFactory->getOperationStatus(cassandra_exemple::accounted));
        updateOperation(operation);
        initializeBalanceEvent(operation, client);
        eventDAO.insertBalanceErpEvent(balanceEvent);
    }
    clientDAO.release(client);
}
