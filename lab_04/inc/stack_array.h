#ifndef STACK_ARRAY_H__

#define STACK_ARRAY_H__

#include <stdio.h>
#include <stdlib.h>

#include "stack_types.h"

void initializeArrayStack(ArrayStack* stack);

int isArrayStackEmpty(ArrayStack* stack);

int isArrayStackFull(ArrayStack* stack);

int getArrayStackTop(ArrayStack* stack);

int pushArrayStack(ArrayStack* stack, int value);

int popArrayStack(ArrayStack* stack);

void printArrayStack(ArrayStack* stack);

#endif
