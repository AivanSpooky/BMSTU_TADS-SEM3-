#ifndef LONG_NUMS_H__

#define LONG_NUMS_H__

#include <stdio.h>
#include <stdbool.h>

#include "consts.h"
#include "err_codes.h"

#include "long_double.h"

/**
 * @brief nums - cтруктура для хранения цифр числа LongDouble,
 * @brief над которыми можно производить математические действия.
 * @param int digits[NUMS_SIZE] - массив цифр
*/
typedef struct
{
    int digits[NUMS_SIZE];
} nums;

/**
 * @brief Функция создает число типа nums на основе числа типа LongDouble
 * @param LongDouble *n - число типа LongDouble
 * @return Функция возвращает полученный тип nums.
*/
nums LDton(LongDouble *n);

/**
 * @brief Функция сдвигает цифры на одно место вправо, добавляя ноль в начало
 * @param nums *n - число типа nums
 * @return Функция ничего не возвращает.
*/
void numShift(nums *n);

bool numericCompare(nums n1, nums n2);
/**
 * @brief Функция выполняет разность (в столбик) двух типов nums
 * @param nums n1 - первый массив
 * @param nums n2 - второй массив
 * @return Функция возвращает разность типа nums.
*/
nums numsSub(nums n1, nums n2);

/**
 * @brief Функция сравнивает 2 массива nums
 * @param nums n1 - первый массив
 * @param nums n2 - второй массив
 * @return Функция возвращает значение аналогично функции strcmp.
*/
int numsCompare(nums n1, nums n2);

#endif
