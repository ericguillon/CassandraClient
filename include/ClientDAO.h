/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ClientDAO.h
 * Author: eric
 *
 * Created on 22 mars 2016, 16:12
 */

#ifndef CLIENTDAO_H
#define CLIENTDAO_H
#include <string>
#include <cassandra.h>
#include "BaseDAO.h"
#include "Factory.h"
#include "CassandraUtils.h"


class Client;

class ClientDAO: public BaseDAO,
                 public CassandraUtils,
                 public Factory<Client>
{
public:
    ClientDAO();
    ~ClientDAO();

    Client* getClient(const std::string& iban);

    void insertClient(Client* client);
    void updateClientCorrespondentWhitelist(Client* client);
    bool updateClientBalance(Client* client);
    bool updateClientBalanceErp(Client* client);

protected:

private:
    CassStatement* insertClientStatement;
    CassStatement* selectClientStatement;
    CassStatement* updateClientBalanceStatement;
    CassStatement* updateCLientBalanceErpStatement;
    CassStatement* updateClientCorrespondentWhitelistStatement;
};

#endif /* CLIENTDAO_H */

