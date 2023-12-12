#include "menu.h"
#include "err_codes.h"
#include <time.h>
#include "consts.h"
#include <string.h>
#include <stdlib.h>
#include "abonent_funcs.h"

#define DIF_TESTS 4
#define MAX_TESTS 100

void run()
{
    printf("Здравствуйте!\nДанная программа работает с абонентами, указанными в файле.\nУ каждого абонента есть:\n");
    printf("- Фамилия (20 англ.букв)\n");
    printf("- Имя (20 англ.букв)\n");
    printf("- Телефон (формат: +71234567890)\n");
    printf("- Адрес (улица и номер дома)\n");
    printf("- Статус (personal/proffessional)\n");
    printf("Сейчас считаю информацию об абонентах из файла...\n");
}

void print_menu()
{
    printf("\nMenu:\n");
    printf("|%-30s\n", "1. Вывести таблицу");
    printf("|%-30s\n", "2. Добавить запись в таблицу");
    printf("|%-30s\n", "3. Удалить запись из таблицы (по индексу)");
    printf("|%-30s\n", "4. Отсортировать по Фамилии");
    printf("|%-30s\n", "5. Отсортировать по Имени");
    printf("|%-30s\n", "6. Отсортировать по номеру Телефона");
    printf("|%-30s\n", "7. Отсортировать по Адресу");
    printf("|%-30s\n", "8. Сравнить сортировку массива записей и массива ключей");
    printf("|%-30s\n", "9. Найти друзей, которых необходимо поздравить в течение недели");
    printf("|%-30s\n", "10. Вывести таблицу ключей");
    printf("|%-30s\n", "11. Вывести таблицу по ключам");
    printf("|%-30s\n", "12. Выйти из программы");
}

int get_choice(int *choice)
{
    printf("\n");
    char tmp[200];
    printf("Введите номер пункта меню: ");
    if (scanf("%d", choice) != 1)
    {
        fgets(tmp, sizeof(tmp), stdin);
        printf("Неправильный ввод пункта меню!\n");
        return ERR_IO;
    }
    fgets(tmp, sizeof(tmp), stdin);
    size_t len = strlen(tmp);
    if (len != 1)
    {
        printf("Неправильный ввод пункта меню!\n");
        return ERR_IO;
    }
    if (*choice < 0)
    {
        printf("Пункт меню должен быть неотрицательным!\n");
        return ERR_DATA;
    }
    if (*choice > MAX_OPT)
    {
        printf("Вы выбрали несуществующий пункт меню!\n");
        return ERR_OVERFLOW;
    }
    printf("\n");
    return OK;
}

int get_index(size_t *index, size_t cnt)
{
    char tmp[200];
    printf("Введите номер записи (индекс): ");
    if (scanf("%zu", index) != 1)
    {
        fgets(tmp, sizeof(tmp), stdin);
        printf("Неправильный ввод индекса!\n");
        return ERR_IO;
    }
    fgets(tmp, sizeof(tmp), stdin);
    size_t len = strlen(tmp);
    if (len != 1)
    {
        printf("Неправильный ввод индекса!\n");
        return ERR_IO;
    }
    if (*index >= cnt)
    {
        printf("Вы выбрали несуществующий индекс!\n");
        return ERR_OVERFLOW;
    }
    return OK;
}

int get_sort_method(size_t *sort_method)
{
    char tmp[200];
    printf("Выберите метод сортировки:\n");
    printf("1. Сортировка массива записей\n");
    printf("2. Сортировка массива ключей\n");
    printf(": ");
    if (scanf("%zu", sort_method) != 1)
    {
        fgets(tmp, sizeof(tmp), stdin);
        printf("Неправильный ввод метода сортировки!\n");
        return ERR_IO;
    }
    fgets(tmp, sizeof(tmp), stdin);
    size_t len = strlen(tmp);
    if (len != 1)
    {
        printf("Неправильный ввод метода сортировки!\n");
        return ERR_IO;
    }
    if (*sort_method > 2 || *sort_method == 0)
    {
        printf("Вы выбрали несуществующий метода сортировки!\n");
        return ERR_OVERFLOW;
    }
    return OK;
}

int get_sort_type(size_t *sort_type)
{
    char tmp[200];
    printf("Выберите тип сортировки:\n");
    printf("1. Сортировка расческой\n");
    printf("2. Быстрая сортировка (qsort)\n");
    printf(": ");
    if (scanf("%zu", sort_type) != 1)
    {
        fgets(tmp, sizeof(tmp), stdin);
        printf("Неправильный ввод типа сортировки!\n");
        return ERR_IO;
    }
    fgets(tmp, sizeof(tmp), stdin);
    size_t len = strlen(tmp);
    if (len != 1)
    {
        printf("Неправильный ввод типа сортировки!\n");
        return ERR_IO;
    }
    if (*sort_type > 2 || *sort_type == 0)
    {
        printf("Вы выбрали несуществующий типа сортировки!\n");
        return ERR_OVERFLOW;
    }
    return OK;
}

double eff(double t1, double t2)
{
    return ((t1 - t2) / t1 * 100);
}

int get_times(Abonent *abonents, size_t cnt, size_t *keys, double times[DIF_TESTS][MAX_TESTS], size_t ind)
{
    if (ind >= MAX_TESTS)
    {
        printf("Ошибка (слишком много замеров)!");
        return ERR_RANGE;
    }
    //printf("ERR\n");
    Abonent *ab1 = (Abonent *)malloc(cnt * sizeof(Abonent));
    if (!ab1)
    {
        printf("\nОшибка при выделении памяти!\n");
        return ERR_MEM;
    }
    Abonent *ab2 = (Abonent *)malloc(cnt * sizeof(Abonent));
    if (!ab2)
    {
        free(ab1);
        printf("\nОшибка при выделении памяти!\n");
        return ERR_MEM;
    }
    Abonent *ab3 = (Abonent *)malloc(cnt * sizeof(Abonent));
    if (!ab3)
    {
        free(ab1);
        free(ab2);
        printf("\nОшибка при выделении памяти!\n");
        return ERR_MEM;
    }
    Abonent *ab4 = (Abonent *)malloc(cnt * sizeof(Abonent));
    if (!ab4)
    {
        free(ab1);
        free(ab2);
        free(ab3);
        printf("\nОшибка при выделении памяти!\n");
        return ERR_MEM;
    }
    size_t *k1 = (size_t *)malloc(cnt * sizeof(size_t));
    if (!k1)
    {
        free(ab1);
        free(ab2);
        free(ab3);
        free(ab4);
        printf("\nОшибка при выделении памяти!\n");
        return ERR_MEM;
    }
    size_t *k2 = (size_t *)malloc(cnt * sizeof(size_t));
    if (!k2)
    {
        free(ab1);
        free(ab2);
        free(ab3);
        free(ab4);
        free(k1);
        printf("\nОшибка при выделении памяти!\n");
        return ERR_MEM;
    }
    memcpy(ab1, abonents, cnt * sizeof(Abonent));
    memcpy(ab2, abonents, cnt * sizeof(Abonent));
    memcpy(ab3, abonents, cnt * sizeof(Abonent));
    memcpy(ab4, abonents, cnt * sizeof(Abonent));
    memcpy(k1, keys, cnt * sizeof(size_t));
    memcpy(k2, keys, cnt * sizeof(size_t));
    // Вычисление времен
    clock_t start, end;
    // расческа - таблица
    start = clock();
    mysort(ab1, cnt, sizeof(Abonent), lastname_cmp);
    end = clock();
    double t1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    // быстрая - таблица
    start = clock();
    qsort(ab2, cnt, sizeof(Abonent), lastname_cmp);
    end = clock();
    double t2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    // расческа - ключи
    start = clock();
    mysort_keys(ab3, cnt, sizeof(size_t), lastname_cmp, k1);
    end = clock();
    double t3 = ((double)(end - start)) / CLOCKS_PER_SEC;
    // быстрая - ключи
    start = clock();
    qsort_keys(ab4, k2, 0, cnt - 1, lastname_cmp);
    end = clock();
    double t4 = ((double)(end - start)) / CLOCKS_PER_SEC;

    times[0][ind] = t1;
    times[1][ind] = t2;
    times[2][ind] = t3;
    times[3][ind] = t4;
    free(ab1);
    free(ab2);
    free(ab3);
    free(ab4);
    free(k1);
    free(k2);
    return OK;
}

double avg(double *nums, size_t cnt)
{
    double sum = 0;
    for (size_t i = 0; i < cnt; i++)
    {
        sum += nums[i];
    }
    return sum / cnt;
}

int sort_cmp(Abonent *abonents, size_t cnt, size_t *keys)
{
    size_t rc = OK;
    size_t s1 = cnt*sizeof(Abonent), s2 = cnt*(sizeof(Abonent) + sizeof(size_t));

    double times[DIF_TESTS][MAX_TESTS];
    
    for (size_t i = 0; i < MAX_TESTS; i++)
    {
        rc = get_times(abonents, cnt, keys, times, i);
        if (rc != OK)
        {
            return rc;
        }
    }
    double t1 = avg(times[0], MAX_TESTS), t2 = avg(times[1], MAX_TESTS), t3 = avg(times[2], MAX_TESTS), t4 = avg(times[3], MAX_TESTS);
    // Эффективность по времени в %.
    double er1 = eff(t1, t2), er2 = eff(t3, t4), ec1 = eff(t1, t3), ec2 = eff(t2, t4), et = eff(t1, t4);


    printf("Сравнение для (n = %zu):\n", cnt);
    printf("+---------+---------------------++-------------------++-------------++\n");
    printf("|         | Расческа            || Быстрая           ||-------------++\n");
    printf("+---------+---------------------++-------------------++-------------++\n");
    printf("| Таблица | %-.8lfс. %zuБ  || %-.8lfс. %zuБ|| %-.8lf%%||\n", t1, s1, t2, s1, er1);
    printf("+---------+---------------------++-------------------++-------------++\n");
    printf("| Ключи   | %-.8lfс. %zuБ  || %-.8lfс. %zuБ|| %-.8lf%%||\n", t3, s2, t4, s2, er2);
    printf("+---------+---------------------++-------------------++-------------++\n");
    printf("|---------| %-.8lf%%        || %-.8lf%%      || %-.8lf%%||\n", ec1, ec2, et);
    printf("+---------+---------------------++-------------------++-------------++\n");

    return OK;
}
