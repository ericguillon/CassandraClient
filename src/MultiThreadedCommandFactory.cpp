#include <boost/thread.hpp>
#include "Logger.h"
#include "Thread.h"
#include "OnHoldOperationHandler.h"
#include "ProvionedOperationHandler.h"
#include "ReceivedTransferCommand.h"
#include "ReceivedTransferOnHoldCommand.h"
#include "SepaProvisionedCommand.h"
#include "MultiThreadedCommandFactory.h"

MultiThreadedCommandFactory::MultiThreadedCommandFactory()
: commandQueue(128)
, freeCommandQueue(128)
, freeOnHoldCommandQueue(128)
, freeProvisionedCommandQueue(128)
, nbJobs(0)
{
    unsigned int nb_processor = boost::thread::hardware_concurrency() * 4;
    for (unsigned int i = 0; i < nb_processor; ++i)
    {
        threadPool.create_thread(Thread(this));
    }
}

MultiThreadedCommandFactory::~MultiThreadedCommandFactory()
{
    Command* command;
    while (freeCommandQueue.pop(command))
    {
        delete command;
    }

    while (freeOnHoldCommandQueue.pop(command))
    {
        delete command;
    }
}

void MultiThreadedCommandFactory::addCommand(rapidxml::xml_node<>* node,
                                             boost::shared_ptr<SepaHeader> sepaHeader)
{
    ReceivedTransferCommand* command = get();
    command->sepaHeader = sepaHeader;
    command->node = node;
    commandQueue.push(command);
    nbJobs.fetch_add(1, boost::memory_order_relaxed);
}

void MultiThreadedCommandFactory::addCommand(const CassRow* row,
                                              cassandra_exemple::OperationType type,
                                              cassandra_exemple::OperationStatus status,
                                              OnHoldOperationHandler* handler)
{
    ReceivedTransferOnHoldCommand* command = getOnHoldCommand();
    command->row = row;
    command->status = status;
    command->type = type;
    command->handler = handler;
    commandQueue.push(command);
    nbJobs.fetch_add(1, boost::memory_order_relaxed);
}

void MultiThreadedCommandFactory::addCommand(const CassRow* row,
                                              cassandra_exemple::OperationType type,
                                              cassandra_exemple::OperationStatus status,
                                              ProvionedOperationHandler* handler)
{
    SepaProvisionedCommand* command = getProvisionedCommand();
    command->row = row;
    command->status = status;
    command->type = type;
    command->handler = handler;
    commandQueue.push(command);
    nbJobs.fetch_add(1, boost::memory_order_relaxed);
}

bool MultiThreadedCommandFactory::getCommand(Command*& command)
{
    return commandQueue.pop(command);
}

void MultiThreadedCommandFactory::flush(bool stop)
{
    BOOST_LOG_TRIVIAL(info) << "Flushing commands from thread " << boost::this_thread::get_id();
    Command* command;
    while (getCommand(command))
    {
        command->execute();
        command->accept(this);
    }

    while (nbJobs.load(boost::memory_order_relaxed))
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
    }

    if (stop)
    {
        BOOST_LOG_TRIVIAL(info) << "Sending stop signal :" << boost::this_thread::get_id();
        stopThread();
        threadPool.join_all();
    }
}

void MultiThreadedCommandFactory::release(ReceivedTransferCommand* command)
{
    release(command, freeCommandQueue);
}

void MultiThreadedCommandFactory::release(ReceivedTransferOnHoldCommand* command)
{
    release(command, freeOnHoldCommandQueue);
}

void MultiThreadedCommandFactory::release(SepaProvisionedCommand* command)
{
    release(command, freeProvisionedCommandQueue);
}

ReceivedTransferCommand* MultiThreadedCommandFactory::get()
{
    return get(freeCommandQueue);
}

ReceivedTransferOnHoldCommand* MultiThreadedCommandFactory::getOnHoldCommand()
{
    return get(freeOnHoldCommandQueue);
}

SepaProvisionedCommand* MultiThreadedCommandFactory::getProvisionedCommand()
{
    return get(freeProvisionedCommandQueue);
}
