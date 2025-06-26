#include "../headers/stack.hpp"
#include "../myLib/myLib.hpp"

void stackCtor(Stack_t* stk)
{
    DBG(ASSERT(stk, "stk = nullptr", stderr);)

    CAN_PR(
        stk->leftStackCanary = L_STACK_KANAR;
        stk->rightStackCanary = R_STACK_KANAR;
    )

    stk->coefCapacity = 2;
    stk->size = 0;
    stk->capacity = START_SIZE;
    stk->data = 0;

    stk->data = (StackElem_t*)calloc(stk->capacity, sizeof(StackElem_t));
    DBG(ASSERT(stk->data, "data = nullptr", stderr);)

    CAN_PR(
        stk->data[0]                 = L_DATA_KANAR;   // УСТАНОВКА ЛЕВОЙ  КАНАРЕЙКИ НА data
        stk->data[stk->capacity - 1] = R_DATA_KANAR;   // УСТАНОВКА ПРАВОЙ КАНАРЕЙКИ НА data
    )

    for (size_t i = 1; i < stk->capacity - 1; i++) 
        stk->data[i] = POISON;

    StackError verifyError = (StackError)stackVerify(stk);
    if (verifyError != OK) 
    {
        stackDump(*stk);
        stackErrorDump(*stk);
        exit(1);
    }

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
    CAN_PR(
        stk->leftStackCanary = 0;
        stk->rightStackCanary = 0;
    )
    stk = nullptr;
}

StackError stackPush(Stack_t* stk, StackElem_t value)
{
    DBG(ASSERT(stk, "stk = nullptr", stderr);)

    if (!stk)
        return POINTER_ERROR;

    StackError verifyError = (StackError)stackVerify(stk);

    if (verifyError != OK)
    {
        stackDump(*stk);
        stackErrorDump(*stk);
        return verifyError;
    }

    if (stk->size >= stk->capacity - 2) // CHECKING FOR IMPLEMENTATION
    {    
        CAN_PR(
            stk->data[0] = POISON;                  // REMOVAL OF OLD LEFT CANARY
            stk->data[stk->capacity - 1] = POISON;  // REMOVING THE RIGHT CANARY LINE (CHANGE TO POISON)
        )

        size_t newCapacity = stk->capacity * stk->coefCapacity;
        StackElem_t* newData = (StackElem_t*)realloc(stk->data, (stk->capacity) * sizeof(StackElem_t));

        if (!newData)
        {
            CAN_PR(     
                stk->data[0] = L_DATA_KANAR;
                stk->data[stk->capacity - 1] = R_DATA_KANAR;
            )
            
            stk->errorStatus |= ALLOC_ERROR;
            stackDump(*stk);
            return ALLOC_ERROR;
        }

        stk->data = newData;
        stk->capacity = newCapacity;
        
        for (size_t i = stk->size + 1; i < stk->capacity - 1; i++) // Initialize new memory
            stk->data[i] = POISON;

        CAN_PR(
            stk->data[0] = L_DATA_KANAR;                 // INSTALLING A NEW LEFT  CANARY
            stk->data[stk->capacity - 1] = R_DATA_KANAR; // INSTALLING A NEW RIGHT CANARY
        )
    }    
   
    stk->data[stk->size + 1] = value;
    stk->size++;

    if ((verifyError = (StackError)stackVerify(stk)) != OK) // final check
    {
        stk->errorStatus = verifyError;
        stackDump(*stk);
        stackErrorDump(*stk);
        return verifyError;
    }

    return OK;
}

StackElem_t stackPop(Stack_t* stk)
{
    StackError verifyError = (StackError)stackVerify(stk);
    if (verifyError != OK || stk == nullptr || stk->size == 0)
    {
        if (verifyError != OK)
        {
            stackDump(*stk);
            stackErrorDump(*stk);
        }
        else if (stk != nullptr && stk->size == 0)
        {
            fprintf(stderr, RED "Error: stack underflow (attempt to pop from empty stack)\n" RESET);
        }
        return POISON;
    }
    
    StackElem_t temp = stk->data[stk->size];   
    stk->data[stk->size] = POISON;   
    stk->size--;

    if (stk->size < stk->capacity / stk->coefCapacity && stk->capacity > START_SIZE)
    {
        CAN_PR(
            stk->data[0] = POISON; // REMOVING THE OLD LEFT CANARY
            stk->data[stk->capacity - 1] = POISON; // REMOVING RIGHT CANARY LINE (CHANGE TO POISON)
        )
        
        stk->capacity /= stk->coefCapacity; // DECREASE capacity

        StackElem_t* newData = (StackElem_t*)realloc(stk->data, stk->capacity * sizeof(StackElem_t));
        if (!newData)
        {
            stk->capacity *= stk->coefCapacity; // save the old capacity (since realloc failed)
            
            stk->errorStatus |= ALLOC_ERROR;
            
            CAN_PR(
                stk->data[0] = L_DATA_KANAR;
                stk->data[stk->capacity - 1] = R_DATA_KANAR;
            )
            
        }
        else
        {
            stk->data = newData;
            
            CAN_PR(
                stk->data[0] = L_DATA_KANAR;
                stk->data[stk->capacity - 1] = R_DATA_KANAR;
                
                for (size_t i = stk->size + 1; i < stk->capacity - 1; i++) // Initialized "empty" elements as POISON
                    stk->data[i] = POISON;
            )
        }
    }

    if (stackVerify(stk) != OK)
    {
        stackDump(*stk);
        stackErrorDump(*stk);
    }

    return temp;
}

StackElem_t stackGet(Stack_t stk)
{
    if (stk.size > 1)
        return stk.data[stk.size];  

    printf(RED"STACK IS EMPTY\n"RESET);
    return POISON;
}

static void stackDataDump(Stack_t stk)
{
    printf("%s{%s\n", GREEN, RESET);

    for (size_t i = 0; i < stk.capacity; i++)
        printf("  %s[%s%3zu%s]   = %s%3lg%s\n", GREEN, MANG, i, GREEN, RED, stk.data[i], RESET);
    
    printf("%s}%s\n", GREEN, RESET);
    
    printf("%sstk.data%s[%s0%s]            = %s%lg %s[ %shex%s %X%s ]%s", BLUE, GREEN, MANG, GREEN, RED, stk.data[0], MANG, BLUE, RED, (unsigned int)stk.data[0], MANG, RESET);
    CAN_PR(printf(" %s[%strue hex%s %X %s]%s", MANG, BLUE, RED, (unsigned int)L_DATA_KANAR, MANG, RESET);)
    putchar('\n');
    printf("%sstk.data%s[%scapacity - 1%s] = %s%lg %s[ %shex%s %X%s ]%s", BLUE, GREEN, MANG, GREEN, RED, stk.data[stk.capacity - 1], MANG, BLUE, RED, (unsigned int)stk.data[stk.capacity - 1], MANG, RESET);
    CAN_PR(printf(" %s[%strue hex%s %X %s]%s", MANG, BLUE, RED, (unsigned int)R_DATA_KANAR, MANG, RESET);)
    putchar('\n');
}

void stackDump(Stack_t stk)
{
    printf("%s___stackDump___~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", RED, RESET);
    CAN_PR(printf("%s{%sL_STACK_KANAR %s= %s%X%s", GREEN, BLUE, GREEN, RED, (unsigned int)stk.leftStackCanary, RESET);)
    CAN_PR(printf("%s, %sR_STACK_KANAR %s= %s%X%s}%s\n", GREEN, BLUE, GREEN, RED, (unsigned int)stk.rightStackCanary, GREEN, RESET);)
    printf("%s{%sL_DATA_KANAR %s = %s%X%s, %s", GREEN, BLUE, GREEN, RED, (unsigned int)stk.data[0], GREEN, RESET);
    printf("%sR_DATA_KANAR %s = %s%X%s}%s\n", BLUE, GREEN, RED, (unsigned int)stk.data[stk.capacity - 1], GREEN, RESET);

    printf("%scapasity %s= %s%zu%s\n", BLUE, GREEN, RED, stk.capacity, RESET);
    printf("%ssize %s= %s%zu%s\n", BLUE, GREEN, RED, stk.size, RESET);
    printf("%sdata %s[%s%p%s]%s\n", CEAN, GREEN, MANG, stk.data, GREEN, RESET);

    stackDataDump(stk);
    printf("%s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", RED, RESET);
}

uint64_t stackVerify(Stack_t* stk)
{
    if (!stk)
        return POINTER_ERROR;
    
    uint64_t errors = OK;

    if (stk->size > stk->capacity - 2)  // -2 for canaries
        errors |= SIZE_ERROR;
    
    CAN_PR
    (
        if (stk->leftStackCanary != L_STACK_KANAR)
            errors |= LEFT_STACK_CANARY_DIED;
            
        if (stk->rightStackCanary != R_STACK_KANAR)
            errors |= RIGHT_STACK_CANARY_DIED;
        
        if (!stk->data)
        {
            if (stk -> capacity == 0)
                errors |= POINTER_ERROR;
        }
        else 
        {
            if (stk->data[0] != L_DATA_KANAR)                  // check left data canary
                errors |= LEFT_DATA_CANARY_DIED;               // 
                
            if (stk->data[stk->capacity - 1] != R_DATA_KANAR)  // check right data canary
                errors |= RIGHT_DATA_CANARY_DIED;              // 
            
            for (size_t i = stk->size + 1; i < stk->capacity - 1; i++) // check poison elem
            {
                if (stk->data[i] != POISON)
                {
                    errors |= SIZE_ERROR;
                    break;
                }
            }
        }

    )
        
    stk->errorStatus = errors;
    return (StackError)errors;
}
    
static const char* stackErrors[9] = {
                                        "POINTER_ERROR",
                                        "ALLOC_ERROR",
                                        "SIZE_ERROR",
                                        "LEFT_STACK_CANARY_DIED",
                                        "RIGHT_STACK_CANARY_DIED",
                                        "LEFT_DATA_CANARY_DIED",
                                        "RIGHT_DATA_CANARY_DIED"
                                    };
StackError stackErrorDump(Stack_t stk)
{
    printf("%s___stackErrorDump___~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", RED, RESET);
    for (size_t i = 0; i < NUMBER_OF_ERRORS; i++)
    {
        if (stk.errorStatus & (1 << i))
            fprintf(stderr, RED"error: code %zu ( %s )\n"RESET, i, stackErrors[i]);
    }

    return OK;
}