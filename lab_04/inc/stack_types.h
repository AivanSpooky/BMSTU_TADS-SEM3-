#ifndef STACK_TYPES_H__

#define STACK_TYPES_H__

#include <stdio.h>

#include "consts.h"
#include "err_codes.h"

#define MAX_SIZE 1000

typedef struct
{
    int data[MAX_SIZE];
    int top;
} ArrayStack;

typedef struct Node 
{
    int data;
    struct Node *next;
} ListNode;

typedef struct
{
    ListNode* top;
} ListStack;

#endif
