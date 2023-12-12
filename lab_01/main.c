#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "consts.h"
#include "err_codes.h"

#include "long_double.h"
#include "long_nums.h"

int main()
{
    LongDouble n1;
    LongDouble n2;
    LongDouble invn;
    LongDouble res;
    memset(n1.digits, '\0', MAX_ANSWER + 1);
    memset(n2.digits, '\0', MAX_ANSWER + 1);
    memset(invn.digits, '\0', MAX_ANSWER + 1);
    memset(res.digits, '\0', MAX_ANSWER + 1);
    char s[BUF_SIZE];
    int rc = OK;

    printf("Программа выполняет деление двух чисел особого формата (описан далее)\n");
    printf("Результат выводится в нормализованном виде с точность до 40 цифр.\n");
    printf("Введите целое делимое (до 40 знаков):\n");
    printf("---------1---------2---------3---------4\n");
    if (!fgets(s, sizeof(s), stdin))
    {
        printf("Ошибка ввода!\n");
        return ERR_IO;
    }
    rc = writeInteger(&n1, s);
    size_t zero = 0;
    if (rc == ERR_ZERO)
    {
        zero++;
    }
    else if (rc != OK)
    {
        return ERR_IO;
    }
    //printLongDouble(&n1);

    printf("\nВведите вещественный делитель в виде\n[+-]m.nE[+-]K\n\
m+n до 40 знаков\nК до 5 знаков:\n");
    if (!fgets(s, sizeof(s), stdin))
    {
        printf("Ошибка ввода!\n");
        return ERR_IO;
    }
    printf("\n");
    rc = writeDouble(&n2, s);
    if (rc != OK)
        return ERR_IO;
    //printLongDouble(&n2);

    if (zero == 1)
    {
        printf("Частное (в нормализованном виде/40 знаков): \n");
        printLongDouble(&n1);
    }
    else
    {
        res = division(&n1, &n2);
        if (abs(res.exponent) > MAX_EXP)
        {
            printf("Порядок частного выходит за границы допустимых значений! (больше 5 знаков)\n");
            return ERR_RANGE;
        }
        printf("Частное (в нормализованном виде/40 знаков): \n");
        printLongDouble(&res);
    }

    return OK;
}
