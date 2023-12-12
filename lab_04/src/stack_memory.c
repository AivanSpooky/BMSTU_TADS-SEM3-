#include "stack_memory.h"

void printMemoryAddresses(ArrayStack* stack)
{
    if (isArrayStackEmpty(stack))
    {
        printf("Стек пуст!\n");
    }
    else
    {
        printf("Адреса памяти: ");
        for (int i = 0; i <= stack->top; i++)
        {
            printf("%p ", (void*)&(stack->data[i]));
        }
        printf("\n");
    }  
}

void printFreeMemoryAddresses(ArrayStack* stack)
{
    if (isArrayStackFull(stack))
    {
        printf("Стек полон! (свободных адрессов нет)\n");
    }
    else
    {
        printf("Свободные адреса памяти: ");
        for (int i = stack->top + 1; i < MAX_SIZE; i++)
        {
            printf("%p ", (void*)&(stack->data[i]));
        }
        printf("\n");
    }
}

void printMemoryAddressesList(ListStack* stack)
{
    if (isListStackEmpty(stack))
    {
        printf("Стек пуст!\n");
    }
    else
    {
        printf("Адреса памяти: ");
        ListNode* current = stack->top;
        while (current != NULL)
        {
            printf("%p ", (void*)current);
            current = current->next;
        }
        printf("\n");
    }
}

void printFreeMemoryAddressesList(ListNode *address[], size_t max_i)
{
    printf("Свободные адреса памяти: ");
    for (size_t i = 0; i < max_i; i++)
    {
        printf("%p ", (void*)address[i]);
    }
    printf("\n");
}
