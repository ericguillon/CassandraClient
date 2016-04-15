#ifndef SEPAPROVISIONEDCOMMAND_H
#define SEPAPROVISIONEDCOMMAND_H

#include "SepaCommonCommand.h"
#include "SepaProvisionedCommandImpl.h"

class SepaProvisionedCommand : public SepaCommonCommand<SepaProvisionedCommand, SepaProvisionedCommandImpl>
{
public:
    SepaProvisionedCommand();
};

#endif // SEPAPROVISIONEDCOMMAND_H
