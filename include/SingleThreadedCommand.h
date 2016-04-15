#ifndef SINGLETHREADCOMMAND_H
#define SINGLETHREADCOMMAND_H

#include "Command.h"


class SingleThreadedCommand : public Command
{
public:
    void execute();
protected:

};

#endif // SINGLETHREADCOMMAND_H
