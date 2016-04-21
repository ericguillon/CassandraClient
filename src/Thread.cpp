#include <boost/thread.hpp>
#include "Command.h"
#include "MultiThreadedCommandFactory.h"
#include "Logger.h"
#include "Thread.h"

static const boost::chrono::microseconds timeToSleep( 40000 );

Thread::Thread(MultiThreadedCommandFactory* factory_)
: started(true)
, factory(factory_)
{
    factory->stopThread.connect(boost::bind(&Thread::stop, this));
}

Thread::Thread(const Thread& other)
: started(other.started)
, factory(other.factory)
{
    factory->stopThread.connect(boost::bind(&Thread::stop, this));
}

Thread::~Thread()
{
    factory->stopThread.disconnect(this);
}

void Thread::operator()()
{
    BOOST_LOG_TRIVIAL(info) << "Starting thread :" << boost::this_thread::get_id();
    while (started)
    {
        Command* command;
        if (factory->getCommand(command))
        {
            command->execute();
            command->accept(factory);
        }
        else
        {
            boost::this_thread::sleep_for(timeToSleep);
        }
    }
    BOOST_LOG_TRIVIAL(info) << "Thread :" << boost::this_thread::get_id() << " stopped";
}

void Thread::stop()
{
    started = false;
}
