/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   OperationDAO.cpp
 * Author: eric
 *
 * Created on 29 mars 2016, 17:03
 */
#include <typeinfo>
#include <cassert>
#include "boost/foreach.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Logger.h"
#include "Operation.h"
#include "OperationHandler.h"
#include "Decimal.h"
#include "OperationStatus.h"
#include "Utils.h"
#include "CustomFields.h"
#include "constants.h"
#include "OperationFactory.h"
#include "OperationStatusFactory.h"
#include "OperationDAO.h"

#define CHECK(a) assert(a == CASS_OK)

OperationDAO::OperationDAO(OperationFactory* factory_, OperationStatusFactory* statusFactory_)
: factory(factory_)
, statusFactory(statusFactory_)
{
    insertOperationStatement = cass_statement_new("INSERT INTO fpe.operations (month, iban, id, status, custom_fields,\
                                                                               canal, sub_canal, type, acquirer_id, insertion_date,\
                                                                               required_settlement_date, local_required_amount,\
                                                                               euro_required_amount, sepa_transaction_id,\
                                                                               sepa_bank, sepa_message_id, sepa_fpe_rejected,\
                                                                               sepa_sab_rejected, sepa_sab_reject, rejection_cause,\
                                                                               mastercard_stan)\
                                                    VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?, ?);", 21);
    selectOperationStatement = cass_statement_new("SELECT id, status, custom_fields, canal, sub_canal,\
                                                          type, acquirer_id, insertion_date, required_settlement_date, local_required_amount,\
                                                          euro_required_amount, sepa_transaction_id, sepa_bank, sepa_message_id, sepa_fpe_rejected,\
                                                          sepa_sab_rejected, sepa_sab_reject, rejection_cause FROM fpe.operations\
                                                    WHERE month=? AND iban=?", 2);
    selectOperationTypeStatusStatement = cass_statement_new("SELECT iban, id, custom_fields, canal, sub_canal,\
                                                                    acquirer_id, insertion_date, required_settlement_date, local_required_amount,\
                                                                    euro_required_amount, sepa_transaction_id, sepa_bank, sepa_message_id, sepa_fpe_rejected,\
                                                                    sepa_sab_rejected, sepa_sab_reject, rejection_cause FROM fpe.operations\
                                                            WHERE type=? AND status=? ALLOW FILTERING;", 2);
    selectRejectedOperationStatement = cass_statement_new("SELECT iban, id, status, custom_fields, canal, sub_canal,\
                                                                  type, acquirer_id, insertion_date, required_settlement_date, local_required_amount,\
                                                                  euro_required_amount, sepa_transaction_id, sepa_bank, sepa_message_id, sepa_fpe_rejected,\
                                                                   sepa_sab_rejected, sepa_sab_reject, rejection_cause FROM fpe.operations\
                                                            WHERE sepa_sab_reject=?", 1);
    rejectedOperationStatement = cass_statement_new("UPDATE fpe.operations SET status=?, rejection_cause=?, rejection_date=?,\
                                                            rejected_amount=?, sepa_fpe_rejected=?, sepa_sab_rejected=?, sepa_sab_reject=?,\
                                                            custom_fields = custom_fields + ?\
                                                    WHERE month=? AND iban=? AND mastercard_stan='' AND id=?", 11);
    provisionedOperationStatement = cass_statement_new("UPDATE fpe.operations SET status=?, provision_due_date=?, provisioned_amount=?\
                                                        WHERE month=? AND iban=? AND mastercard_stan='' AND id=?", 6);

    accountedOperationStatement = cass_statement_new("UPDATE fpe.operations SET status=?, accounting_date=?, accounted_amount=?\
                                                     WHERE month=? AND iban=? AND mastercard_stan='' AND id=?", 6);

}

OperationDAO::~OperationDAO()
{
    cass_statement_free(insertOperationStatement);
    cass_statement_free(selectOperationStatement);
    cass_statement_free(rejectedOperationStatement);
    cass_statement_free(provisionedOperationStatement);
    cass_statement_free(accountedOperationStatement);
    cass_statement_free(selectOperationTypeStatusStatement);
    cass_statement_free(selectRejectedOperationStatement);
}

void OperationDAO::getOperation(const std::string& month,
                                const std::string& iban,
                                std::vector<Operation*>& operations)
{

}

void OperationDAO::getOperation(const std::string& month,
                                const std::string& iban,
                                const std::string& transactionId,
                                std::vector<Operation*>& operations)
{

}

void OperationDAO::getRejectedOperations(std::vector<Operation*>& operations)
{
    CassFuture* result_future = session_execute<bool>
                                                (selectRejectedOperationStatement,
                                                true);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        const CassResult* result = cass_future_get_result(result_future);
        CassIterator* rows = cass_iterator_from_result(result);
        while (cass_iterator_next(rows))
        {
            const CassRow* row = cass_iterator_get_row(rows);
            Operation* operation = factory->get();

            const CassValue* ibanValue = cass_row_get_column(row, 0);
            const CassValue* idValue = cass_row_get_column(row, 1);
            const CassValue* statusValue = cass_row_get_column(row, 2);
            const CassValue* customFieldsValue = cass_row_get_column(row, 3);

            CassIterator* mapIterator = cass_iterator_from_map(customFieldsValue);
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

            const CassValue* canalValue = cass_row_get_column(row, 4);
            const CassValue* subCanalValue = cass_row_get_column(row, 5);
            const CassValue* typeValue = cass_row_get_column(row, 6);
            const CassValue* acquirer_id = cass_row_get_column(row, 7);
            const CassValue* insertionDateValue = cass_row_get_column(row, 8);
            const CassValue* requiredSettlementDateValue = cass_row_get_column(row, 9);
            const CassValue* requiredAmountValue = cass_row_get_column(row, 11);
            const CassValue* transactionIdValue = cass_row_get_column(row, 12);
            const CassValue* messageIdValue = cass_row_get_column(row, 14);

            cass_value_get(typeValue, operation->type);
            std::string value;
            cass_value_get_string(statusValue, value);
            cassandra_exemple::OperationStatus status = cassandra_exemple::getOperationStatus(value);
            OperationStatus* operationStatus = statusFactory->getOperationStatus(status);
            operationStatus->initialize(statusFactory, row);
            operation->setStatus(operationStatus);

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

            operations.push_back(operation);
        }
        cass_iterator_free(rows);
        cass_result_free(result);
    }
    cass_future_free(result_future);
}

void OperationDAO::getOperation(cassandra_exemple::OperationType type,
                                cassandra_exemple::OperationStatus status,
                                std::vector<Operation*>& operations)
{
    CassFuture* result_future = session_execute<cassandra_exemple::OperationType, cassandra_exemple::OperationStatus>
                                                (selectOperationTypeStatusStatement,
                                                type,
                                                status);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        const CassResult* result = cass_future_get_result(result_future);
        CassIterator* rows = cass_iterator_from_result(result);
        while (cass_iterator_next(rows))
        {
            const CassRow* row = cass_iterator_get_row(rows);
            Operation* operation = factory->get();
            operation->setType(type);
            OperationStatus* operationStatus = statusFactory->getOperationStatus(status);
            operationStatus->initialize(statusFactory, row);
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

            operations.push_back(operation);
        }
        cass_iterator_free(rows);
        cass_result_free(result);
    }
    cass_future_free(result_future);
}

void OperationDAO::getOperation(cassandra_exemple::OperationType type,
                                cassandra_exemple::OperationStatus status,
                                OperationHandler* operationHandler)
{
    CassFuture* result_future = session_execute<cassandra_exemple::OperationType, cassandra_exemple::OperationStatus>
                                                (selectOperationTypeStatusStatement,
                                                type,
                                                status);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        const CassResult* result = cass_future_get_result(result_future);
        CassIterator* rows = cass_iterator_from_result(result);
        while (cass_iterator_next(rows))
        {
            const CassRow* row = cass_iterator_get_row(rows);
            operationHandler->onResultAvailable(row, type, status);
        }
        cass_iterator_free(rows);
        cass_result_free(result);
    }
    cass_future_free(result_future);
}

void OperationDAO::insertOperation(Operation* operation)
{
    const Compte& clientCompte = operation->getClientCompte();
    std::string rejectionCause;
    bool sabRejected = false;
    CassCollection* customFields = cass_collection_new(CASS_COLLECTION_TYPE_MAP, 6);
    cass_collection_append(customFields, CustomFields::OPERATION_DIRECTION);
    cass_collection_append(customFields, operation->getDirection());

    if (operation->getFee().getValue())
    {
        cass_collection_append(customFields, CustomFields::FPE_FEE);
        cass_collection_append(customFields, operation->getFee().getBytes());
    }

    if (Rejet* rejet = operation->getRejet())
    {
        cass_collection_append(customFields, CustomFields::REJECTION_CODE);
        cass_collection_append(customFields, rejet->code);
        rejectionCause = rejet->cause;
        sabRejected = true;
    }
    const std::string& uuId = Utils::getUUId();
    operation->setId(uuId);

    CHECK(cass_statement_bind(insertOperationStatement, 0, Utils::getMonth(operation->getInsertionDate())));
    CHECK(cass_statement_bind(insertOperationStatement, 1, clientCompte.iban));
    CHECK(cass_statement_bind(insertOperationStatement, 2, uuId));
    CHECK(cass_statement_bind(insertOperationStatement, 3, operation->getStatus()->getStatus()));
    CHECK(cass_statement_bind(insertOperationStatement, 4, customFields));
    CHECK(cass_statement_bind(insertOperationStatement, 5, operation->getCanal()));
    CHECK(cass_statement_bind(insertOperationStatement, 6, operation->getSubCanal()));
    CHECK(cass_statement_bind(insertOperationStatement, 7, operation->getType()));
    CHECK(cass_statement_bind(insertOperationStatement, 8, operation->getCorrespondentCompte().iban));
    CHECK(cass_statement_bind(insertOperationStatement, 9, operation->getInsertionDate()));
    CHECK(cass_statement_bind(insertOperationStatement, 10, operation->getSettlementDate()));
    CHECK(cass_statement_bind(insertOperationStatement, 11, operation->getAmount()));
    CHECK(cass_statement_bind(insertOperationStatement, 12, operation->getAmount()));
    CHECK(cass_statement_bind(insertOperationStatement, 13, operation->getTransactionId()));
    CHECK(cass_statement_bind(insertOperationStatement, 14, ""));
    CHECK(cass_statement_bind(insertOperationStatement, 15, operation->getMessageId()));
    CHECK(cass_statement_bind(insertOperationStatement, 16, false));
    CHECK(cass_statement_bind(insertOperationStatement, 17, sabRejected));
    CHECK(cass_statement_bind(insertOperationStatement, 18, false));
    CHECK(cass_statement_bind(insertOperationStatement, 19, rejectionCause));
    CHECK(cass_statement_bind(insertOperationStatement, 20, ""));
    CassFuture* result_future = cass_session_execute(session, insertOperationStatement);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        BOOST_LOG_TRIVIAL(info) << "Operation " << operation->getTransactionId()
                                 << " from client " << clientCompte.iban
                                 << " successfully inserted in database";
    }
    else
    {
        displayError(result_future, "Unable to run query");
    }
    cass_future_free(result_future);
    cass_collection_free(customFields);
}

void OperationDAO::updateOperation(Operation* operation)
{
    operation->getStatus()->update(this);
}

bool OperationDAO::isOperationInserted(Operation* operation)
{
    bool operationInserted = false;
    cass_statement_bind(selectOperationStatement, 1, operation->getClientCompte().iban);
    cass_statement_bind(selectOperationStatement, 0, Utils::getMonth(operation->getInsertionDate()));
    CassFuture* result_future = cass_session_execute(session, selectOperationStatement);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        const CassResult* result = cass_future_get_result(result_future);
        if (cass_result_row_count(result))
        {
            CassIterator* rows = cass_iterator_from_result(result);

            while(cass_iterator_next(rows))
            {
                const CassRow* row = cass_iterator_get_row(rows);
                const CassValue* transactionIdValue = cass_row_get_column_by_name(row, "sepa_transaction_id");
                std::string transactionId;
                cass_value_get_string(transactionIdValue, transactionId);
                if (operation->getTransactionId() == transactionId)
                {
                    const CassValue* messageIdValue = cass_row_get_column_by_name(row, "sepa_message_id");
                    std::string messageId;
                    cass_value_get_string(messageIdValue, messageId);
                    if (operation->getMessageId() == messageId)
                    {
                        operationInserted = true;
                        const CassValue* idValue = cass_row_get_column_by_name(row, "id");
                        const CassValue* typeValue = cass_row_get_column_by_name(row, "type");
                        const CassValue* statusValue = cass_row_get_column_by_name(row, "status");
                        const CassValue* insertionDateValue = cass_row_get_column_by_name(row, "insertion_date");

                        std::string value;
                        cass_value_get_string(typeValue, value);
                        cassandra_exemple::OperationType operationType = cassandra_exemple::getOperationType(value);
                        if (operation->getType() == operationType)
                        {
                            BOOST_LOG_TRIVIAL(info) << "Operation " << operation->getTransactionId()
                                                    << " type " << value
                                                    << " from client " << operation->getClientCompte().iban
                                                    << " was already inserted";
                        }

                        cass_value_get_string(statusValue, value);
                        cassandra_exemple::OperationStatus status = cassandra_exemple::getOperationStatus(value);
                        OperationStatus* operationStatus = statusFactory->getOperationStatus(status);
                        operationStatus->initialize(statusFactory, row);
                        operation->setStatus(operationStatus);
                        cass_value_get_string(idValue, operation->id);
                        cass_int64_t timestamp;
                        cass_value_get_int64(insertionDateValue, &timestamp);
                        operation->setInsertionDate(boost::posix_time::from_time_t(timestamp));
                        break;
                    }
                }

            }
            cass_iterator_free(rows);
        }
        cass_result_free(result);
    }
    else
    {
        displayError(result_future, "Unable to run query");
    }
    cass_future_free(result_future);
    return operationInserted;
}

void OperationDAO::updateOperationStatus(ReservedStatus* status)
{

}

void OperationDAO::updateOperationStatus(RejectedStatus* status)
{
    Operation* operation = status->getOperation();
    CassCollection* customFields = cass_collection_new(CASS_COLLECTION_TYPE_MAP, 2);
    cass_collection_append(customFields, CustomFields::REJECTION_CODE);
    cass_collection_append(customFields, status->getCode());
    session_execute<cassandra_exemple::OperationStatus, std::string, boost::posix_time::ptime, Decimal, bool, bool, bool, CassCollection*, std::string, std::string, std::string>( rejectedOperationStatement,
                    status->getStatus(),
                    status->getCause(),
                    boost::posix_time::second_clock::local_time(),
                    operation->getAmount(),
                    status->isFpeRejected(),
                    status->isSabRejected(),
                    status->isNotifySab(),
                    customFields,
                    Utils::getMonth(operation->getInsertionDate()),
                    operation->getClientCompte().iban,
                    operation->getId());

}

void OperationDAO::updateOperationStatus(OnHoldStatus* status)
{

}

void OperationDAO::updateOperationStatus(ProvisionedStatus* status)
{
    Operation* operation = status->getOperation();
    BOOST_LOG_TRIVIAL(info) << "Updating operation id " << operation->getId()
                            << " month " << Utils::getMonth(operation->getInsertionDate())
                            << " iban " << operation->getClientCompte().iban
                            << " transaction id " << operation->getTransactionId();

    session_execute<cassandra_exemple::OperationStatus, boost::posix_time::ptime, Decimal, std::string, std::string, std::string>
                                                (provisionedOperationStatement,
                                                status->getStatus(),
                                                boost::posix_time::second_clock::local_time(),
                                                operation->getAmount(),
                                                Utils::getMonth(operation->getInsertionDate()),
                                                operation->getClientCompte().iban,
                                                operation->getId());

}

void OperationDAO::updateOperationStatus(AccountedStatus* status)
{
    Operation* operation = status->getOperation();
    session_execute<cassandra_exemple::OperationStatus, boost::posix_time::ptime, Decimal, std::string, std::string, std::string>
                    (accountedOperationStatement,
                    status->getStatus(),
                    boost::posix_time::second_clock::local_time(),
                    operation->getAmount(),
                    Utils::getMonth(operation->getInsertionDate()),
                    operation->getClientCompte().iban,
                    operation->getId());
}

void OperationDAO::updateOperationStatus(CancelledStatus* status)
{

}



