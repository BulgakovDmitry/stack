#include "../headers/stack.hpp"

int main(void)
{
    Stack_t stk = {};
    stackCtor(&stk);
    
    stackPush(&stk, 5);
    stackPush(&stk, 6);
    stackPop(&stk);

    stackDump(stk);
    stackDtor(&stk);
    return 0;
}