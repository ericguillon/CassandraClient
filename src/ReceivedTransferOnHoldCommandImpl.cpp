#include "Logger.h"
#include "Decimal.h"
#include "Operation.h"
#include "OperationStatus.h"
#include "OperationStatusFactory.h"
#include "ReceivedTransferOnHoldCommandImpl.h"

void ReceivedTransferOnHoldCommandImpl::processOperation(Operation* operation)
{
    const Compte& clientCompte = operation->getClientCompte();
    Client* client = clientDAO.getClient(clientCompte.iban);
    if (client)
    {
        if (checkClientAccount(client, cassandra_exemple::debitBlocked))
        {
            if (client->getBalanceLimit().isSet())
            {
                if (client->getBalance() + operation->getAmount() - operation->getFee() > client->getBalanceLimit())
                {
                    rejectOperation(operation, cassandra_exemple::limit_reached, "Client balance reached");
                }
            }
            if (operation->getStatus()->getStatus() != cassandra_exemple::rejected)
            {
                checkCorrespondentAccount(operation);
            }
        }
        else
        {
            rejectOperation(operation, cassandra_exemple::client_status, client->getStatus() + " " + clientCompte.iban);
        }
    }
    else
    {
        rejectOperation(operation, cassandra_exemple::client_status, "Unknown account " + clientCompte.iban);
    }

    if (operation->getStatus()->getStatus() != cassandra_exemple::rejected)
    {
        BOOST_LOG_TRIVIAL(info) << "Acknowledging operation " <<  cassandra_exemple::toString(operation->getType())
                                << " id " << operation->getId()
                                << " transaction id" << operation->getTransactionId()
                                << " status " << cassandra_exemple::toString(operation->getStatus()->getStatus())
                                << " for client " << client->getIban();
        const Decimal& fee = operation->getFee();
        Decimal amount = operation->getAmount() * operation->getDirection();
        if (fee.isSet())
        {
            amount -= fee;
        }
        client->updateBalance(amount);
        if (clientDAO.updateClientBalance(client))
        {
            operation->setStatus(statusFactory->getOperationStatus(cassandra_exemple::provisioned));
            updateOperation(operation);
            initializeBalanceEvent(operation, client);
            eventDAO.insertBalanceEvent(balanceEvent);
        }
    }
}
