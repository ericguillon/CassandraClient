/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OperationDAO.h
 * Author: eric
 *
 * Created on 29 mars 2016, 17:03
 */

#ifndef OPERATIONDAO_H
#define OPERATIONDAO_H
#include <cassandra.h>
#include <vector>
#include "BaseDAO.h"
#include "Factory.h"

class Operation;
class OperationStatus;
class ReservedStatus;
class RejectedStatus;
class OnHoldStatus;
class ProvisionedStatus;
class CancelledStatus;
class AccountedStatus;

class OperationDAO: public BaseDAO,
                    public Factory<Operation>
{
public:
    OperationDAO();
    OperationDAO(const OperationDAO& orig);
    ~OperationDAO();
    
    void getRejectedOperations(std::vector<Operation*>& operations);
    void getOperation(const std::string& month, const std::string& iban, std::vector<Operation*>& operations);
    void getOperation(const std::string& month, const std::string& iban, const std::string& transactionId, std::vector<Operation*>& operations);
    void getOperation(cassandra_exemple::OperationType type, cassandra_exemple::OperationStatus status, std::vector<Operation*>& operations);

    void insertOperation(Operation* operation);
    void updateOperation(Operation* operation);
    
    bool isOperationInserted(Operation* operation);

    void updateOperationStatus(ReservedStatus* status);
    void updateOperationStatus(RejectedStatus* status);
    void updateOperationStatus(OnHoldStatus* status);
    void updateOperationStatus(ProvisionedStatus* status);
    void updateOperationStatus(AccountedStatus* status);
    void updateOperationStatus(CancelledStatus* status);
   
    template <typename T>
    void initializeOperationStatus(T* operationStatus, const CassRow* row);

    OperationStatus* getOperationStatus(cassandra_exemple::OperationStatus operationStatus) const;

protected:
    
private:
    std::vector<OperationStatus*> operationStatuses;
    CassStatement* insertOperationStatement;
    CassStatement* selectOperationStatement;
    CassStatement* selectOperationTypeStatusStatement;
    CassStatement* selectRejectedOperationStatement;
    CassStatement* rejectedOperationStatement;
    CassStatement* provisionedOperationStatement;
    CassStatement* accountedOperationStatement;
};

#endif /* OPERATIONDAO_H */

