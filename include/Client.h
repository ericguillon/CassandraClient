/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Client.h
 * Author: eric
 *
 * Created on 22 mars 2016, 13:59
 */

#ifndef CLIENT_H
#define CLIENT_H
#include <set>
#include <string>
#include <Decimal.h>

class Client {
public:
    Client();

    ~Client();

    void setBalanceLimit(const Decimal& balance_limit);
    const Decimal& getBalanceLimit() const;
    void setBalanceErp(const Decimal& balance_erp);
    const Decimal& getBalanceErp() const;
    void setBalance(const Decimal& balance);
    const Decimal& getBalance() const;

    const std::set<std::string>& getSepaWhitelistCorrespondents() const;
    void setStatus(const std::string& status);
    const std::string& getStatus() const;
    const std::string& getIban() const;
    const std::string& getRevisionId() const;
    bool isCorrespondentAuthorized(const std::string& iban) const;
    void authorizedCorrespondentIban(const std::string& iban);
    void updateBalanceErp(const Decimal& decimal);
    void updateBalance(const Decimal& decimal);
    void setIban(const std::string& iban)
    {
        this->iban = iban;
    }
    void display() const;

    friend class ClientDAO;
private:
    Client(const Client& orig);

    std::string iban;
    std::string status;
    std::string revision_id;
    std::set<std::string> sepa_whitelist_correspondents;
    std::set<std::string> correspondentsToAuthorize;
    Decimal balance;
    Decimal balance_erp;
    Decimal balance_limit;
};

#endif /* CLIENT_H */

