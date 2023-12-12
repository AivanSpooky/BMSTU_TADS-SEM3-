#include "long_double.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "long_nums.h"

void LDround(LongDouble *n)
{
    // Округляем число до 50 знаков, опираясь на 51-ую цифру
    for (int i = MAX_ANSWER - 1; i >= 0; i--)
    {
        // Если получилось округлить без увеличения порядка
        if (n->digits[i] - '0' + 1 <= 9)
        {
            (n->digits[i])++;
            break;
        }
        // Если в данном разряде порядок изменился - заменяем на 0
        // Иначе ставим на нулевой разряд единицу как конец алгоритма округления
        if (i != 0)
            n->digits[i] = '0';
        else
        {
            n->digits[i] = '1';
            n->exponent++;
        }
    }
}

void printLongDouble(LongDouble *n)
{
    // Выводим сетку
    printf("--|---------1---------2---------3---------4|-\n");
    
    // Выводим знак
    if (n->sign == -1)
        printf("-");
    else
        printf("+");
    // Выводим начало числа
    printf("0.");

    size_t zeros = 0;
    // Выводим цифры числа (40)
    for (size_t i = 0; i < MAX_ANSWER; i++)
    {
        char *elem = &n->digits[i];
        //printf("\n-%s-\n", elem);
        if (*elem == '\0')
            break;
        if (*elem == '0')
        {
            // Если наше число ноль - выводим ноль и завершаем цикл
            // Иначе просто выводим ноль
            if (i == 0)
            {
                printf("0");
                break;
            }
            else
            {
                zeros++;
            }
        }
        else
        {
            for (size_t j = 0; j < zeros; j++)
                printf("0");
            zeros = 0;
            printf("%c", *elem);
        }
    }
    // Выводим порядок (экспоненту)
    if (n->exponent >= 0)
        printf("E+%d\n", n->exponent);
    else
        printf("E%d\n", n->exponent);
}

int writeInteger(LongDouble *n, char *s)
{
    // Считываем знак
    if (*s == '-')
    {
        n->sign = -1;
        s++;
    }
    else if (*s == '+')
    {
        n->sign = 1;
        s++;
    }
    else
    {
        n->sign = 1;
    }
    
    // Заводим переменную для количества считанных цифр (для проверки на корректность ввода)
    // Далее считываем все цифры введенного целого
    size_t cnt = 0;
    for (size_t i = 0; *s != '\n'; i++)
    {
        // Удаление лишних нулей слева (не влияют на порядок)
        if (*s == '0' && i == 0)
        {
            while (*s == '0')
            {
                s++;
                cnt++;
            }
            if (*s == '\n')
                break;
        }
        // Если нашли не цифру - ошибка, завершение программы
        if (!isdigit(*s))
        {
            printf("Число введено некорректно! (содержит посторонние символы)\n");
            return ERR_IO;
        }
        // Записываем цифру в массив
        n->digits[i] = s[0];
        s++;
        cnt++;
    }
    // Ставим порядок для нормализации числа
    n->exponent = strlen(n->digits);
    // Убираем лишние нолики справа
    for (size_t i = n->exponent - 1; n->digits[i] == '0'; i--)
    {
        n->digits[i] = '\0';
        //cnt++;
        //n->exponent++;
    }
    
    // ПРОВЕРКА НА КОЛИЧЕСТВО ВВЕДЕННЫХ ЦИФР - ошибка, завершение программы
    if (cnt == OK)
    {
        printf("Слишком мало цифр! (меньше 1)\n");
        return ERR_RANGE;
    }
    if (cnt > MAX_DIGITS)
    {
        printf("Слишком много цифр! (больше 40)\n");
        return ERR_RANGE;
    }
    // Случай, когда ввели ноль
    if (strlen(n->digits) == 0)
    {
        n->digits[0] = '0';
        n->exponent = 1;
        return ERR_ZERO;
    }
    //
    return OK;
}

int writeDouble(LongDouble *n, char *s)
{
    // Считываем знак
    if (*s == '-')
    {
        n->sign = -1;
        s++;
    }
    else if (*s == '+')
    {
        n->sign = 1;
        s++;
    }
    else
    {
        n->sign = 1;
    }

    // Заводим переменную для количества считанных цифр (для проверки на корректность ввода)
    // Далее при наличии . или Е находим их положение
    // Далее считываем все цифры в зависимости от . и Е
    size_t cnt = 0;
    char *point = strchr(s, '.');
    char *exponent = strchr(s, 'E');
    if (point != NULL)
    {
        size_t ppos = point - s;
        // Считываем числа до точки
        for (size_t i = 0; *s != '.'; i++)
        {
            // Удаление лишних нулей слева
            if (*s == '0' && i == 0)
            {
                while (*s == '0')
                {
                    s++;
                    ppos--;
                    cnt++;
                }
                if (*s == '.')
                    break;
            }
            // Если нашли не цифру - ошибка, завершение программы
            if (!isdigit(*s))
            {
                printf("Число введено некорректно! (содержит посторонние символы)");
                return ERR_IO;
            }
            // Записываем цифру в массив
            n->digits[i] = *s;
            s++;
            cnt++;
        }
        // Ставим порядок для нормализации числа
        s++;
        n->exponent = strlen(n->digits);
        // Если указана экспонента - читаем числа поле точки и до Е
        if (exponent != NULL)
        {
            for (size_t i = ppos; *s != 'E'; i++)
            {
                // Удаление лишних нулей справа от точки (если нет целой части)
                if (*s == '0' && i == ppos && n->exponent == 0)
                {
                    i = 0;
                    while (*s == '0')
                    {
                        s++;
                        cnt++;
                        n->exponent--;
                    }
                    if (*s == 'E')
                        break;
                }
                // Если нашли не цифру - ошибка, завершение программы
                if (!isdigit(*s))
                {
                    printf("Число введено некорректно! (содержит посторонние символы)");
                    return ERR_IO;
                }
                // Записываем цифру в массив
                n->digits[i] = *s;
                s++;
                cnt++;
            }
            // Удаление лишних нулей справа от дробной части
            for (int i = strlen(n->digits) - 1; n->digits[i] == '0'; i--)
            {
                n->digits[i] = '\0';
            }
            // Считываем порядок
            char *end;
            int exp = strtol(s + 1, &end, BASE);
            // Дополнительные проверки на порядок - ошибка, завершение программы
            if (strlen(end) > 1)
            {
                printf("Порядок указан неправильно!\n");
                return ERR_RANGE;
            }
            if (abs(exp) > MAX_EXP)
            {
                printf("Порядок выходит за границы допустимых значений! (больше 5 знаков)\n");
                return ERR_RANGE;
            }
            n->exponent += exp;
        }
        else
        {
            // Экспонента не указана - читаем числа поле точки и до конца
            for (size_t i = ppos; *s != '\n'; i++)
            {
                // Удаление лишних нулей справа от точки (если нет целой части)
                if (*s == '0' && i == ppos && n->exponent == 0)
                {
                    i = 0;
                    while (*s == '0')
                    {
                        s++;
                        cnt++;
                        n->exponent--;
                    }
                    if (*s == '\n')
                        break;
                }
                // Если нашли не цифру - ошибка, завершение программы
                if (!isdigit(*s))
                {
                    printf("Число введено некорректно! (содержит посторонние символы)");
                    return ERR_IO;
                }
                // Записываем цифру в массив
                n->digits[i] = *s;
                s++;
                cnt++;
            }
            // Удаление лишних нулей справа от дробной части
            for (int i = strlen(n->digits) - 1; n->digits[i] == '0'; i--)
            {
                n->digits[i] = '\0';
            }
        }
    }
    // Обрабатывем случай, когда нет точки
    else
    {
        // Если указана экспонента - читаем числа до Е
        if (exponent != NULL)
        {
            for (size_t i = 0; *s != 'E'; i++)
            {
                // Удаление лишних нулей слева
                if (*s == '0' && i == 0)
                {
                    while (*s == '0')
                    {
                        cnt++;
                        s++;
                    }
                    if (*s == 'E')
                        break;
                }
                // Если нашли не цифру - ошибка, завершение программы
                if (!isdigit(*s))
                {
                    printf("Число введено некорректно! (содержит посторонние символы)\n");
                    return ERR_IO;
                }
                // Записываем цифру в массив
                n->digits[i] = *s;
                s++;
                cnt++;
            }
            n->exponent = strlen(n->digits);
            // Удаление лишних нулей справа от целой части
            for (size_t i = n->exponent - 1; n->digits[i] == '0'; i--)
            {
                n->digits[i] = '\0';
            }
            // Считываем порядок
            char *end;
            int exp = strtol(s + 1, &end, BASE);
            // Дополнительные проверки на порядок - ошибка, завершение программы
            if (strlen(end) > 1)
            {
                printf("Порядок указан неправильно!\n");
                return ERR_RANGE;
            }
            if (abs(exp) > MAX_EXP)
            {
                printf("Порядок выходит за границы допустимых значений! (больше 5 знаков)\n");
                return ERR_RANGE;
            }
            n->exponent += exp;
        }
        else
        {
            // В случае отсутсвия . и Е - считываем как целое
            for (size_t i = 0; *s != '\n'; i++)
            {
                // Удаление лишних нулей слева
                if (*s == '0' && i == 0)
                {
                    while (*s == '0')
                    {
                        s++;
                        cnt++;
                    }
                    if (*s == '\n')
                        break;
                }
                //
                if (!isdigit(*s))
                {
                    printf("Число введено некорректно! (содержит посторонние символы)\n");
                    return ERR_IO;
                }
                n->digits[i] = *s;
                s++;
                cnt++;
            }
            n->exponent = strlen(n->digits);
            // Удаление лишних нулей справа от целой части
            for (size_t i = n->exponent - 1; n->digits[i] == '0'; i--)
            {
                n->digits[i] = '\0';
            }
        }
    }
    // ПРОВЕРКА НА КОЛИЧЕСТВО ВВЕДЕННЫХ ЦИФР
    if (cnt > MAX_DIGITS)
    {
        printf("Слишком много цифр в мантиссе! (больше 40)\n");
        return ERR_RANGE;
    } 
    if (cnt == OK)
    {
        printf("Слишком мало цифр! (меньше 1)\n");
        return ERR_RANGE;
    }
    // Случай, когда ввели ноль в качестве втрого числа - ошибка, завершение программы
    if (strlen(n->digits) == 0)
    {
        printf("На ноль делить нельзя!\n");
        return ERR_ZERO;
    }
    return OK;
}

LongDouble division(LongDouble *d1, LongDouble *d2)
{
    LongDouble res;
    memset(res.digits, '\0', MAX_ANSWER + 1);
    res.exponent = 1;
    // Перезаписываем LongDouble в nums
    nums n1 = LDton(d1);
    nums n2 = LDton(d2);
    
    // Заполняем цифры нового числа пока не заполнили 51 цифру
    size_t len = strlen(res.digits);
    char digit = 0;
    size_t flag = 1;
    while (len <= MAX_ANSWER + 1)
    {
        // Если делимое меньше делителя - записываем digit в частное и 
        // сдвигаем цифры делителя вправо. Иначе выполняем вычитание и увеличиваем
        // digit на 1 после каждого вычитания.

        // printf("%zu - %d\n   ", len, numsCompare(n1, n2));
        // for (size_t i = 0; i <= MAX_ANSWER; i++)
        //     printf("%c", res.digits[i]);
        // printf("\n");
        if (numsCompare(n1, n2) < 0)
        {
            if (digit != 0)
            {
                res.digits[len] = (digit + '0');
                //itoa(digit, res.digits[len], BASE);
                digit = 0;
                len = strlen(res.digits);
                numShift(&n2);
                continue;
            }
            numShift(&n2);
            if (flag)
            {
                res.exponent--;
                flag = 0;
            }
            if (len != 0)
                res.digits[len] = '0';
        }
        else
        {
            flag = 0;
            n1 = numsSub(n1, n2);
            digit++;
        }
        len = strlen(res.digits);
    }

    // Если 51-ая цифра не меньше 5 - округляем число
    if (res.digits[MAX_ANSWER] - '0' >= 5)
    {
        LDround(&res);
    }
    // Меняем знак и порядок для частного
    res.sign = d1->sign * d2->sign;
    res.exponent += d1->exponent - d2->exponent;
    return res;
}
