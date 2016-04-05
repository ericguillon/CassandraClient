/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventDAO.cpp
 * Author: eric
 * 
 * Created on 30 mars 2016, 17:23
 */

#include "Event.h"
#include "Logger.h"
#include "Utils.h"
#include "EventDAO.h"

#define CHECK(a) assert(a == CASS_OK)

EventDAO::EventDAO()
{
    insertBalanceEventStatement = cass_statement_new("INSERT INTO fpe.events (iban, month, id, operation_id, operation_canal,\
                                                        operation_sub_canal, operation_type, event_type, dt_event, description,\
                                                        technical_label, balance_impact, old_balance, new_balance) \
                                                        VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?);", 14);
    insertBalanceErpEventStatement = cass_statement_new("INSERT INTO fpe.events (iban, month, id, operation_id, operation_canal,\
                                                        operation_sub_canal, operation_type, event_type, dt_event, description,\
                                                        technical_label, balance_erp_impact, old_balance_erp, new_balance_erp) \
                                                        VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?);", 14);
    insertStatusEventStatement = cass_statement_new("INSERT INTO fpe.events (iban, month, id, operation_id, operation_canal,\
                                                        operation_sub_canal, operation_type, event_type, dt_event, description,\
                                                        technical_label, old_status, new_status) \
                                                        VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?);", 13);
}

EventDAO::~EventDAO()
{
    cass_statement_free(insertBalanceEventStatement);
    cass_statement_free(insertBalanceErpEventStatement);
    cass_statement_free(insertStatusEventStatement);
}

void EventDAO::bindCommonParameters(CassStatement* statement, Event* event)
{
    cass_statement_bind(statement, 0, event->getIban());
    CHECK(cass_statement_bind(statement, 1, Utils::getMonth(event->getCreationDate())));
    cass_statement_bind(statement, 2, event->getId());
    cass_statement_bind(statement, 3, event->getOperationId());
    cass_statement_bind(statement, 4, event->getOperationCanal());
    cass_statement_bind(statement, 5, event->getOperationSubCanal());
    cass_statement_bind(statement, 6, event->getOperationType());
    cass_statement_bind(statement, 7, event->getType());
    cass_statement_bind(statement, 8, event->getCreationDate());
    cass_statement_bind(statement, 9, event->getDescription());
    cass_statement_bind(statement, 10, event->getTechnicalLabel());
}

void EventDAO::execute(CassStatement* statement, Event* event)
{
    CassFuture* result_future = cass_session_execute(session, statement);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        BOOST_LOG_TRIVIAL(info) << "Event " << event->getId()
                                << " type " << event->getType()
                                << " on operation " << event->getOperationId()
                                 << " from client " << event->getIban()
                                 << " successfully inserted in database";
    }
    else
    {
        displayError(result_future, "Unable to run query");
    }
    cass_future_free(result_future);
}

void EventDAO::insertBalanceEvent(BalanceEvent* event)
{
    insertEvent(insertBalanceEventStatement, event);
}

void EventDAO::insertBalanceErpEvent(BalanceEvent* event)
{
    insertEvent(insertBalanceErpEventStatement, event);
}

void EventDAO::insertEvent(CassStatement* statement, BalanceEvent* event)
{
    bindCommonParameters(statement, event);
    cass_statement_bind(statement, 11, event->getBalanceImpact());
    cass_statement_bind(statement, 12, event->getOldBalance());
    cass_statement_bind(statement, 13, event->getNewBalance());
    execute(statement, event);
}

void EventDAO::insertEvent(StatusEvent* event)
{
    bindCommonParameters(insertStatusEventStatement, event);
    cass_statement_bind(insertStatusEventStatement, 11, event->getOldStatus());
    cass_statement_bind(insertStatusEventStatement, 12, event->getNewStatus());
    execute(insertStatusEventStatement, event);
}

