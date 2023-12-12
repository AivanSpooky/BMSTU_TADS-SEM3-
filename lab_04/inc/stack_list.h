#ifndef STACK_LIST_H__

#define STACK_LIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "stack_types.h"


void initializeListStack(ListStack* stack);

int isListStackEmpty(ListStack* stack);

int getListStackTop(ListStack* stack);

int pushListStack(ListStack* stack, int value);

int popListStack(ListStack* stack);

void printListStack(ListStack* stack);

#endif
