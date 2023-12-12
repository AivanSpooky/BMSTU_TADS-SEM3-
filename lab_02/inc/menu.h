#ifndef MENU_H__

#define MENU_H__

#include <stdio.h>
#include "consts.h"
#include "abonent_funcs.h"

/**
 * @brief Функция сортирует массив элементов
 * @param void *ptr - массив элементов
 * @param int left - левый индекс
 * @param int right - правый индекс
 * @param uni_cmp cmp - функция сравнения двух элементов
 * @param void *keys - массив ключей
 * @return Функция ничего не возвращает
*/
void run();

void print_menu();

int get_choice(int *choice);

int get_index(size_t *index, size_t cnt);

int get_sort_method(size_t *sort_method);

int get_sort_type(size_t *sort_type);

int sort_cmp(Abonent *abonents, size_t cnt, size_t *keys);

#endif