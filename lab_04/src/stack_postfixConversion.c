#include "stack_postfixConversion.h"

void printPostfix(char* postfix)
{
    printf("Постфиксная форма: ");
    int i = 0;
    while (postfix[i] != '\0')
    {
        printf("%c", postfix[i]);
        i++;
    }
    printf("\n");
}

int isValidExpression(char *infix)
{
    ListStack stack;
    initializeListStack(&stack);
    int i = 0;
    while (infix[i] != '\0')
    {
        if (infix[i] == '(')
        {
            pushListStack(&stack, infix[i]);
        }
        else if (infix[i] == ')')
        {
            if (isListStackEmpty(&stack))
            {
                return 0;
            }
            popListStack(&stack);
        }
        i++;
    }
    if (!isListStackEmpty(&stack))
    {
        return 0;
    }
    return 1;
}

int precedence(char operator)
{
    if (operator == '+' || operator == '-')
    {
        return 1;
    }
    else if (operator == '*' || operator == '/')
    {
        return 2;
    }
    return 0;
}

void convertToPostfix(char* infix, char* postfix) {
    if (!isValidExpression(infix))
    {
        printf("Неверное выражение.\n");
        return;
    }
    
    ArrayStack operatorStack;
    initializeArrayStack(&operatorStack);
    int i = 0;
    int j = 0;
    while (infix[i] != '\0')
    {
        if (!isdigit(infix[i]))
            postfix[j++] = ' ';
        if (isdigit(infix[i]))
        {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(')
        {
            pushArrayStack(&operatorStack, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!isArrayStackEmpty(&operatorStack) && getArrayStackTop(&operatorStack) != '(')
            {
                postfix[j++] = popArrayStack(&operatorStack);
            }
            if (!isArrayStackEmpty(&operatorStack) && getArrayStackTop(&operatorStack) == '(')
            {
                popArrayStack(&operatorStack);
            }
            else
            {
                printf("Неверное выражение.\n");
                return;
            }
        }
        else
        {
            while (!isArrayStackEmpty(&operatorStack) && precedence(infix[i]) <= precedence(getArrayStackTop(&operatorStack)))
            {
                postfix[j++] = popArrayStack(&operatorStack);
            }
            pushArrayStack(&operatorStack, infix[i]);
        }
        i++;
    }
    if (isdigit(infix[i - 1]))
        postfix[j++] = ' ';
    while (!isArrayStackEmpty(&operatorStack))
        postfix[j++] = popArrayStack(&operatorStack);
    
    postfix[j] = '\0';
}

void convertToPostfixList(char* infix, char* postfix) {
    if (!isValidExpression(infix)) {
        printf("Неверное выражение.\n");
        return;
    }
    
    ListStack operatorStack;
    initializeListStack(&operatorStack);
    int i = 0;
    int j = 0;
    while (infix[i] != '\0')
    {
        if (!isdigit(infix[i]))
            postfix[j++] = ' ';
        if (isdigit(infix[i]))
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            pushListStack(&operatorStack, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!isListStackEmpty(&operatorStack) && getListStackTop(&operatorStack) != '(')
            {
                postfix[j++] = popListStack(&operatorStack);
            }
            if (!isListStackEmpty(&operatorStack) && getListStackTop(&operatorStack) == '(')
            {
                popListStack(&operatorStack);
            }
            else
            {
                printf("Неверное выражение.\n");
                return;
            }
        }
        else
        {
            while (!isListStackEmpty(&operatorStack) && precedence(infix[i]) <= precedence(getListStackTop(&operatorStack)))
            {
                postfix[j++] = popListStack(&operatorStack);
            }
            pushListStack(&operatorStack, infix[i]);
        }
        i++;
    }
    if (isdigit(infix[i - 1]))
        postfix[j++] = ' ';
    while (!isListStackEmpty(&operatorStack))
        postfix[j++] = popListStack(&operatorStack);
    
    postfix[j] = '\0';
}
