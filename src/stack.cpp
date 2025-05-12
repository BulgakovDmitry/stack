#include "../headers/stack.hpp"
#include "../myLib/myLib.hpp"

/*---------------ФУНКЦИЯ КОНСТРУКТОР ДЛЯ СОЗДАНИЯ СТЕКА------------------------------------------------------------------------------------------*/
int StackCtor(Stack_t* stk)
{
    DBG(ASSERT(stk, "stk = nullptr", stderr);)

    CAN_PR(stk->L_STACK_KANAR = L_STACK_KANAR;)

    stk->coef_capacity = 2;
    stk->size = 0;
    stk->capacity = START_SIZE;
    stk->data = 0;

    stk->data = (StackElem_t*)calloc(stk->capacity + 2, sizeof(StackElem_t));
    DBG(ASSERT(stk->data, "data = nullptr", stderr);)

    stk->data[0] = L_DATA_KANAR;                  // УСТАНОВКА ЛЕВОЙ  КАНАРЕЙКИ НА data
    stk->data[stk->capacity] = R_DATA_KANAR;  // УСТАНОВКА ПРАВОЙ КАНАРЕЙКИ НА data

    stk->error_status = 0;

    CAN_PR(stk->R_STACK_KANAR = R_STACK_KANAR;)

    return 0;
}
