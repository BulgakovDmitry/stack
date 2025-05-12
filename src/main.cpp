#include "../headers/stack.hpp"

int main(void)
{
    Stack_t stk = {};
    stackCtor(&stk);
    printf("hello!\n");
    stackDtor(&stk);
    return 0;
}