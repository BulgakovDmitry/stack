#include "../headers/stack.hpp"

int main(void)
{
    Stack_t stk = {};
    stackCtor(&stk);
    printf("hello!\n");

    stackPush(&stk, 5);
    stackPush(&stk, 6);

    stackDump(stk);

    stackDtor(&stk);
    return 0;
}