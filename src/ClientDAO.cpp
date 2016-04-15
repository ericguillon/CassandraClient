/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ClientDAO.cpp
 * Author: eric
 *
 * Created on 22 mars 2016, 16:12
 */
#include <boost/foreach.hpp>
#include <boost/algorithm/string/join.hpp>
#include "Utils.h"
#include "Logger.h"
#include "Client.h"
#include "ClientDAO.h"

ClientDAO::ClientDAO()
{
    selectClientStatement = cass_statement_new("SELECT revision_id, balance, balance_erp, balance_limit, status, sepa_whitelist_correspondents FROM fpe.clients WHERE iban=?", 1);
    updateClientBalanceStatement = cass_statement_new("UPDATE fpe.clients SET revision_id=?, balance=? WHERE iban=? IF revision_id=?;", 4);
    updateCLientBalanceErpStatement = cass_statement_new("UPDATE fpe.clients SET revision_id=?, balance_erp=? WHERE iban=? IF revision_id=?;", 4);
    insertClientStatement = cass_statement_new("INSERT INTO fpe.clients (iban, revision_id, balance, balance_erp, status) VALUES(?,?,?,?,?);", 5);
    updateClientCorrespondentWhitelistStatement = cass_statement_new("UPDATE fpe.clients SET sepa_whitelist_correspondents=sepa_whitelist_correspondents+? WHERE iban=?;", 2);
}

ClientDAO::~ClientDAO()
{
    cass_statement_free(selectClientStatement);
    cass_statement_free(updateClientBalanceStatement);
    cass_statement_free(updateCLientBalanceErpStatement);
    cass_statement_free(insertClientStatement);
    cass_statement_free(updateClientCorrespondentWhitelistStatement);
}

Client* ClientDAO::getClient(const std::string& iban)
{
    Client* client = 0;
    if (cass_statement_bind(selectClientStatement, 0, iban) == CASS_OK)
    {
        CassFuture* result_future = cass_session_execute(session, selectClientStatement);
        if (cass_future_error_code(result_future) == CASS_OK)
        {
            if (const CassResult* result = cass_future_get_result(result_future))
            {
                if (const CassRow* row = cass_result_first_row(result))
                {
                    client = get();
                    client->iban = iban;
                    const CassValue* balance_value = cass_row_get_column_by_name(row, "balance");
                    const CassValue* balance_erp_value = cass_row_get_column_by_name(row, "balance_erp");
                    const CassValue* status_value = cass_row_get_column_by_name(row, "status");
                    const CassValue* balance_limit = cass_row_get_column_by_name(row, "balance_limit");
                    const CassValue* revision_id_value = cass_row_get_column_by_name(row, "revision_id");
                    const CassValue* sepa_whitelist_correspondents = cass_row_get_column_by_name(row, "sepa_whitelist_correspondents");

                    cass_value_get_string(status_value, client->status);
                    cass_value_get_string(revision_id_value, client->revision_id);
                    cass_value_get_decimal(balance_value, client->balance);
                    cass_value_get_decimal(balance_erp_value, client->balance_erp);
                    cass_value_get_decimal(balance_limit, client->balance_limit);
                    if (CassIterator* iterator = cass_iterator_from_collection(sepa_whitelist_correspondents))
                    {
                        while (cass_iterator_next(iterator))
                        {
                            const CassValue* ibanValue = cass_iterator_get_value(iterator);
                            std::string iban;
                            cass_value_get_string(ibanValue, iban);
                            client->sepa_whitelist_correspondents.insert(iban);
                        }
                        cass_iterator_free(iterator);
                    }
                }

                cass_result_free(result);
            }
        }
        else
        {
            displayError(result_future, "Unable to run query");
        }
        cass_future_free(result_future);
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Failed to build query to retrieve client " << iban << " from database";
    }
    return client;
}

void ClientDAO::insertClient(Client* client)
{
    client->revision_id = Utils::getUUId();
    CassFuture* result_future = session_execute<std::string, std::string, Decimal, Decimal, std::string>(insertClientStatement,
                                                                                                        client->getIban(),
                                                                                                        client->getRevisionId(),
                                                                                                        client->getBalance(),
                                                                                                        client->getBalanceErp(),
                                                                                                        client->getStatus());
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        BOOST_LOG_TRIVIAL(info) << "Client " << client->getIban() << " successfully inserted in database";
    }
    else
    {
        displayError(result_future, "Unable to run query");
    }
    cass_future_free(result_future);
}

bool ClientDAO::updateClientBalance(Client* client)
{
    const std::string& uuId = Utils::getUUId();
    cass_statement_bind(updateClientBalanceStatement, 0, uuId);
    cass_statement_bind(updateClientBalanceStatement, 1, client->getBalance());
    cass_statement_bind(updateClientBalanceStatement, 2, client->getIban());
    cass_statement_bind(updateClientBalanceStatement, 3, client->getRevisionId());
    bool result = false;
    CassFuture* result_future = cass_session_execute(session, updateClientBalanceStatement);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        BOOST_LOG_TRIVIAL(info) << "Client " << client->getIban()
                                 << " balance " << client->getBalance()
                                 << " successfully updated in database";
        client->revision_id = uuId;
        result = true;
    }
    else
    {
        displayError(result_future, "Unable to run query");
    }
    cass_future_free(result_future);
    return result;
}

bool ClientDAO::updateClientBalanceErp(Client* client)
{
    const std::string& uuId = Utils::getUUId();
    cass_statement_bind(updateCLientBalanceErpStatement, 0, uuId);
    cass_statement_bind(updateCLientBalanceErpStatement, 1, client->getBalanceErp());
    cass_statement_bind(updateCLientBalanceErpStatement, 2, client->getIban());
    cass_statement_bind(updateCLientBalanceErpStatement, 3, client->getRevisionId());
    bool result = false;
    CassFuture* result_future = cass_session_execute(session, updateCLientBalanceErpStatement);
    if (cass_future_error_code(result_future) == CASS_OK)
    {
        BOOST_LOG_TRIVIAL(info) << "Client " << client->getIban()
                                 << " balance erp " << client->getBalanceErp()
                                 << " successfully updated in database";
        client->revision_id = uuId;
        result = true;
    }
    else
    {
        displayError(result_future, "Unable to run query");
    }
    cass_future_free(result_future);
    return result;
}

void ClientDAO::updateClientCorrespondentWhitelist(Client* client)
{
    if (!client->correspondentsToAuthorize.empty())
    {
        cass_statement_bind(updateClientCorrespondentWhitelistStatement, 1, client->getIban());
        CassCollection* correspondents = cass_collection_new(CASS_COLLECTION_TYPE_SET, client->correspondentsToAuthorize.size());
        BOOST_FOREACH(const std::string& iban, client->correspondentsToAuthorize)
        {
            cass_collection_append(correspondents, iban);
        }
        cass_statement_bind(updateClientCorrespondentWhitelistStatement, 0, correspondents);
        CassFuture* result_future = cass_session_execute(session, updateClientCorrespondentWhitelistStatement);
        if (cass_future_error_code(result_future) == CASS_OK)
        {
            client->sepa_whitelist_correspondents.insert(client->correspondentsToAuthorize.begin(),
                                                          client->correspondentsToAuthorize.end());
            client->correspondentsToAuthorize.clear();
            BOOST_LOG_TRIVIAL(info) << "Client " << client->getIban()
                             << " correspondent white list " << boost::algorithm::join(client->getSepaWhitelistCorrespondents(), ",")
                             << " successfully updated in database";
        }
        else
        {
            displayError(result_future, "Unable to run query");
        }
        cass_collection_free(correspondents);
        cass_future_free(result_future);
    }
}
