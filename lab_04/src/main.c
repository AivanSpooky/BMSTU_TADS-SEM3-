#include <stdio.h>
#include <stdlib.h>

#include "stack_types.h"
#include "stack_array.h"
#include "stack_list.h"
#include "stack_memory.h"
#include "stack_postfixConversion.h"
#include "stack_comparison.h"

int main() {
    ArrayStack arrayStack;
    ListStack listStack;
    initializeArrayStack(&arrayStack);
    initializeListStack(&listStack);
    int choice;
    int value;
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    ListNode *address[MAX_SIZE];
    size_t cur_address = 0;

    char tmp[200] = { 0 };
    do {
        choice = 0;
        printf("\n");
        printf("Меню:\n");
        printf("1) Добавить элемент в стек (массив)\n");
        printf("2) Удалить элемент из стека (массив)\n");
        printf("3) Вывод текущего состояния стека (массив)\n");
        printf("4) Ввести выражение и записать в стек (массив)\n");
        printf("5) Вывести выражение в постфиксной форме (массив)\n");
        printf("6) Вывести адреса памяти элементов стека (массив)\n");
        printf("7) Вывести свободные адреса памяти стека (массив)\n");
        printf("8) Добавить элемент в стек (список)\n");
        printf("9) Удалить элемент из стека (список)\n");
        printf("10) Вывод текущего состояния стека (список)\n");
        printf("11) Ввести выражение и записать в стек (список)\n");
        printf("12) Вывести выражение в постфиксной форме (список)\n");
        printf("13) Вывести адреса памяти элементов стека (список)\n");
        printf("14) Вывести свободные адреса памяти стека (список)\n");
        printf("15) Сравнить время и ресурсы использования стека (массив) и стека (список)\n");
        printf("16) Выход\n");
        printf("Выберите пункт меню: ");
        if (scanf("%d", &choice) != ARG_READ)
        {
            fgets(tmp, sizeof(tmp), stdin);
        }

        printf("\n");
        switch (choice)
        {
            case 1:
                printf("Введите элемент (целое), которое надо добавить в стек: ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    fgets(tmp, sizeof(tmp), stdin);
                    printf("\nЭлемент введен неправильно!\n");
                    break;
                }
                else if (pushArrayStack(&arrayStack, value) == ERROR)
                {
                    printf("Стек полон! (нельзя добавить элемент)\n");
                }
                break;
            case 2:
                if (isArrayStackEmpty(&arrayStack))
                {
                    printf("Стек пуст! (нельзя удалить элемент)\n");
                }
                else
                {
                    printf("Удаленный элемент: %d\n", popArrayStack(&arrayStack));
                }
                break;
            case 3:
                printArrayStack(&arrayStack);
                break;
            case 4:
                postfix[0] = '\0';
                printf("Введите выражение: ");
                if (scanf("%s", infix) < ARG_READ)
                {
                    printf("\nПустой ввод!\n");
                    break;
                }
                convertToPostfix(infix, postfix);
                printf("Выражение помещено в стек.\n");
                break;
            case 5:
                printPostfix(postfix);
                break;
            case 6:
                printMemoryAddresses(&arrayStack);
                break;
            case 7:
                printFreeMemoryAddresses(&arrayStack);
                break;
            case 8:
                printf("Введите элемент (целое), которое надо добавить в стек: ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nЭлемент введен неправильно!\n");
                    fgets(tmp, sizeof(tmp), stdin);
                    break;
                }
                else if (pushListStack(&listStack, value) == ERROR)
                    printf("Стек полон! (нельзя добавить элемент)\n");
                else if (cur_address > 0)
                    address[cur_address--] = NULL;
                break;
            case 9:
                if (isListStackEmpty(&listStack)) {
                    printf("List stack is empty.\n");
                } else {
                    address[cur_address++] = listStack.top;
                    printf("Popped element: %d\n", popListStack(&listStack));
                }
                break;
            case 10:
                printListStack(&listStack);
                break;
            case 11:
                printf("Enter expression: ");
                scanf("%s", infix);
                convertToPostfixList(infix, postfix);
                break;
            case 12:
                printPostfix(postfix);
                break;
            case 13:
                printMemoryAddressesList(&listStack);
                break;
            case 14:
                printFreeMemoryAddressesList(address, cur_address);
                break;
            case 15:
                runExperiment();
                break;
            case 16:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 16);

    return 0;
}