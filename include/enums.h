/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enums.h
 * Author: eric
 *
 * Created on 22 mars 2016, 11:23
 */

#ifndef ENUMS_H
#define ENUMS_H

namespace cassandra_exemple
{
    enum CompteType
    {
        client = 0,
        correspondent,
        end  
    };
    
    enum OperationDirection
    {
        debit = -1,
        credit = 1
    };
    
    static const char* toString(OperationDirection direction)
    {
        const char* directionString;
        switch(direction)
        {
            case debit:
                directionString = "DEBIT";
                break;
            case credit:
                directionString = "CREDIT";
                break;
        }
        return directionString;
    }
    
    static OperationDirection getOperationDirection(const std::string& directionString)
    {
        if (directionString == "DEBIT")
            return debit;
        if (directionString == "CREDIT")
            return credit;
    }
    
    enum OperationStatus
    {
        undefined = -1,
        reserved = 0,
        onHold,
        provisioned,
        accounted,
        cancelled,
        rejected
    };
    
    static const char* toString(OperationStatus status)
    {
        const char* statusString;
        switch(status)
        {
            case reserved:
                statusString = "RESERVEE";
                break;
            case onHold:
                statusString = "MISE_EN_ATTENTE";
                break;
            case provisioned:
                statusString = "PROVISIONNEE";
                break;
            case accounted:
                statusString = "COMPTABILISEE";
                break;
            case cancelled:
                statusString = "ANNULEE";
                break;
            case rejected:
                statusString = "REJETEE";
                break;
            default:
                statusString = "INCONNUE";
        }
        return statusString;
    }
    
    static OperationStatus getOperationStatus(const std::string& statusString)
    {
        if (statusString == "RESERVEE")
            return reserved;
        if (statusString == "MISE_EN_ATTENTE")
            return onHold;
        if (statusString == "PROVISIONNEE")
            return provisioned;
        if (statusString == "COMPTABILISEE")
            return accounted;
        if (statusString == "ANNULEE")
            return cancelled;
        if (statusString == "REJETEE")
            return rejected;
        if (statusString == "INCONNUE")
            return undefined;
        return undefined;
    }
    
    enum AccountStatus
    {
        opened = 0,
        closed,
        globalBlocked,
        creditBlocked,
        debitBlocked
    };
    
    static const char* toString(AccountStatus accountStatus)
    {
        const char* statusString;
        switch(accountStatus)
        {
            case opened:
                statusString = "compte_ouvert";
                break;
            case closed:
                statusString = "compte_ferme";
                break;
            case globalBlocked:
                statusString = "compte_bloque";
                break;
            case creditBlocked:
                statusString = "compte_bloque_credit";
                break;
            case debitBlocked:
                statusString = "compte_bloque_debit";
                break;
        }
        return statusString;
    }
    
    static AccountStatus getAccountStatus(const std::string& statusString)
    {
        if (statusString == "compte_ouvert")
            return opened;
        if (statusString == "compte_ferme")
            return closed;
        if (statusString == "compte_bloque")
            return globalBlocked;
        if (statusString == "compte_bloque_credit")
            return creditBlocked;
        if (statusString == "compte_bloque_debit")
            return debitBlocked;
        return opened;
    }
    
    enum OperationCanal
    {
        mastercard = 0,
        sepa,
        on_us
    };
    
    static const char* toString(OperationCanal canal)
    {
        const char* canalString;
        switch (canal)
        {
            case mastercard:
                canalString = "MASTERCARD";
                break;
            case sepa:
                canalString = "SEPA";
                break;
            case on_us:
                canalString = "ON_US";
                break;
        }
        return canalString;
    }
    
    static OperationCanal getOperationCanal(const std::string& canalString)
    {
        if (canalString == "MASTERCARD")
            return mastercard;
        if (canalString == "SEPA")
            return sepa;
        if (canalString == "ON_US")
            return on_us;
        return sepa;
    }
    
    enum OperationSubCanal
    {
        mastercard_proxi_payment = 0,
        mastercard_vad_payment,
        mastercard_atm_withdrawal,
        mastercard_counter_withdrawal,
        mastercard_almost_cash,
        sepa_received_transfer,
        sepa_emitted_transfer,
        sepa_sdd_direct_debit,
        sepa_sepa_b2b_direct_debit,
        on_us_fees,
        on_us_various_operations
    };
    
    static const char* toString(OperationSubCanal subCanal)
    {
        const char* subCanalString;
        switch (subCanal)
        {
            case mastercard_proxi_payment:
                subCanalString = "PROXI_PAYMENT";
                break;
            case mastercard_vad_payment:
                subCanalString = "VAD_PAYMENT";
                break;
            case mastercard_atm_withdrawal:
                subCanalString = "ATM_WITHDRAWAL";
                break;
            case mastercard_counter_withdrawal:
                subCanalString = "COUNTER_WITHDRAWAL";
                break;
            case mastercard_almost_cash:
                subCanalString = "ALMOST_CASH";
                break;
            case sepa_received_transfer:
                subCanalString = "RECEIVED_TRANSFER";
                break;
            case sepa_emitted_transfer:
                subCanalString = "EMITTED_TRANSFER";
                break;
            case sepa_sdd_direct_debit:
                subCanalString = "SDD_DIRECT_DEBIT";
                break;
            case sepa_sepa_b2b_direct_debit:
                subCanalString = "B2B_DIRECT_DEBIT";
                break;
            case on_us_fees:
                subCanalString = "FEES";
                break;
            case on_us_various_operations:
                subCanalString = "VARIOUS_OPERATIONS";
                break;
        }
        return subCanalString;
    }
    
    static OperationSubCanal getOperationSubCanal(const std::string& subCanalString)
    {
        if (subCanalString == "PROXI_PAYMENT")
            return mastercard_proxi_payment;
        if (subCanalString == "VAD_PAYMENT")
            return mastercard_vad_payment;
        if (subCanalString == "ATM_WITHDRAWAL")
            return mastercard_atm_withdrawal;
        if (subCanalString == "COUNTER_WITHDRAWAL")
            return mastercard_counter_withdrawal;
        if (subCanalString == "ALMOST_CASH")
            return mastercard_almost_cash;
        if (subCanalString == "RECEIVED_TRANSFER")
            return sepa_received_transfer;
        if (subCanalString == "EMITTED_TRANSFER")
            return sepa_emitted_transfer;
        if (subCanalString == "SDD_DIRECT_DEBIT")
            return sepa_sdd_direct_debit;
        if (subCanalString == "B2B_DIRECT_DEBIT")
            return sepa_sepa_b2b_direct_debit;
        if (subCanalString == "FEES")
            return on_us_fees;
        if (subCanalString == "VARIOUS_OPERATIONS")
            return on_us_various_operations;
    }
    
    enum OperationType
    {
        card_payment = 0,
        card_payment_refund,
        card_payment_cancellation,
        unpaid_card_payment,
        atm_withdrawal,
        atm_withdrawal_refund,
        atm_withdrawal_cancellation,
        unpaid_atm_withdrawal,
        counter_withdrawal,
        counter_withdrawal_refund,
        counter_withdrawal_cancellation,
        unpaid_counter_withdrawal,
        quasi_cash,
        quasi_cash_refund,
        quasi_cash_cancellation,
        quasi_cash_unpaid,
        sepa_received_transfer_operation,
        sepa_received_transfer_rejection,
        sepa_received_transfer_refund,
        sepa_received_transfer_cancellation,
        sepa_emitted_transfer_operation,
        sepa_emitted_transfer_rejection,
        sepa_emitted_transfer_refund,
        sepa_emitted_transfer_cancellation,
        sepa_sdd_direct_debit_operation,
        sepa_sdd_direct_debit_rejection,
        sepa_sdd_direct_debit_refund,
        sepa_sdd_direct_debit_cancellation,
        sepa_b2b_direct_debit_operation,
        sepa_b2b_direct_debit_rejection,
        on_us_subscription,
        on_us_subscription_deposit,
        on_us_transfer,
        on_us_deposit,
        on_us_withdrawal,
        on_us_payment,
        on_us_fees_replacement,
        on_us_fees_on_demand,
        on_us_fees_yearly_subscription,
        on_us_fees_sms_agreement,
        on_us_fees_search,
        on_us_fees_irregular_use,
        on_us_fees_other,
        on_us_various_refund
    };
    
    static const char* toString(OperationType type)
    {
        const char* typeString;
        switch (type)
        {
            case card_payment:
                typeString = "CARD_PAYMENT";
                break;
            case card_payment_refund:
                typeString = "CARD_PAYMENT_REFUND";
                break;
            case card_payment_cancellation:
                typeString = "CARD_PAYMENT_CANCELLATION";
                break;
            case unpaid_card_payment:
                typeString = "UNPAID_CARD_PAYMENT";
                break;
            case atm_withdrawal:
                typeString = "ATM_WITHDRAWAL";
                break;
            case atm_withdrawal_refund:
                typeString = "ATM_WITHDRAWAL_REFUND";
                break;
            case atm_withdrawal_cancellation:
                typeString = "ATM_WITHDRAWAL_CANCELLATION";
                break;
            case unpaid_atm_withdrawal:
                typeString = "UNPAID_ATM_WITHDRAWAL";
                break;
            case counter_withdrawal:
                typeString = "COUNTER_WITHDRAWAL";
                break;
            case counter_withdrawal_refund:
                typeString = "COUNTER_WITHDRAWAL_REFUND";
                break;
            case counter_withdrawal_cancellation:
                typeString = "COUNTER_WITHDRAWAL_CANCELLATION";
                break;
            case unpaid_counter_withdrawal:
                typeString = "UNPAID_COUNTER_WITHDRAWAL";
                break;
            case quasi_cash:
                typeString = "QUASI_CASH";
                break;
            case quasi_cash_refund:
                typeString = "QUASI_CASH_REFUND";
                break;
            case quasi_cash_cancellation:
                typeString = "QUASI_CASH_CANCELLATION";
                break;
            case quasi_cash_unpaid:
                typeString = "QUASI_CASH_UNPAID";
                break;
            case sepa_received_transfer_operation:
                typeString = "RECEIVED_TRANSFER";
                break;
            case sepa_received_transfer_rejection:
                typeString = "RECEIVED_TRANSFER_REJECTION";
                break;
            case sepa_received_transfer_refund:
                typeString = "RECEIVED_TRANSFER_REFUND";
                break;
            case sepa_received_transfer_cancellation:
                typeString = "RECEIVED_TRANSFER_CANCELLATION";
                break;
            case sepa_emitted_transfer_operation:
                typeString = "EMITTED_TRANSFER";
                break;
            case sepa_emitted_transfer_rejection:
                typeString = "EMITTED_TRANSFER_REJECTION";
                break;
            case sepa_emitted_transfer_refund:
                typeString = "EMITTED_TRANSFER_REFUND";
                break;
            case sepa_emitted_transfer_cancellation:
                typeString = "EMITTED_TRANSFER_CANCELLATION";
                break;
            case sepa_sdd_direct_debit_operation:
                typeString = "SDD_DIRECT_DEBIT";
                break;
            case sepa_sdd_direct_debit_rejection:
                typeString = "SDD_DIRECT_DEBIT_REJECTION";
                break;
            case sepa_sdd_direct_debit_refund:
                typeString = "SDD_DIRECT_DEBIT_REFUND";
                break;
            case sepa_sdd_direct_debit_cancellation:
                typeString = "SDD_DIRECT_DEBIT_CANCELLATION";
                break;
            case sepa_b2b_direct_debit_operation:
                typeString = "B2B_DIRECT_DEBIT";
                break;
            case sepa_b2b_direct_debit_rejection:
                typeString = "B2B_DIRECT_DEBIT_REJECTION";
                break;
            case on_us_subscription:
                typeString = "ON_US_SUBSCRIPTION";
                break;
            case on_us_subscription_deposit:
                typeString = "ON_US_SUBSCRIPTION_DEPOSIT";
                break;
            case on_us_transfer:
                typeString = "ON_US_TRANSFER";
                break;
            case on_us_deposit:
                typeString = "ON_US_DEPOSIT";
                break;
            case on_us_withdrawal:
                typeString = "ON_US_WITHDRAWAL";
                break;
            case on_us_payment:
                typeString = "ON_US_PAYMENT";
                break;
            case on_us_fees_replacement:
                typeString = "ON_US_FEE_REPLACEMENT";
                break;
            case on_us_fees_on_demand:
                typeString = "ON_US_FEES_ON_DEMAND";
                break;
            case on_us_fees_yearly_subscription:
                typeString = "ON_US_FEES_YEARLY_SUBSCRIPTION";
                break;
            case on_us_fees_sms_agreement:
                typeString = "ON_US_FEES_SMS_AGREEMENT";
                break;
            case on_us_fees_search:
                typeString = "ON_US_FEES_SEARCH";
                break;
            case on_us_fees_irregular_use:
                typeString = "ON_US_FEES_IRREGULAR_USE";
                break;
            case on_us_fees_other:
                typeString = "ON_US_FEES_OTHER";
                break;
            case on_us_various_refund:
                typeString = "ON_US_VARIOUS_REFUND";
                break;
        }
        return typeString;
    }
    
    static OperationType getOperationType(const std::string& operationString)
    {
        if (operationString == "CARD_PAYMENT")
            return card_payment;
        if  (operationString == "CARD_PAYMENT_REFUND")
            return card_payment_refund;    
        if (operationString == "CARD_PAYMENT_CANCELLATION")
            return card_payment_cancellation;
        if (operationString == "UNPAID_CARD_PAYMENT")
            return unpaid_card_payment;
        if (operationString == "ATM_WITHDRAWAL")
            return atm_withdrawal;
        if (operationString == "ATM_WITHDRAWAL_REFUND")
            return atm_withdrawal_refund;
        if (operationString == "ATM_WITHDRAWAL_CANCELLATION")
            return atm_withdrawal_cancellation;
        if (operationString == "UNPAID_ATM_WITHDRAWAL")
            return unpaid_atm_withdrawal;
        if (operationString == "COUNTER_WITHDRAWAL")
            return counter_withdrawal;
        if (operationString == "COUNTER_WITHDRAWAL_REFUND")
            return counter_withdrawal_refund;
        if (operationString == "COUNTER_WITHDRAWAL_CANCELLATION")
            return counter_withdrawal_cancellation;
        if (operationString == "UNPAID_COUNTER_WITHDRAWAL")
            return unpaid_counter_withdrawal;
        if (operationString == "QUASI_CASH")
            return quasi_cash;
        if (operationString == "QUASI_CASH_REFUND")
            return quasi_cash_refund;
        if (operationString == "QUASI_CASH_CANCELLATION")
            return quasi_cash_cancellation;
        if (operationString == "QUASI_CASH_UNPAID")
            return quasi_cash_unpaid;
        if (operationString == "RECEIVED_TRANSFER")
            return sepa_received_transfer_operation;
        if (operationString == "RECEIVED_TRANSFER_REJECTION")
            return sepa_received_transfer_rejection;
        if (operationString == "RECEIVED_TRANSFER_REFUND")
            return sepa_received_transfer_refund;
        if (operationString == "RECEIVED_TRANSFER_CANCELLATION")
            return sepa_received_transfer_cancellation;
        if (operationString == "EMITTED_TRANSFER")
            return sepa_emitted_transfer_operation;
        if (operationString == "EMITTED_TRANSFER_REJECTION")
            return sepa_emitted_transfer_rejection;
        if (operationString == "EMITTED_TRANSFER_REFUND")
            return sepa_emitted_transfer_refund;
        if (operationString == "EMITTED_TRANSFER_CANCELLATION")
            return sepa_emitted_transfer_cancellation;
        if (operationString == "SDD_DIRECT_DEBIT")
            return sepa_sdd_direct_debit_operation;
        if (operationString == "SDD_DIRECT_DEBIT_REJECTION")
            return sepa_sdd_direct_debit_rejection;
        if (operationString == "SDD_DIRECT_DEBIT_REFUND")
            return sepa_sdd_direct_debit_refund;
        if (operationString == "SDD_DIRECT_DEBIT_CANCELLATION")
            return sepa_sdd_direct_debit_cancellation;
        if (operationString == "B2B_DIRECT_DEBIT")
            return sepa_b2b_direct_debit_operation;
        if (operationString == "B2B_DIRECT_DEBIT_REJECTION")
            return sepa_b2b_direct_debit_rejection;
        if (operationString == "ON_US_SUBSCRIPTION")
            return on_us_subscription;
        if (operationString == "ON_US_SUBSCRIPTION_DEPOSIT")
            return on_us_subscription_deposit;
        if (operationString == "ON_US_TRANSFER")
            return on_us_transfer;
        if (operationString == "ON_US_DEPOSIT")
            return on_us_deposit;
        if (operationString == "ON_US_WITHDRAWAL")
            return on_us_withdrawal;
        if (operationString == "ON_US_PAYMENT")
            return on_us_payment;
        if (operationString == "ON_US_FEE_REPLACEMENT")
            return on_us_fees_replacement;
        if (operationString == "ON_US_FEES_ON_DEMAND")
            return on_us_fees_on_demand;
        if (operationString == "ON_US_FEES_YEARLY_SUBSCRIPTION")
            return on_us_fees_yearly_subscription;
        if (operationString == "ON_US_FEES_SMS_AGREEMENT")
            return on_us_fees_sms_agreement;
        if (operationString == "ON_US_FEES_SEARCH")
            return on_us_fees_search;
        if (operationString == "ON_US_FEES_IRREGULAR_USE")
            return on_us_fees_irregular_use;
        if (operationString == "ON_US_FEES_OTHER")
            return on_us_fees_other;
        if (operationString == "ON_US_VARIOUS_REFUND")
            return on_us_various_refund;
        return sepa_received_transfer_operation;
    }
    enum RejectionCode
    {
        client_status = 0,
        insufficient_balance,
        limit_reached,
        sdd_direct_debit_mandate,
        dcirc_validation,
        aml_validation,
        sab_received_transfer_rejection,
        sab_sdd_direct_debit_rejection
    };
    
    static const char* toString(RejectionCode rejectionCode)
    {
        const char* rejectionString;
        switch (rejectionCode)
        {
            case client_status:
                rejectionString = "05";
                break;
            case insufficient_balance:
                rejectionString = "51";
                break;
            case limit_reached:
                rejectionString = "61";
                break;
            case sdd_direct_debit_mandate:
                rejectionString = "00";
                break;
            case dcirc_validation:
                rejectionString = "00";
                break;
            case aml_validation:
                rejectionString = "00";
                break;
            case sab_received_transfer_rejection:
                rejectionString = "00";
                break;
            case sab_sdd_direct_debit_rejection:
                rejectionString = "00";
                break;
        }
        return rejectionString;
    }
    
    static RejectionCode getRejectionCode(const std::string& rejectionString)
    {
        if (rejectionString == "05")
            return client_status;
        if (rejectionString == "51")
            return insufficient_balance;
        if (rejectionString == "61")
            return limit_reached;
        if (rejectionString == "00")
            return sdd_direct_debit_mandate;
        if (rejectionString == "00")
            return dcirc_validation;
        if (rejectionString == "00")
            return aml_validation;
        if (rejectionString == "00")
            return sab_received_transfer_rejection;
        if (rejectionString == "00")
            return sab_sdd_direct_debit_rejection;
    }
    
    enum EventType
    {
        sepa_integration = 0,
        sepa_settlement_date,
        sepa_aml_validation,
        sepa_dcirc_validation,
        sepa_erp_integration,
        balance_event,
        balance_erp_event,
        user_cancellation,
        sepa_refund,
        sepa_cancellation,
        sab_cancellation,
        sab_rejection,
    };
    
    static const char* toString(EventType eventType)
    {
        const char* eventTypeStr;
        switch(eventType)
        {
            case sepa_integration:
                eventTypeStr = "INTEGRATION";
                break;
            case sepa_settlement_date:
                eventTypeStr = "DATE_PAIEMENT";
                break;
            case sepa_aml_validation:
                eventTypeStr = "VALIDATION_AML";
                break;
            case sepa_dcirc_validation:
                eventTypeStr = "VALIDATION_DCIRC";
                break;
            case sepa_erp_integration:
                eventTypeStr = "INTEGRATION_ERP";
                break;
            case balance_event:
                eventTypeStr = "BALANCE_EVENT";
                break;
            case balance_erp_event:
                eventTypeStr = "BALANCE_ERP_EVENT";
                break;
            case user_cancellation:
                eventTypeStr = "USER_CANCELLATION";
                break;
            case sepa_refund:
                eventTypeStr = "SEPA_REFUND";
                break;
            case sepa_cancellation:
                eventTypeStr = "SEPA_CANCELLATION";
                break;
            case sab_cancellation:
                eventTypeStr = "SAB_CANCELLATION";
                break;
            case sab_rejection:
                eventTypeStr = "SAB_REJECTION";
                break;
            default:
                ;
        }
        return eventTypeStr;
    }
}

#endif /* ENUMS_H */

