#include "../headers/stack.hpp"
#include "../myLib/myLib.hpp"

/*---------------ФУНКЦИЯ КОНСТРУКТОР ДЛЯ СОЗДАНИЯ СТЕКА------------------------------------------------------------------------------------------*/
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
    stk->L_STACK_KANAR = 0;
    stk->R_STACK_KANAR = 0;
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

    stk->data[0] = L_DATA_KANAR;                    // УСТАНОВКА НОВОЙ ЛЕВОЙ КАНАРЕЙКИ
    stk->data[stk->capacity - 1] = R_DATA_KANAR;    // УСТАНОВКА НОВОЙ ПРАВОЙ КАНАРЕЙКИ
    stk->data[stk->size + 1] = value;
    stk->size++;
}

void stackDump(Stack_t stk)
{
    printf("%s___stackDump___~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", RED, RESET);
    //printf("%sStack_t %s[%s%p%s]%s\n", CEAN, GREEN, MANG, stk, GREEN, RESET);
    //printf("%sCalled from %s%s %s: %s%zu %s(%s%s%s)  %s\n", CEAN, MANG, info_l.file, GREEN, RED, info_l.line, GREEN, BLUE, info_l.func, GREEN, RESET);
    //printf("%sname 'stk' born at %s%s %s:%s %zu %s(%s%s%s)%s\n", CEAN, MANG, stk->info_Stack_t.file, GREEN, RED, stk->info_Stack_t.line, GREEN, BLUE, stk->info_Stack_t.func, GREEN, RESET);
    printf("%s{%sL_STACK_KANAR %s= %s%X%s", GREEN, BLUE, GREEN, RED, (unsigned int)stk.L_STACK_KANAR, RESET);
    printf("%s, %sR_STACK_KANAR %s= %s%X%s}%s\n", GREEN, BLUE, GREEN, RED, (unsigned int)stk.R_STACK_KANAR, GREEN, RESET);
    printf("%s{%sL_DATA_KANAR %s = %s%X%s, %s", GREEN, BLUE, GREEN, RED, (unsigned int)stk.data[0], GREEN, RESET);
    printf("%sR_DATA_KANAR %s = %s%X%s}%s\n", BLUE, GREEN, RED, (unsigned int)stk.data[stk.capacity - 1], GREEN, RESET);

    printf("%scapasity %s= %s%zu%s\n", BLUE, GREEN, RED, stk.capacity, RESET);
    printf("%ssize %s= %s%zu%s\n", BLUE, GREEN, RED, stk.size, RESET);
    printf("%sdata %s[%s%p%s]%s\n", CEAN, GREEN, MANG, stk.data, GREEN, RESET);

    stackPrint(stk);
    //StackError(stk); //TODO
    printf("%s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", RED, RESET);
}

void stackPrint(Stack_t stk)
{
    printf("%s{%s\n", GREEN, RESET);
    //printf("  %sk%s[%s%3d%s]   = %s  %X %s\n", YELLOW, GREEN, MANG, 0, GREEN, RED, (unsigned int)stk.data[0], RESET);
    for (size_t i = 0; i < stk.capacity; i++)  //FIXME there is...
    {
        printf("  %s*%s[%s%3zu%s]   = %s%3lg%s\n", YELLOW, GREEN, MANG, i, GREEN, RED, stk.data[i], RESET);
    }
    printf("%sstk.data%s[%s0%s]            = %s%lg %s[ %shex%s %X%s ]%s\n", BLUE, GREEN, MANG, GREEN, RED, stk.data[0], MANG, BLUE, RED, (unsigned int)stk.data[0], MANG, RESET);
    printf("%sstk.data%s[%scapacity - 1%s] = %s%lg %s[ %shex%s %X%s ]%s\n", BLUE, GREEN, MANG, GREEN, RED, stk.data[stk.capacity - 1], MANG, BLUE, RED, (unsigned int)stk.data[stk.capacity - 1], MANG, RESET);
    //printf("stk.data[capacity - 1] = %lg hex = %X\n", stk.data[stk.capacity - 1], (unsigned int)stk.data[stk.capacity - 1]);
    /*for (size_t i = 1; i < stk->size; i++) 
    {
        printf("  %s*%s[%s%3zu%s]   = %s%3lg%s\n", YELLOW, GREEN, MANG, i, GREEN, RED, stk->data[i], RESET);
    }
    
    for (size_t j = 1; j < stk->capacity - stk->size + 1; j++) 
    {
        printf("   %s[%s%3zu%s]   = %s%5lg %s (%sPOISON%s)%s\n", GREEN, MANG, j + stk->size, GREEN, RED, POISON, GREEN, YELLOW, GREEN, RESET);
    }
    printf("  %sk%s[%s%3zu%s]   = %s  %X %s \n", YELLOW, GREEN, MANG, stk->capacity + 1, GREEN, RED, (int)stk->data[stk->capacity+1], RESET);*/
    printf("%s}%s\n", GREEN, RESET);
}
