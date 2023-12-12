#ifndef LONG_DOUBLE_H__

#define LONG_DOUBLE_H__

#include <stdio.h>

#include "consts.h"

/**
 * @brief LongDouble - cтруктура для хранения действительного числа,
 * @brief записанного в нормализованном виде (с терминала).
 * @param int sign - знак числа (плюс или минус)
 * @param char digits[MAX_ANSWER] - массив для хранения цифр введенного числа
 * @param int exponent - порядок (экспонента) числа
*/
typedef struct
{
    int sign;
    char digits[MAX_ANSWER + 2];
    int exponent;
} LongDouble;

/**
 * @brief Функция округляет число типа LongDouble до 50 значащих цифр
 * @brief с помощью математического округления
 * @param LongDouble *n - число, которое необходимо округлить
 * @return Функция ничего не возвращает
*/
void LDround(LongDouble *n);

/**
 * @brief Функция выводит на экран число типа LongDouble
 * @brief в нормализованном виде с точностью 50 значащих цифр
 * @brief Для удобства в чтении цифр печатается специальная линейка
 * @param LongDouble *n - число, которое необходимо округлить
 * @return Функция ничего не возвращает
*/
void printLongDouble(LongDouble *n);

/**
 * @brief Функция создает число типа LongDouble по введеной
 * @brief пользователем строке с дополнительной проверкой на целый тип
 * @param LongDouble *n - новое число
 * @param char *s - буфер, из которого формируется число
 * @return Функция возвращает код ошибки.
*/
int writeInteger(LongDouble *n, char *s);

/**
 * @brief Функция создает число типа LongDouble по введеной
 * @brief пользователем строке
 * @param LongDouble *n - новое число
 * @param char *s - буфер, из которого формируется число
 * @return Функция возвращает код ошибки.
*/
int writeDouble(LongDouble *n, char *s);

/**
 * @brief Функция выполняет деление чисел типа LongDouble
 * @param LongDouble *d1 - первое число
 * @param LongDouble *d2 - второе число
 * @return Функция возвращает частное типа LongDouble.
*/
LongDouble division(LongDouble *d1, LongDouble *d2);

#endif
