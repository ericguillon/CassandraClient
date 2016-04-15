#ifndef ONHOLDOPERATIONHANDLER_H
#define ONHOLDOPERATIONHANDLER_H
#include <BaseOperationHandler.h>

class OnHoldOperationHandler : public BaseOperationHandler<OnHoldOperationHandler>
{
public:
    OnHoldOperationHandler(CommandFactory* factory);
};

#endif // ONHOLDOPERATIONHANDLER_H
