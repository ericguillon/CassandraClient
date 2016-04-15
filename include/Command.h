#ifndef COMMAND_H
#define COMMAND_H

class MultiThreadedCommandFactory;

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void accept(MultiThreadedCommandFactory* factory) = 0;
};

#endif // COMMAND_H
