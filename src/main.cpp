#include "../headers/stack.hpp"

int main(void)
{
    Stack_t stk = {};
    stackCtor(&stk);
    
    stackPush(&stk, 5);
    stackPush(&stk, 6);
    stackPush(&stk, 7);
    
    /*for (int i = 0; i < 11; i++)
        stackPush(&stk, (double)i);

    stackPush(&stk, 11);
    stackPush(&stk, 12);
    stackPush(&stk, 13);
    stackPush(&stk, 14);

    stackPop(&stk);
    stackPop(&stk);
    stackPop(&stk);
    stackPop(&stk);
    stackPop(&stk);*/
    stackPop(&stk);
    


    stackDump(stk);
    stackDtor(&stk);
    return 0;
}