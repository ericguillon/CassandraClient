#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "Command.h"
#include "OperationStatusFactory.h"
#include "MultiThreadedCommandFactory.h"

template <typename T, typename OperationFactory>
class BaseCommand : public Command
{
public:
    BaseCommand()
    {
        statusFactory = new OperationStatusFactory;
        factory = new OperationFactory(statusFactory);
    }

    ~BaseCommand()
    {
        delete statusFactory;
        delete factory;
    }

    void accept(MultiThreadedCommandFactory* commandFactory)
    {
        commandFactory->release(static_cast<T*>(this));
    }

protected:
    OperationStatusFactory* statusFactory;
    OperationFactory* factory;
};

#endif // BASECOMMAND_H
