#ifndef OPERATIONHANDLER_H
#define OPERATIONHANDLER_H
#include <cassandra.h>
#include "enums.h"


class OperationHandler
{
public:
    virtual ~OperationHandler() {}
    virtual void onResultAvailable(const CassRow* row,
                                   cassandra_exemple::OperationType type,
                                   cassandra_exemple::OperationStatus status) = 0;
    virtual void flush() = 0;
    void setDone()
    {
        done = true;
    }
protected:
    bool done;
};

#endif // OPERATIONHANDLER_H
