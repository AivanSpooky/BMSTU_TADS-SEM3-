#ifndef STACK_POSTFIXCONVERSION_H__

#define STACK_POSTFIXCONVERSION_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack_types.h"
#include "stack_array.h"
#include "stack_list.h"

void printPostfix(char *postfix);

void convertToPostfix(char* infix, char* postfix);

void convertToPostfixList(char* infix, char* postfix);

#endif
