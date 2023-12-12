#include "external_ht.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_comparison.h"
#include <time.h>
#define TESTS 100

// Функция для поиска целого числа в хеш-таблице с выводом информации
bool findNumberInExternalCacheHashTable(hashtable_t* hashtable, int key, bool info)
{
    if (hashtable == NULL || hashtable->table == NULL)
    {
        printf("\nХеш-таблица пуста!\n");
        return false;
    }
    clock_t start, end;
    double cpu_time_used;
    int comparisons = 0;
    double times[TESTS];
    int index;
    bool found = false;

    for (size_t i = 0; i < TESTS; i++)
    {
        comparisons = 0;
        start = clock(); // стартуем!

        index = (key >= 0) ? (key % hashtable->size) : (hashtable->size + (key % hashtable->size));
        while (hashtable->table[index].key != key && hashtable->table[index].key != -1)
        {
            index = (index + 1) % hashtable->size;
            comparisons++;
        }
        comparisons++;
        end = clock(); // заканчиваем((
        cpu_time_used = ((double) (end - start));
        times[i] = cpu_time_used;
    }
    double t_avg = avg(times, TESTS);
    // t2_avg = avg(t2_arr, tests);
    // double eff_ = eff(t2_avg, t1_avg);
    if (hashtable->table[index].key == key)
    {
        if (info)
            printf("\nЧисло найдено в хеш-таблице\n");
        found = true;
    }
    else
    {
        if (info)
            printf("\nЧисло НЕ найдено в хеш-таблице\n");
        found = false;
    }
    if (info)
    {
        printf("Занимаемая память хеш-таблицей: %luБ\n", sizeof(entry_t) * hashtable->size + sizeof(hashtable_t));
        printf("Среднее время поиска элемента <%d>: %.6lfмкс.\n", key, t_avg);  // Предполагая 100 замеров
        printf("Теоретическое количество сравниваний: (%d - %d)\n", 1, hashtable->size);
        printf("Количество сравниваний: %d\n", comparisons);
    }

    return found;
}

hashtable_t* createExternalCacheHashTable(const char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nТакого файла не существует!\n");
        return NULL;
    }

    hashtable_t* hashtable = (hashtable_t*)malloc(sizeof(hashtable_t));
    hashtable->size = TABLE_SIZE;
    hashtable->table = (entry_t*)malloc(TABLE_SIZE * sizeof(entry_t));
    for (int i = 0; i < TABLE_SIZE; i++)
        hashtable->table[i].key = -1;  // Используем -1 в качестве пустого значения ключа

    int key;
    int* keys = (int*)malloc(TABLE_SIZE * sizeof(int));  // Создаем массив для хранения ключей
    int numKeys = 0;  // Переменная для отслеживания количества уникальных ключей
    hashtable->cnt = 0;
    while (fscanf(file, "%d", &key) == 1)
    {
        // Проверяем, есть ли уже такой ключ в массиве
        int duplicate = 0;
        for (int i = 0; i < numKeys; i++)
        {
            if (keys[i] == key)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
        {
            printf("\nВ файле найдены дубликаты вершин!\n");
            free(keys);
            free(hashtable->table);
            free(hashtable);
            fclose(file);
            return NULL;
        }

        keys[numKeys] = key;
        numKeys++;

        if (hashtable->cnt >= hashtable->size) {
            printf("Хеш-таблица реструктурирована!\n");
            // Реструктуризация хеш-таблицы
            int oldSize = hashtable->size;
            hashtable->size *= 2;
            entry_t* oldTable = hashtable->table;
            hashtable->table = (entry_t*)malloc(hashtable->size * sizeof(entry_t));
            for (int i = 0; i < hashtable->size; i++)
                hashtable->table[i].key = -1;

            for (int i = 0; i < oldSize; i++) {
                if (oldTable[i].key != -1) {
                    int newIndex = (oldTable[i].key >= 0) ? (oldTable[i].key % hashtable->size) : (hashtable->size + oldTable[i].key % hashtable->size);
                    //printf("%d %d\n", oldTable[i].key, newIndex);
                    while (hashtable->table[newIndex].key != -1) {
                        newIndex = (newIndex + 1) % hashtable->size;
                        //printf("%d\n", newIndex);
                    }
                    hashtable->table[newIndex].key = oldTable[i].key;
                    hashtable->table[newIndex].value = oldTable[i].value;
                }
            }
            //free(oldTable);
        }

        int index = (key >= 0) ? (key % hashtable->size) : (hashtable->size + (key % hashtable->size));
        // printf("value:%d %d\n", key, index);
        while (hashtable->table[index].key != -1) {
            index = (index + 1) % hashtable->size;  // Простое рехеширование
        }
        hashtable->table[index].key = key;
        hashtable->table[index].value = key;  // Просто используем ключ в качестве значения
        hashtable->cnt++;
    }
    // printf("AHHAHAH\n");
    //free(keys);
    // fclose(file);
    printf("Хеш-таблица c открытой адресацией (и внешним хешированием) успешно создана!\n");
    return hashtable;
}

void printHashtable(hashtable_t *ht) {
    printf("\nХеш-таблица с открытой адресацией\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i].key != -1) {
            printf("Key: %d, Value: %d, Index: %d\n", ht->table[i].key, ht->table[i].value, i);
        }
    }
}

void freeExternalCacheHashTable(hashtable_t* hashtable)
{
    free(hashtable->table);
    free(hashtable);
}