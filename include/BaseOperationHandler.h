#ifndef BASEOPERATIONHANDLER_H
#define BASEOPERATIONHANDLER_H
#include <boost/thread.hpp>
#include <OperationHandler.h>
#include "CommandFactory.h"

template <typename T>
class BaseOperationHandler : public OperationHandler
{
public:
    void onResultAvailable(const CassRow* row,
                            cassandra_exemple::OperationType type,
                            cassandra_exemple::OperationStatus status)
    {
        done = false;
        factory->addCommand(row, type, status, static_cast<T*>(this));
        while (!done)
        {
            boost::this_thread::sleep_for(boost::chrono::microseconds(10));
        }
    }

    void flush()
    {
        factory->flush();
    }
protected:
    BaseOperationHandler(CommandFactory* factory_)
    : factory(factory_)
    {}
    CommandFactory* factory;
};

#endif // BASEOPERATIONHANDLER_H
