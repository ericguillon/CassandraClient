#include "constants.h"
#include "Operation.h"
#include "SepaOperationFactory.h"

SepaOperationFactory::SepaOperationFactory(OperationStatusFactory* operationStatusFactory)
: OperationFactory(operationStatusFactory)
{
    creditorAgent.type = Constants::CREDITOR_AGENT;
    creditorAgent.name = Constants::CREDITOR;
    creditorAgent.account = Constants::CREDITOR_ACCOUNT;

    debtorAgent.type = Constants::DEBTOR_AGENT;
    debtorAgent.name = Constants::DEBTOR;
    debtorAgent.account = Constants::DEBTOR_ACCOUNT;
}

void SepaOperationFactory::decodeField(char*& field, XmlNode* node)
{
    field = node->value();
}

void SepaOperationFactory::decodeField(std::string& field, XmlNode* node)
{
    field = node->value();
}

void SepaOperationFactory::decodeField(boost::posix_time::ptime& dateField, XmlNode* node)
{
    std::string value(node->value());
    if (node->value_size() == Constants::DATE_STRING_FORMAT_SIZE)
    {
        value += "T00:00:00";
    }
    dateField = boost::date_time::parse_delimited_time<boost::posix_time::ptime>(value, 'T');
}

void SepaOperationFactory::fillIds(Operation* operation, XmlNode* node)
{
    if (XmlNode* paymentIdenticationNode = node->first_node(Constants::PAYMENT_ID))
    {
        if (XmlNode* node = paymentIdenticationNode->first_node(Constants::TRANSACTION_ID))
        {
            std::string transactionId;
            decodeField(transactionId, node);
            operation->setTransactionId(transactionId);
        }
    }
}

void SepaOperationFactory::fillCompte(Compte& compte, const Agent& agent, XmlNode* node)
{
    if (XmlNode* agentTypeNode = node->first_node(agent.type))
    {
        if (XmlNode* financialInstitutionNode = agentTypeNode->first_node(Constants::FINANCIAL_INSTITUTION_ID))
        {
            if (XmlNode* bicNode = financialInstitutionNode->first_node(Constants::BIC))
            {
                decodeField(compte.bic, bicNode);
            }
        }
    }

    if (XmlNode* agentAccountNode = node->first_node(agent.account))
    {
        if (XmlNode* idNode = agentAccountNode->first_node(Constants::ID))
        {
            if (XmlNode* ibanNode = idNode->first_node(Constants::IBAN))
            {
                decodeField(compte.iban, ibanNode);
            }
        }
    }
}


