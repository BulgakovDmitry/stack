#include "../headers/stack.hpp"
#include "../myLib/myLib.hpp"

void stackCtor(Stack_t* stk)
{
    DBG(ASSERT(stk, "stk = nullptr", stderr);)

    CAN_PR(stk->L_STACK_KANAR = L_STACK_KANAR;)

    stk->coefCapacity = 2;
    stk->size = 0;
    stk->capacity = START_SIZE;
    stk->data = 0;

    stk->data = (StackElem_t*)calloc(stk->capacity, sizeof(StackElem_t));
    DBG(ASSERT(stk->data, "data = nullptr", stderr);)

    CAN_PR(stk->data[0]                 = L_DATA_KANAR;)   // УСТАНОВКА ЛЕВОЙ  КАНАРЕЙКИ НА data
    CAN_PR(stk->data[stk->capacity - 1] = R_DATA_KANAR;)   // УСТАНОВКА ПРАВОЙ КАНАРЕЙКИ НА data

    stk->errorStatus = 0;

    CAN_PR(stk->R_STACK_KANAR = R_STACK_KANAR;)
}

void stackDtor(Stack_t* stk)
{
    ASSERT(stk, "stk = nullptr", stderr);

    DBG(ASSERT(stk->data, "stk->data = nullptr", stderr);)
    FREE(stk->data);

    stk->coefCapacity = 0;
    stk->size = 0;
    stk->capacity = 0;
    stk->data = 0;
    CAN_PR(stk->L_STACK_KANAR = 0;)
    CAN_PR(stk->R_STACK_KANAR = 0;)
    stk = nullptr;
}

void stackPush(Stack_t* stk, StackElem_t value)
{
    DBG(ASSERT(stk, "stk = nullptr", stderr);)

    if (stk->size >= stk->capacity - 2) // ПРОВЕРКА НА РЕАЦИРОВАНИЕ
    {    
        CAN_PR(stk->data[0] = POISON;)                  // УДАЛЕНИЕ СТАРОЙ ЛЕВОЙ КАНАРЕЙКИ
        CAN_PR(stk->data[stk->capacity - 1] = POISON;)  // УДАЛЕНИЕ СТРОЙ ПРАВОЙ КАНАРЕЙКИ (ИЗМЕНЕНИЕ НА POISON)

        stk->capacity = stk->capacity * stk->coefCapacity;
        stk->data = (StackElem_t*)realloc(stk->data, (stk->capacity) * sizeof(StackElem_t));
    }    

    CAN_PR(stk->data[0] = L_DATA_KANAR;)                    // УСТАНОВКА НОВОЙ ЛЕВОЙ КАНАРЕЙКИ
    CAN_PR(stk->data[stk->capacity - 1] = R_DATA_KANAR;)    // УСТАНОВКА НОВОЙ ПРАВОЙ КАНАРЕЙКИ
    stk->data[stk->size + 1] = value;
    stk->size++;
}

StackElem_t stackPop(Stack_t* stk)
{
    if ((stk->size < (0.5 * stk->capacity - 1)) && stk->size > 1)
    {
        if (stk->capacity > START_SIZE)
        {
            CAN_PR(stk->data[0]                 = POISON;)  // УДАЛЕНИЕ СТАРОЙ ЛЕВОЙ КАНАРЕЙКИ
            CAN_PR(stk->data[stk->capacity - 1] = POISON;)  // УДАЛЕНИЕ СТРОЙ ПРАВОЙ КАНАРЕЙКИ (ИЗМЕНЕНИЕ НА POISON)
            stk->capacity = stk->capacity / stk->coefCapacity; // УМЕНЬШЕНИЕ capacity

            stk->data = (StackElem_t*)realloc(stk->data, (stk->capacity + 2) * sizeof(StackElem_t));
            DBG(ASSERT(stk, "stk = nullptr", stderr);)
            CAN_PR(stk->data[0] = L_DATA_KANAR;)                 // УСТАНОВКА НОВОЙ ЛЕВОЙ КАНАРЕЙКИ
            CAN_PR(stk->data[stk->capacity - 1] = R_DATA_KANAR;) // УСТАНОВКА НОВОЙ ПРАВОЙ КАНАРЕЙКИ
        }   
    }  

    StackElem_t temp = stk->data[stk->size];   
    stk->data[stk->size] = POISON;   
    stk->size--;
    return temp;
}

StackElem_t stackGet(Stack_t stk)
{
    if (stk.size > 1)
        return stk.data[stk.size];  

    printf(RED"STACK IS EMPTY\n"RESET);
    return POISON;
}

void stackDump(Stack_t stk)
{
    printf("%s___stackDump___~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", RED, RESET);
    CAN_PR(printf("%s{%sL_STACK_KANAR %s= %s%X%s", GREEN, BLUE, GREEN, RED, (unsigned int)stk.L_STACK_KANAR, RESET);)
    CAN_PR(printf("%s, %sR_STACK_KANAR %s= %s%X%s}%s\n", GREEN, BLUE, GREEN, RED, (unsigned int)stk.R_STACK_KANAR, GREEN, RESET);)
    printf("%s{%sL_DATA_KANAR %s = %s%X%s, %s", GREEN, BLUE, GREEN, RED, (unsigned int)stk.data[0], GREEN, RESET);
    printf("%sR_DATA_KANAR %s = %s%X%s}%s\n", BLUE, GREEN, RED, (unsigned int)stk.data[stk.capacity - 1], GREEN, RESET);

    printf("%scapasity %s= %s%zu%s\n", BLUE, GREEN, RED, stk.capacity, RESET);
    printf("%ssize %s= %s%zu%s\n", BLUE, GREEN, RED, stk.size, RESET);
    printf("%sdata %s[%s%p%s]%s\n", CEAN, GREEN, MANG, stk.data, GREEN, RESET);

    stackDataDump(stk);
    //StackError(stk); //TODO
    printf("%s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", RED, RESET);
}

void stackDataDump(Stack_t stk)
{
    printf("%s{%s\n", GREEN, RESET);

    for (size_t i = 0; i < stk.capacity; i++)
        printf("  %s[%s%3zu%s]   = %s%3lg%s\n", GREEN, MANG, i, GREEN, RED, stk.data[i], RESET);
    
    printf("%s}%s\n", GREEN, RESET);
    
    printf("%sstk.data%s[%s0%s]            = %s%lg %s[ %shex%s %X%s ]%s", BLUE, GREEN, MANG, GREEN, RED, stk.data[0], MANG, BLUE, RED, (unsigned int)stk.data[0], MANG, RESET);
    CAN_PR(printf(" %s[%strue hex%s %X %s]%s", MANG, BLUE, RED, (const int)L_DATA_KANAR, MANG, RESET);)
    putchar('\n');
    printf("%sstk.data%s[%scapacity - 1%s] = %s%lg %s[ %shex%s %X%s ]%s", BLUE, GREEN, MANG, GREEN, RED, stk.data[stk.capacity - 1], MANG, BLUE, RED, (unsigned int)stk.data[stk.capacity - 1], MANG, RESET);
    CAN_PR(printf(" %s[%strue hex%s %X %s]%s", MANG, BLUE, RED, (const int)R_DATA_KANAR, MANG, RESET);)
    putchar('\n');
}
