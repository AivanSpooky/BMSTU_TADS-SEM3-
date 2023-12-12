#include "long_nums.h"

#include <string.h>
#include <stdbool.h>
#include <ctype.h>

nums LDton(LongDouble *n)
{
    nums res;
    size_t len = strlen(n->digits);
    for (size_t i = 0; i < NUMS_SIZE; i++)
    {
        if (i < len)
        {
            res.digits[i] = n->digits[i] - '0';
        }
        else
        {
            res.digits[i] = 0;
        }
    }
    return res;
}

void numShift(nums *n)
{
    for (size_t i = NUMS_SIZE - 1; i > 0; i--)
        n->digits[i] = n->digits[i - 1];
    n->digits[0] = 0;
}

bool numericCompare(nums n1, nums n2)
{
    nums d1 = n1;
    nums d2 = n2;
    size_t cnt1 = 0, cnt2 = 0;
    while (d1.digits[NUMS_SIZE - 1] == 0 && cnt1 < NUMS_SIZE)
    {
        numShift(&d1);
        cnt1++;
    }
    while (d2.digits[NUMS_SIZE - 1] == 0 && cnt2 < NUMS_SIZE)
    {
        numShift(&d2);
        cnt2++;
    }
    // if (numsCompare(d1, d2) >= 0 && cnt1 == cnt2)
    //     return true;
    return false;

}

nums numsSub(nums n1, nums n2)
{
    nums res;
    int reduct = 0;
    for (int i = NUMS_SIZE - 1; i >= 0; i--)
    {
        int p = n1.digits[i];
        int q = n2.digits[i];

        // Выполняем умножение, учитывая возможное изменение порядков
        if (p >= q)
        {
            res.digits[i] = (n1.digits[i]) - (n2.digits[i]) - reduct;
            reduct = 0;
        }
        else
        {
            res.digits[i] = BASE - reduct + (n1.digits[i]) - (n2.digits[i]);
            reduct = 1;
        }
    }
    return res;
}

int numsCompare(nums n1, nums n2)
{
    // Сравниваем по цифрам
    for (size_t i = 0; i < NUMS_SIZE; i++)
    {
        int p = n1.digits[i];
        int q = n2.digits[i];
        if (p != q)
            return p - q;
    }
    return OK;
}
