#include "Stack.h"

int main(void)
{
    Stack_t stk = {};
    //ON_DEBUG({stk.info_Stack_t = INFO()})
    STACK_CTOR(&stk);
    StackPush(&stk, 1);
    StackPush(&stk, 2);
    StackPush(&stk, 5);
    //for (int q = 0; q < 15; q++) {StackPush(&stk, q + 3);}
    //for (int i = 0; i < 3; i++) {StackPop(&stk);}

    ON_DEBUG(StackDump(&stk, INFO());)

    //ON_DEBUG(StackDump(&stk, INFO());)

    StackDtor(&stk);
    //ON_DEBUG(printf("error_status = %d", stk.error_status);)
    return 0;
}