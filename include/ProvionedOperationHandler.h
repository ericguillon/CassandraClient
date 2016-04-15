#ifndef PROVIONEDOPERATIONHANDLER_H
#define PROVIONEDOPERATIONHANDLER_H

#include <BaseOperationHandler.h>


class ProvionedOperationHandler : public BaseOperationHandler<ProvionedOperationHandler>
{
public:
    ProvionedOperationHandler(CommandFactory* factory);
};

#endif // PROVIONEDOPERATIONHANDLER_H
