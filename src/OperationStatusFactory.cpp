#include "OperationStatus.h"
#include "CustomFields.h"
#include "OperationStatusFactory.h"

OperationStatusFactory::OperationStatusFactory()
{
    operationStatuses = { new ReservedStatus, new OnHoldStatus,
                          new ProvisionedStatus, new AccountedStatus,
                          new CancelledStatus, new RejectedStatus};
}

OperationStatusFactory::~OperationStatusFactory()
{
    for (OperationStatus* status : operationStatuses)
    {
        delete status;
    }
}

OperationStatus* OperationStatusFactory::getOperationStatus(cassandra_exemple::OperationStatus operationStatus) const
{
    return operationStatuses[operationStatus];
}

template <>
void OperationStatusFactory::initializeOperationStatus<RejectedStatus>(RejectedStatus* rejectedStatus, const CassRow* row)
{
    const CassValue* customFieldsValue = cass_row_get_column_by_name(row, "custom_fields");
    const CassValue* rejectionCauseValue = cass_row_get_column_by_name(row, "rejection_cause");
    const CassValue* fpeRejectedValue = cass_row_get_column_by_name(row, "sepa_fpe_rejected");
    const CassValue* sabRejectedValue = cass_row_get_column_by_name(row, "sepa_sab_rejected");
    const CassValue* sabRejectValue = cass_row_get_column_by_name(row, "sepa_sab_reject");

    if (CassIterator* iterator = cass_iterator_from_map(customFieldsValue))
    {
        while (cass_iterator_next(iterator))
        {
            std::string value;
            const CassValue* key = cass_iterator_get_map_key(iterator);
            cass_value_get_string(key, value);
            if (value == CustomFields::REJECTION_CODE)
            {
                const CassValue* rejectionCodeValue = cass_iterator_get_map_value(iterator);
                cass_value_get_string(rejectionCodeValue, value);
                rejectedStatus->setCode(cassandra_exemple::getRejectionCode(value));
                break;
            }
        }
        cass_iterator_free(iterator);
    }
    cass_value_get_string(rejectionCauseValue, rejectedStatus->cause);
    cass_value_get_bool(fpeRejectedValue, rejectedStatus->fpeRejected);
    cass_value_get_bool(sabRejectedValue, rejectedStatus->sabRejected);
    cass_value_get_bool(sabRejectValue, rejectedStatus->notifySab);
}

