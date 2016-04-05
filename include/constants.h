/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   constants.h
 * Author: eric
 *
 * Created on 24 mars 2016, 16:20
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
public:
    static const char* XML_DOCUMENT;

    //Direct debit rejection A1P
    static const char* ORIGINAL_GROUP_INFO_AND_STATUS;
    static const char* ORIGINAL_GROUP_INFO;
    static const char* ORIGINAL_MESSAGE_ID;

    static const char* PAYMENT_STATUS_REPORT;
    static const char* TRANSACTION_INFORMATION_AND_STATUS;

    static const char* ORIGINAL_END_TO_END_ID;
    static const char* ORIGINAL_TRANSACTION_ID;
    static const char* ORIGINAL_TRANSACTION_REFERENCE;

    //#Direct debit
    static const char* FI_TO_FI_CUSTOMER_DIRECT_DEBIT;
    static const char* DIRECT_DEBIT_TRANSACTION_INFORMATION;

    static const char* PAYMENT_ID;
    static const char* TRANSACTION_ID;
    static const char* END_TO_END_ID;
    static const char* INSTRUCTION_ID;
    static const char* RETURN_IDENTIFICATION;
    static const char* CANCELLATION_IDENTIFICATION;
    static const char* CANCELLATION_STATUS_IDENTIFICATION;
    static const char* CANCELLATION_STATUS_REASON_INFORMATION;
    static const char* STATUS_IDENTIFICATION;

    static const char* HEADER;
    static const char* MESSAGE_ID;
    static const char* NUMBER_OF_TX;
    static const char* INTERBANK_SETTLEMENT_DATE;
    static const char* CREATION_DATE;
    static const char* ORIGINAL_INTERBANK_SETTLEMENT_DATE;

    static const char* INTERBANK_SETTLEMENT_AMOUNT;
    static const char* ORIGINAL_INTERBANK_SETTLEMENT_AMOUNT;
    static const char* RETURNED_INTERBANK_SETTLEMENT_AMOUNT;
    static const char* TOTAL_INTERBANK_SETTLEMENT_AMOUNT;
    static const char* TOTAL_RETURNED_INTERBANK_SETTLEMENT_AMOUNT;
    static const char* SETTLEMENT_CURRENCY;
    static const char* SETTLEMENT_VALUE;

    static const char* CREDITOR;
    static const char* DEBTOR;
    static const char* CREDITOR_ACCOUNT;
    static const char* DEBTOR_ACCOUNT;
    static const char* INSTRUCTED_AGENT;
    static const char* INSTRUCTING_AGENT;
    static const char* CREDITOR_AGENT;
    static const char* DEBTOR_AGENT;
    static const char* FINANCIAL_INSTITUTION_ID;
    static const char* ID;
    static const char* IBAN;
    static const char* BIC;
    static const char* NAME;
    static const char* POSTAL_ADDRESS;
    static const char* COUNTRY;

    static const char* REQUESTED_COLLECTION_DATE;
    static const char* STATUS_REASON_INFORMATION;
    static const char* RETURN_REASON_INFORMATION;
    static const char* REASON;
    static const char* CODE;

    //received transfer
    static const char* FI_TO_FI_CUSTOMER_CREDIT_TRANSFER;
    static const char* CREDIT_TRANSFER_TRANSACTION_INFORMATION;

    //received transfer rejection
    static const char* PAYMENT_RETURN;
    static const char* TRANSACTION_INFORMATION;

    //recall
    static const char* FI_TO_FI_PAYMENT_CANCELLATION_REQUEST;
    static const char* ASSIGNMENT;
    static const char* UNDERLYING;
    static const char* ASSIGNER;
    static const char* ASSIGNEE;
    static const char* AGENT;
    static const char* CONTROL_DATA;
    static const char* CANCELLATION_REASON_INFORMATION;
    static const char* PROPRIETARY;
    static const char* ADDITIONAL_INFORMATION;

    static const char* RESOLUTION_OF_INVESTIGATION;
    static const char* CANCELLATION_DETAILS;

    //partial recall
    static const char* CHARGES_INFORMATION;
    static const char* CHARGES_AMOUNT;
    static const char* RETURNED_INSTRUCTED_AMOUNT;

    static const char* FI_TO_FI_PAYMENT_REVERSAL;
    static const char* TOTAL_REVERSED_INTERBANK_SETTLEMENT_AMOUNT;
    static const char* REVERSAL_IDENTIFICATION;
    static const char* REVERSED_INTERBANK_SETTLEMENT_AMOUNT;
    static const char* REVERSAL_REASON_INFORMATION;
    
    static const char* DATE_STRING_FORMAT;
    static const char* DATE_ISO_FORMAT;
    static const char* MONTH_STRING_FORMAT;
    static const int   DATE_STRING_FORMAT_SIZE;
    static const int   MONTH_STRING_FORMAT_SIZE;
};

#endif /* CONSTANTS_H */

