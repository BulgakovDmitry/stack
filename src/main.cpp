#include "../headers/stack.hpp"

int main(void)
{
    Stack_t stk = {};
    stackCtor(&stk);
    
    //stackPush(&stk, 5);
    //stackPush(&stk, 6);
    //for (int i = 0; i < 11; i++)
    //{
    //    stackPush(&stk, (double)i);
    //}
    //stackPush(&stk, 11);
    //stackPush(&stk, 12);
    //stackPush(&stk, 13);

    //stackPop(&stk);
    //stackPop(&stk);
    //stackPop(&stk);
    //stackPop(&stk);
    //stackPop(&stk);
    //stackPop(&stk);
    //stackPop(&stk);
    printf("123456789------------------------------------\n");
    stackDump(stk);

    stackDtor(&stk);
    return 0;
}