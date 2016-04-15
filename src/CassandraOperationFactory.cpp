#include "Operation.h"
#include "OperationStatus.h"
#include "OperationStatusFactory.h"
#include "Decimal.h"
#include "CustomFields.h"
#include "CassandraOperationFactory.h"

Operation* CassandraOperationFactory::buildOperation(const CassRow* row,
                                                     cassandra_exemple::OperationType type,
                                                     cassandra_exemple::OperationStatus status)
{
    Operation* operation = get();
    operation->setType(type);
    OperationStatus* operationStatus = operationStatusFactory->getOperationStatus(status);
    operationStatus->initialize(operationStatusFactory, row);
    operation->setStatus(operationStatus);

    const CassValue* ibanValue = cass_row_get_column(row, 0);
    const CassValue* idValue = cass_row_get_column(row, 1);
    const CassValue* customFieldsValue = cass_row_get_column(row, 2);

    if (CassIterator* mapIterator = cass_iterator_from_map(customFieldsValue))
    {
        while (cass_iterator_next(mapIterator))
        {
            const CassValue* key = cass_iterator_get_map_key(mapIterator);
            std::string keyString;
            cass_value_get(key, keyString);
            if (keyString == CustomFields::OPERATION_DIRECTION)
            {
                const CassValue* value = cass_iterator_get_map_value(mapIterator);
                cass_value_get(value, operation->direction);
                break;
            }
        }
        cass_iterator_free(mapIterator);
    }

    const CassValue* canalValue = cass_row_get_column(row, 3);
    const CassValue* subCanalValue = cass_row_get_column(row, 4);
    const CassValue* acquirer_id = cass_row_get_column(row, 5);
    const CassValue* insertionDateValue = cass_row_get_column(row, 6);
    const CassValue* requiredSettlementDateValue = cass_row_get_column(row, 7);
    const CassValue* requiredAmountValue = cass_row_get_column(row, 9);
    const CassValue* transactionIdValue = cass_row_get_column(row, 10);
    const CassValue* messageIdValue = cass_row_get_column(row, 12);

    cass_value_get(ibanValue, operation->getClientCompte().iban);
    cass_value_get(idValue, operation->id);
    cass_value_get(canalValue, operation->canal);
    cass_value_get(subCanalValue, operation->subCanal);
    cass_value_get(acquirer_id, operation->getCorrespondentCompte().iban);
    cass_value_get(insertionDateValue, operation->insertionDate);
    cass_value_get(requiredSettlementDateValue, operation->settlementDate);
    ::cass_value_get(requiredAmountValue, operation->amount);
    cass_value_get(transactionIdValue, operation->transactionId);
    cass_value_get(messageIdValue, operation->messageId);
    return operation;
}



