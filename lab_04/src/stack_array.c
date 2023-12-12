#include "stack_array.h"


void initializeArrayStack(ArrayStack *stack)
{
    for (size_t i = 0; i < MAX_SIZE; i++)
        stack->data[i] = 0;
    stack->top = EMPTY_STACK;
}

int isArrayStackEmpty(ArrayStack* stack)
{
    return stack->top == EMPTY_STACK;
}

int isArrayStackFull(ArrayStack* stack)
{
    return stack->top == FULL_STACK;
}

int getArrayStackTop(ArrayStack* stack) {
    if (isArrayStackEmpty(stack)) {
        return ERROR;
    }
    return stack->data[stack->top];
}

int pushArrayStack(ArrayStack* stack, int value)
{
    if (isArrayStackFull(stack))
    {
        return ERROR;
    }
    stack->data[++stack->top] = value;
    return OK;
}

int popArrayStack(ArrayStack* stack)
{
    if (isArrayStackEmpty(stack))
    {
        return ERROR;
    }
    return stack->data[stack->top--];
}

void printArrayStack(ArrayStack* stack)
{
    if (isArrayStackEmpty(stack))
    {
        printf("Стек пуст!\n");
        return;
    }
    printf("Стек (конец - начало): ");
    for (int i = 0; i <= stack->top; i++)
    {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}
