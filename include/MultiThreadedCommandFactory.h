#ifndef MULTITHREADEDCOMMANDFACTORY_H
#define MULTITHREADEDCOMMANDFACTORY_H
#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/signals2.hpp>
#include "CommandFactory.h"

class Command;
class ReceivedTransferCommand;
class ReceivedTransferOnHoldCommand;
class SepaProvisionedCommand;

class MultiThreadedCommandFactory : public CommandFactory
{
public:
    MultiThreadedCommandFactory();
    ~MultiThreadedCommandFactory();

    void addCommand(rapidxml::xml_node<>* node,
                    boost::shared_ptr<SepaHeader> sepaHeader);
    void addCommand(const CassRow* row,
                      cassandra_exemple::OperationType type,
                      cassandra_exemple::OperationStatus status,
                      OnHoldOperationHandler* handler);
    void addCommand(const CassRow* row,
                      cassandra_exemple::OperationType type,
                      cassandra_exemple::OperationStatus status,
                      ProvionedOperationHandler* handler);

    bool getCommand(Command*& command);
    void release(ReceivedTransferCommand* command);
    void release(ReceivedTransferOnHoldCommand* command);
    void release(SepaProvisionedCommand* command);

    void flush(bool stop = false);
    bool isJobsDone() const
    {
        return nbJobs == 0;
    }
    boost::signals2::signal<void ()> stopThread;
protected:
    ReceivedTransferCommand* get();
    ReceivedTransferOnHoldCommand* getOnHoldCommand();
    SepaProvisionedCommand* getProvisionedCommand();

    template <typename T>
    T * get(boost::lockfree::queue<T*>& freeQueue)
    {
        T* command;
        if (!freeQueue.pop(command))
        {
            command = new T;
        }
        return command;
    }

    template <typename T>
    void release(T* command, boost::lockfree::queue<T*>& freeQueue)
    {
        freeQueue.push(command);
        nbJobs.fetch_sub(1, boost::memory_order_release);
    }

protected:

    boost::lockfree::queue<Command*>                            commandQueue;
    boost::lockfree::queue<ReceivedTransferCommand*>            freeCommandQueue;
    boost::lockfree::queue<ReceivedTransferOnHoldCommand*>      freeOnHoldCommandQueue;
    boost::lockfree::queue<SepaProvisionedCommand*>             freeProvisionedCommandQueue;

    boost::thread_group threadPool;
    boost::atomics::atomic_int32_t nbJobs;

private:
};

#endif // MULTITHREADEDCOMMANDFACTORY_H
