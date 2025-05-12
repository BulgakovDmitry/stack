#ifndef STACK_MAIN_H
#define STACK_MAIN_H

typedef double StackElem_t;
typedef double Canary_t;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "configFile.hpp"

#ifdef STACK_DEBUG
    #define DBG(...) __VA_ARGS__
#else
    #define DBG(...)
#endif

#ifdef CANARY_PROTECTION
    #define CAN_PR(...) __VA_ARGS__
#else
    #define CAN_PR(...)
#endif

struct Stack_t
{
    CAN_PR(Canary_t L_STACK_KANAR;)

    size_t   coef_capacity;
    uint64_t error_status;

    StackElem_t* data;
    size_t       size;
    size_t       capacity;

    CAN_PR(Canary_t R_STACK_KANAR;)
};

const size_t START_SIZE    = 16;

const Canary_t L_DATA_KANAR  = 0xEDAA;
const Canary_t R_DATA_KANAR  = 0xF00D;
const Canary_t L_STACK_KANAR = 0xBEDA;
const Canary_t R_STACK_KANAR = 0x0DED;

void stackCtor(Stack_t* stk);
void stackDtor(Stack_t* stk);

#endif
