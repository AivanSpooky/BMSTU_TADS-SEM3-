#include "io.h"

void menu()
{
    printf("%s",
           "Выберите действие из списка, введя соответствуюший номер:\n");
    printf("%s",
           "1. МАССИВ: Ввести данные обслуживающего аппарата и вывести статистику работы.\n"
           "2. МАССИВ: Вывести количественную характеристику выполнения операций над очередью.\n"
           "3. СПИСОК: Ввести данные обслуживающего аппарата и вывести статистику работы.\n"
           "4. СПИСОК: Вывести количественную характеристику выполнения операций над очередью.\n"
           "0. Выход из программы.\n\n");
}

/*
Clean input stream from trash.
*/
void clean_input_stream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

/*
Input number in between.

Input data:
* int *const num - number of action to be done.
* const int left - left border of between.
* const int right - right border of between.
*/
void input_interval(int *const num, const int left, const int right)
{
    if (scanf("%d", num) != GOT_ARG)
    {
        clean_input_stream();
        errno = EINVALIDINTINPUT;
        return;
    }

    if (*num < left || *num > right)
    {
        clean_input_stream();
        errno = EINVALIDINTER;
        return;
    }
}
