#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "err_codes.h"

#include "json_funcs.h"
#include "abonent_funcs.h"
#include "menu.h"

#define DEFAULT 0

int main()
{
    // Создаем несколько записей абонентов
    Abonent abonents[MAX_ABONENTS];
    size_t cnt = 0;
    int rc = OK;
    run();
    rc = readAbonentsFromJSON("abonents.json", abonents, MAX_ABONENTS, &cnt);
    if (rc != OK)
    {
        return rc;
    }

    size_t keys[cnt];
    for (size_t i = 0; i < cnt; i++)
        keys[i] = i;
    //createJSON(abonents);

    size_t index = 0;
    int choice = DEFAULT;
    size_t sort_method = DEFAULT;
    size_t sort_type = DEFAULT;

    char tmp[200];

    while (choice != MAX_OPT)
    {
        choice = DEFAULT;
        
        print_menu();
        rc = get_choice(&choice);
        if (rc != OK)
            continue;
        //printf("%zu\n", cnt);
        switch(choice)
        {
            case 1:
                printAbonentsTableNoKey(abonents, cnt, keys);
                break;
            case 2:
                rc = addInfo(abonents, &cnt);
                if (rc == ERR_RANGE)
                    fgets(tmp, sizeof(tmp), stdin);
                else
                    keys[cnt - 1] = cnt - 1;
                break;
            case 3:
                rc = get_index(&index, cnt);
                if (rc == OK)
                {
                    deleteAbonentByIndex(abonents, &cnt, index);
                    keys[cnt] = (size_t)NULL;
                }
                break;
            case 4:
                rc = get_sort_type(&sort_type);
                if (rc != OK)
                    break;
                rc = get_sort_method(&sort_method);
                if (rc != OK)
                    break;
                if (sort_type == 2)
                {
                    if (sort_method == 1)
                    {
                        qsort(abonents, cnt, sizeof(Abonent), lastname_cmp);
                        printf("\nМассив абонентов был успешно отсортирован!\n");
                    }
                    else
                    {
                        qsort_keys(abonents, keys, 0, cnt - 1, lastname_cmp);
                        printf("\nМассив ключей был успешно отсортирован!\n");
                    }
                    break;
                }
                if (sort_method == 1)
                {
                    for (size_t i = 0; i < cnt; i++)
                        keys[i] = i;
                    mysort(abonents, cnt, sizeof(Abonent), lastname_cmp);
                    printf("\nМассив абонентов был успешно отсортирован!\n");
                }
                else
                {
                    mysort_keys(abonents, cnt, sizeof(size_t), lastname_cmp, keys);
                    printf("\nМассив ключей был успешно отсортирован!\n");
                }
                break;
            case 5:
                rc = get_sort_type(&sort_type);
                if (rc != OK)
                    break;
                rc = get_sort_method(&sort_method);
                if (rc != OK)
                    break;
                if (sort_type == 2)
                {
                    if (sort_method == 1)
                    {
                        qsort(abonents, cnt, sizeof(Abonent), firstname_cmp);
                        printf("\nМассив абонентов был успешно отсортирован!\n");
                    }
                    else
                    {
                        qsort_keys(abonents, keys, 0, cnt - 1, firstname_cmp);
                        printf("\nМассив ключей был успешно отсортирован!\n");
                    }
                    break;
                }
                if (sort_method == 1)
                {
                    for (size_t i = 0; i < cnt; i++)
                        keys[i] = i;
                    mysort(abonents, cnt, sizeof(Abonent), firstname_cmp);
                    printf("\nМассив абонентов был успешно отсортирован!\n");
                }
                else
                {
                    mysort_keys(abonents, cnt, sizeof(size_t), firstname_cmp, keys);
                    printf("\nМассив ключей был успешно отсортирован!\n");
                }
                break;
            case 6:
                rc = get_sort_type(&sort_type);
                if (rc != OK)
                    break;
                rc = get_sort_method(&sort_method);
                if (rc != OK)
                    break;
                if (sort_type == 2)
                {
                    if (sort_method == 1)
                    {
                        qsort(abonents, cnt, sizeof(Abonent), phone_cmp);
                        printf("\nМассив абонентов был успешно отсортирован!\n");
                    }
                    else
                    {
                        qsort_keys(abonents, keys, 0, cnt - 1, phone_cmp);
                        printf("\nМассив ключей был успешно отсортирован!\n");
                    }
                    break;
                }
                if (sort_method == 1)
                {
                    for (size_t i = 0; i < cnt; i++)
                        keys[i] = i;
                    mysort(abonents, cnt, sizeof(Abonent), phone_cmp);
                    printf("\nМассив абонентов был успешно отсортирован!\n");
                }
                else
                {
                    mysort_keys(abonents, cnt, sizeof(size_t), phone_cmp, keys);
                    printf("\nМассив ключей был успешно отсортирован!\n");
                }
                break;
            case 7:
                rc = get_sort_type(&sort_type);
                if (rc != OK)
                    break;
                rc = get_sort_method(&sort_method);
                if (rc != OK)
                    break;
                if (sort_type == 2)
                {
                    if (sort_method == 1)
                    {
                        qsort(abonents, cnt, sizeof(Abonent), address_cmp);
                        printf("\nМассив абонентов был успешно отсортирован!\n");
                    }
                    else
                    {
                        qsort_keys(abonents, keys, 0, cnt - 1, address_cmp);
                        printf("\nМассив ключей был успешно отсортирован!\n");
                    }
                    break;
                }
                if (sort_method == 1)
                {
                    for (size_t i = 0; i < cnt; i++)
                        keys[i] = i;
                    mysort(abonents, cnt, sizeof(Abonent), address_cmp);
                    printf("\nМассив абонентов был успешно отсортирован!\n");
                }
                else
                {
                    mysort_keys(abonents, cnt, sizeof(size_t), address_cmp, keys);
                    printf("\nМассив ключей был успешно отсортирован!\n");
                }
                break;
            case 8:
                printf("Сравнение ресурсных и временных затрат сортировки абонентов:\n");
                rc = sort_cmp(abonents, cnt, keys);
                if (rc != OK)
                {
                    printf("Ошибка!\n");
                }
                else
                {
                    printf("Время сортировки считалось как среднее из 100 замеров\n");
                }
                break;
            case 9:
                printWithinWeek(abonents, cnt, keys);
                break;
            case 10:
                printKeyTable(keys, cnt);
                break;
            case 11:
                printAbonentsTable(abonents, cnt, keys);
                break;
            case 12:
                choice = MAX_OPT;
                break;
            default:  
                break;
        }
    }
    printf("\nДо встречи!\n");
    return rc;
}