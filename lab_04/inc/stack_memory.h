#ifndef STACK_MEMORY_H__

#define STACK_MEMORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "stack_types.h"
#include "stack_array.h"
#include "stack_list.h"

void printMemoryAddresses(ArrayStack* stack);

void printFreeMemoryAddresses(ArrayStack* stack);

void printMemoryAddressesList(ListStack* stack);

void printFreeMemoryAddressesList(ListNode *address[], size_t max_i);

#endif
