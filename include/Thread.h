#ifndef THREAD_H
#define THREAD_H

class MultiThreadedCommandFactory;

class Thread
{
public:
    Thread(MultiThreadedCommandFactory* factory);
    Thread(const Thread& other);
    ~Thread();
    void operator()();
    void stop();

protected:

private:
    bool started;
    MultiThreadedCommandFactory * factory;
};

#endif // THREAD_H
