#ifndef SEPAOPERATIONFACTORY_H
#define SEPAOPERATIONFACTORY_H
#include <string>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <rapidxml.hpp>
#include <OperationFactory.h>

typedef rapidxml::xml_node<> XmlNode;

class Operation;
struct Compte;

struct Agent
{
    const char* type;
    const char* name;
    const char* account;
};

class SepaOperationFactory : public OperationFactory
{
protected:
    SepaOperationFactory(OperationStatusFactory* operationStatusFactory);
    void fillIds(Operation* operation, XmlNode* node);
    void fillCompte(Compte& compte, const Agent& agent, XmlNode* node);
    void decodeField(char*& field, XmlNode* node);
    void decodeField(std::string& field, XmlNode* node);
    void decodeField(boost::posix_time::ptime& dateField, XmlNode* node);

protected:
    Agent creditorAgent;
    Agent debtorAgent;
};

#endif // SEPAOPERATIONFACTORY_H
