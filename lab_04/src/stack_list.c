#include "stack_list.h"

int getListStackTop(ListStack* stack)
{
    if (isListStackEmpty(stack))
    {
        return ERROR;
    }
    return stack->top->data;
}

void initializeListStack(ListStack* stack)
{
    stack->top = NULL;
}

int isListStackEmpty(ListStack* stack)
{
    return stack->top == NULL;
}

int pushListStack(ListStack* stack, int value)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL)
    {
        return ERROR;
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    return OK;
}

int popListStack(ListStack* stack)
{
    if (isListStackEmpty(stack))
    {
        return ERROR;
    }
    ListNode* temp = stack->top;
    int value = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

void printListStack(ListStack* stack)
{
    if (isListStackEmpty(stack))
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (up - down): ");
    ListNode* current = stack->top;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
