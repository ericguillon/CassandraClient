/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstring>
#include "constants.h"

const char* Constants::XML_DOCUMENT = "Document";

//Direct debit rejection A1P
const char* Constants::ORIGINAL_GROUP_INFO_AND_STATUS = "OrgnlGrpInfAndSts";
const char* Constants::ORIGINAL_GROUP_INFO = "OrgnlGrpInf";
const char* Constants::ORIGINAL_MESSAGE_ID = "OrgnlMsgId";

const char* Constants::PAYMENT_STATUS_REPORT = "FIToFIPmtStsRpt";
const char* Constants::TRANSACTION_INFORMATION_AND_STATUS = "TxInfAndSts";

const char* Constants::ORIGINAL_END_TO_END_ID = "OrgnlEndToEndId";
const char* Constants::ORIGINAL_TRANSACTION_ID = "OrgnlTxId";
const char* Constants::ORIGINAL_TRANSACTION_REFERENCE = "OrgnlTxRef";

//#Direct debit
const char* Constants::FI_TO_FI_CUSTOMER_DIRECT_DEBIT = "FIToFICstmrDrctDbt";
const char* Constants::DIRECT_DEBIT_TRANSACTION_INFORMATION = "DrctDbtTxInf";

const char* Constants::PAYMENT_ID = "PmtId";
const char* Constants::TRANSACTION_ID = "TxId";
const char* Constants::END_TO_END_ID = "EndToEndId";
const char* Constants::INSTRUCTION_ID = "InstrId";
const char* Constants::RETURN_IDENTIFICATION = "RtrId";
const char* Constants::CANCELLATION_IDENTIFICATION = "CxlId";
const char* Constants::CANCELLATION_STATUS_IDENTIFICATION = "CxlStsId";
const char* Constants::CANCELLATION_STATUS_REASON_INFORMATION = "CxlStsRsnInf";
const char* Constants::STATUS_IDENTIFICATION = "StsId";

const char* Constants::HEADER = "GrpHdr";
const char* Constants::MESSAGE_ID = "MsgId";
const char* Constants::NUMBER_OF_TX = "NbOfTxs";
const char* Constants::INTERBANK_SETTLEMENT_DATE = "IntrBkSttlmDt";
const char* Constants::CREATION_DATE = "CreDtTm";
const char* Constants::ORIGINAL_INTERBANK_SETTLEMENT_DATE = "OrgnlIntrBkSttlmDt";

const char* Constants::INTERBANK_SETTLEMENT_AMOUNT = "IntrBkSttlmAmt";
const char* Constants::ORIGINAL_INTERBANK_SETTLEMENT_AMOUNT = "OrgnlIntrBkSttlmAmt";
const char* Constants::RETURNED_INTERBANK_SETTLEMENT_AMOUNT = "RtrdIntrBkSttlmAmt";
const char* Constants::TOTAL_INTERBANK_SETTLEMENT_AMOUNT = "TtlIntrBkSttlmAmt";
const char* Constants::TOTAL_RETURNED_INTERBANK_SETTLEMENT_AMOUNT = "TtlRtrdIntrBkSttlmAmt";
const char* Constants::SETTLEMENT_CURRENCY = "@Ccy";
const char* Constants::SETTLEMENT_VALUE = "#text";

const char* Constants::CREDITOR = "Cdtr";
const char* Constants::DEBTOR = "Dbtr";
const char* Constants::CREDITOR_ACCOUNT = "CdtrAcct";
const char* Constants::DEBTOR_ACCOUNT = "DbtrAcct";
const char* Constants::INSTRUCTED_AGENT = "InstdAgt";
const char* Constants::INSTRUCTING_AGENT = "InstgAgt";
const char* Constants::CREDITOR_AGENT = "CdtrAgt";
const char* Constants::DEBTOR_AGENT = "DbtrAgt";
const char* Constants::FINANCIAL_INSTITUTION_ID = "FinInstnId";
const char* Constants::ID = "Id";
const char* Constants::IBAN = "IBAN";
const char* Constants::BIC = "BIC";
const char* Constants::NAME = "Nm";
const char* Constants::POSTAL_ADDRESS = "PstlAdr";
const char* Constants::COUNTRY = "Ctry";

const char* Constants::REQUESTED_COLLECTION_DATE = "ReqdColltnDt";
const char* Constants::STATUS_REASON_INFORMATION = "StsRsnInf";
const char* Constants::RETURN_REASON_INFORMATION = "RtrRsnInf";
const char* Constants::REASON = "Rsn";
const char* Constants::CODE = "Cd";

//received transfer
const char* Constants::FI_TO_FI_CUSTOMER_CREDIT_TRANSFER = "FIToFICstmrCdtTrf";
const char* Constants::CREDIT_TRANSFER_TRANSACTION_INFORMATION = "CdtTrfTxInf";

//received transfer rejection
const char* Constants::PAYMENT_RETURN = "PmtRtr";
const char* Constants::TRANSACTION_INFORMATION = "TxInf";

//recall
const char* Constants::FI_TO_FI_PAYMENT_CANCELLATION_REQUEST = "FIToFIPmtCxlReq";
const char* Constants::ASSIGNMENT = "Assgnmt";
const char* Constants::UNDERLYING = "Undrlyg";
const char* Constants::ASSIGNER = "Assgnr";
const char* Constants::ASSIGNEE = "Assgne";
const char* Constants::AGENT = "Agt";
const char* Constants::CONTROL_DATA = "CtrlData";
const char* Constants::CANCELLATION_REASON_INFORMATION = "CxlRsnInf";
const char* Constants::PROPRIETARY = "Prtry";
const char* Constants::ADDITIONAL_INFORMATION = "AddtlInf";

const char* Constants::RESOLUTION_OF_INVESTIGATION = "RsltnOfInvstgtn";
const char* Constants::CANCELLATION_DETAILS = "CxlDtls";

//partial recall
const char* Constants::CHARGES_INFORMATION = "ChrgsInf";
const char* Constants::CHARGES_AMOUNT = "Amt";
const char* Constants::RETURNED_INSTRUCTED_AMOUNT = "RtrdInstdAmt";

const char* Constants::FI_TO_FI_PAYMENT_REVERSAL = "FIToFIPmtRvsl";
const char* Constants::TOTAL_REVERSED_INTERBANK_SETTLEMENT_AMOUNT = "TtlRvsdIntrBkSttlmAmt";
const char* Constants::REVERSAL_IDENTIFICATION = "RvslId";
const char* Constants::REVERSED_INTERBANK_SETTLEMENT_AMOUNT = "RvsdIntrBkSttlmAmt";
const char* Constants::REVERSAL_REASON_INFORMATION = "RvslRsnInf";

const char* Constants::DATE_ISO_FORMAT = "YYYY-mm-DDTHH:MM:SS";
const char* Constants::DATE_STRING_FORMAT = "YYYY-mm-DD";
const int Constants::DATE_STRING_FORMAT_SIZE = strlen(Constants::DATE_STRING_FORMAT);
const char* Constants::MONTH_STRING_FORMAT = "YYYY-mm";
const int Constants::MONTH_STRING_FORMAT_SIZE = strlen(Constants::MONTH_STRING_FORMAT);

