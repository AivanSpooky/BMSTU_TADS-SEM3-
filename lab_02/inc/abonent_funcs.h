#ifndef ABONENT_FUNCS_H__

#define ABONENT_FUNCS_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "consts.h"
#include "err_codes.h"

#define MAX_ABONENTS 50

#define MAX_NAME_LEN 20
#define MAX_PHONE_LEN 15
#define OTHER_INFO_LEN 50

// Структура для адреса
struct Address
{
    char street[OTHER_INFO_LEN];
    int house_number;
};

// Объединение для статуса
union Status
{
    struct
    {
        int day;
        int month;
        int year;
    } personal;
    struct
    {
        char position[OTHER_INFO_LEN];
        char organization[OTHER_INFO_LEN];
    } professional;
};

typedef enum
{
    PERSONAL,
    PROFFESSIONAL
} StatusType;

// Структура для абонента
typedef struct
{
    char last_name[MAX_NAME_LEN];
    char first_name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    struct Address address;
    StatusType status_type;
    union Status status;
} Abonent;

/**
 * @brief Функция выводит таблицу ключей
 * @param size_t *keys - массив ключей
 * @param size_t cnt - количество элементов
 * @return Функция ничего не возвращает
*/
void printKeyTable(size_t *keys, size_t cnt);

/**
 * @brief Функция выводит таблицу записей по массиву ключей
 * @param Abonent *abonents - массив записей
 * @param size_t *keys - массив ключей
 * @param size_t num_abonents - количество элементов
 * @return Функция ничего не возвращает
*/
void printAbonentsTable(Abonent *abonents, size_t num_abonents, size_t *keys);

/**
 * @brief Функция выводит таблицу записей не по массиву ключей
 * @param Abonent *abonents - массив записей
 * @param size_t *keys - массив ключей
 * @param size_t num_abonents - количество элементов
 * @return Функция ничего не возвращает
*/
void printAbonentsTableNoKey(Abonent *abonents, size_t num_abonents, size_t *keys);

/**
 * @brief Функция выводит все записи, др которых в течение недели
 * @param Abonent *abonents - массив записей
 * @param size_t *keys - массив ключей
 * @param size_t num_abonents - количество элементов
 * @return Функция ничего не возвращает
*/
void printWithinWeek(Abonent *abonents, size_t num_abonents, size_t *keys);

/**
 * @brief Функция удаляет из таблицы записи элемент по индексу
 * @param Abonent *abonents - массив записей
 * @param int index - индекс удаления
 * @param size_t *cnt - количество элементов
 * @return Функция ничего не возвращает
*/
void deleteAbonentByIndex(Abonent *abonents, size_t *cnt, int index);

/**
 * @brief Функция добавляет новую запись в конец таблицы
 * @param Abonent *abonents - массив записей
 * @param size_t *cnt - количество элементов
 * @return Функция ничего не возвращает
*/
int addInfo(Abonent *abonents, size_t *cnt);

// Определение функции типа сравнения структур по полю 
typedef int (*uni_cmp)(const void *l, const void*r);


int lastname_cmp(const void *l, const void *r);

int firstname_cmp(const void *l, const void *r);

int phone_cmp(const void *l, const void *r);

int address_cmp(const void *l, const void *r);


/**
 * @brief Функция сортирует массив элементов
 * @param void *ptr - массив элементов
 * @param size_t cnt - количество элементов в массиве
 * @param size_t size - размер элемента в массиве
 * @param uni_cmp cmp - функция сравнения двух элементов
 * @return Функция ничего не возвращает
*/
void mysort(Abonent *ptr, size_t cnt, size_t size, uni_cmp cmp);

/**
 * @brief Функция сортирует массив элементов
 * @param void *ptr - массив элементов
 * @param size_t cnt - количество элементов в массиве
 * @param size_t size - размер элемента в массиве
 * @param uni_cmp cmp - функция сравнения двух элементов
 * @param void *keys - массив ключей
 * @return Функция ничего не возвращает
*/
void mysort_keys(Abonent *ptr, size_t cnt, size_t size, uni_cmp cmp, void *keys);

/**
 * @brief Функция сортирует массив элементов
 * @param void *ptr - массив элементов
 * @param int left - левый индекс
 * @param int right - правый индекс
 * @param uni_cmp cmp - функция сравнения двух элементов
 * @param void *keys - массив ключей
 * @return Функция ничего не возвращает
*/
void qsort_keys(Abonent *abonents, size_t *keys, int left, int right, uni_cmp cmp);

// Функция определяет, находится ли др абонента в течение этой недели
int isWithinWeek(Abonent abonent);

#endif
