#include "Logger.h"
#include "enums.h"
#include "Operation.h"
#include "OperationStatus.h"
#include "ReceivedTransferCommandImpl.h"

void ReceivedTransferCommandImpl::processOperation(Operation* operation)
{
    const Compte& clientCompte = operation->getClientCompte();
//    BOOST_LOG_TRIVIAL(info) << "Creating client " << clientCompte.iban << "...";
//    createClient(clientCompte.iban);
    BOOST_LOG_TRIVIAL(info) << "Processing operation " << operation->getTransactionId() << "...";
    OperationStatus* oldOperationStatus = operation->getStatus();
    bool operationInserted = isOperationInserted(operation);
    if (!operationInserted)
    {
        insertOperation(operation);
    }

    if (Client* client = clientDAO.getClient(clientCompte.iban))
    {
        if (checkClientAccount(client, cassandra_exemple::debitBlocked))
        {
            checkCorrespondentAccount(operation);
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

    if (operation->getStatus()->getStatus() == cassandra_exemple::rejected)
    {
        updateOperation(operation);
    }
}
