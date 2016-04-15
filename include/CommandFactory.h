#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
#include <boost/shared_ptr.hpp>
#include <rapidxml.hpp>
#include <cassandra.h>
#include "enums.h"

struct SepaHeader;
class OnHoldOperationHandler;
class ProvionedOperationHandler;

class CommandFactory
{
public:
    virtual ~CommandFactory() {}
    virtual void addCommand(rapidxml::xml_node<>* node,
                            boost::shared_ptr<SepaHeader> sepaHeader) = 0;
    virtual void addCommand(const CassRow* row,
                            cassandra_exemple::OperationType type,
                            cassandra_exemple::OperationStatus status,
                            OnHoldOperationHandler* handler) = 0;
    virtual void addCommand(const CassRow* row,
                            cassandra_exemple::OperationType type,
                            cassandra_exemple::OperationStatus status,
                            ProvionedOperationHandler* handler) = 0;
    virtual void flush(bool stop = false) = 0;
};

#endif // COMMANDFACTORY_H
