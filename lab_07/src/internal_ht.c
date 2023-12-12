#include "internal_ht.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree_comparison.h"
#include <time.h>
#include <stdbool.h>
#define TESTS 100

size_t sizeofClosedAddressingHashTable(ClosedAddressingHashTable* hashtable)
{
    size_t size = sizeof(ClosedAddressingHashTable);
    for (int i = 0; i < hashtable->size; i++)
        if (hashtable->table[i] != NULL)
        {
            HashEntry* current = hashtable->table[i];
            while (current != NULL)
            {
                size += sizeof(HashEntry);
                current = current->next;
            }
        }
    return size;
}

int searchClosedAddressingHashTable(ClosedAddressingHashTable* hashtable, int key)
{
    int index = (key >= 0) ? (key % hashtable->size) : (hashtable->size + (key % hashtable->size));
    int comparisons = 0;
    clock_t start, end;
    double cpu_time_used;
    double times[TESTS];
    bool found = false;

    for (size_t i = 0; i < TESTS; i++)
    {
        index = (key >= 0) ? (key % hashtable->size) : (hashtable->size + (key % hashtable->size));
        comparisons = 0;
        start = clock();
        HashEntry* current = hashtable->table[index];
        while (current != NULL)
        {
            if (current->key == key)
            {
                found = true;
                goto end_state;
            }
            current = current->next;
            comparisons++;
        }
        end_state:
        comparisons++;
        end = clock();
        cpu_time_used = ((double)(end - start));
        times[i] = cpu_time_used;
    }
    double t_avg = avg(times, TESTS);

    if (found)
        printf("\nЧисло найдено в хеш-таблице\n");
    else
        printf("\nЧисло НЕ найдено в хеш-таблице\n");

    printf("Занимаемая память хеш-таблицей: %luБ\n", sizeofClosedAddressingHashTable(hashtable));
    printf("Среднее время поиска элемента <%d>: %.6lfмкс.\n", key, t_avg);  // Предполагая 100 замеров
    printf("Теоретическое количество сравниваний: (%d - %d)\n", 1, 5);
    printf("Количество сравниваний: %d\n", comparisons);
    return comparisons;
}

ClosedAddressingHashTable* restructureHashTable(ClosedAddressingHashTable* oldHashTable, int newTableSize) {
    ClosedAddressingHashTable* newHashTable = (ClosedAddressingHashTable*)malloc(sizeof(ClosedAddressingHashTable));
    if (newHashTable == NULL) {
        printf("Ошибка выделения памяти для новой хэш-таблицы\n");
        return NULL;
    }
    newHashTable->size = newTableSize;
    newHashTable->table = calloc(newTableSize, sizeof(HashEntry*));
    if (newHashTable->table == NULL) {
        printf("Ошибка выделения памяти для новой таблицы\n");
        free(newHashTable);
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashEntry* current = oldHashTable->table[i];
        while (current != NULL) {
            HashEntry* next = current->next;
            size_t newIndex = (current->key >= 0) ? (current->key % newTableSize) : (newTableSize + current->key % newTableSize);
            current->next = newHashTable->table[newIndex];
            newHashTable->table[newIndex] = current;
            current = next;
        }
    }

    // Освобождаем память, занятую старой таблицей
    // for (int i = 0; i < TABLE_SIZE; i++) {
    //     HashEntry* current = oldHashTable->table[i];
    //     while (current != NULL) {
    //         HashEntry* next = current->next;
    //         //free(current);
    //         current = next;
    //     }
    // }
    free(oldHashTable->table);
    free(oldHashTable);

    return newHashTable;
}

ClosedAddressingHashTable* createClosedAddressingHashTable(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nТакого файла не существует!\n");
        return NULL;
    }

    ClosedAddressingHashTable* hashtable = (ClosedAddressingHashTable*)malloc(sizeof(ClosedAddressingHashTable));
    if (hashtable == NULL) {
        printf("Ошибка выделения памяти для хэш-таблицы\n");
        return NULL;
    }
    hashtable->size = TABLE_SIZE;
    hashtable->table = calloc(hashtable->size, sizeof(HashEntry *));
    for (int i = 0; i < hashtable->size; i++) {
        hashtable->table[i] = NULL;
    }

    int key;
    while (fscanf(file, "%d", &key) == 1) {
        size_t index = (key >= 0) ? (key % hashtable->size) : (hashtable->size + (key % hashtable->size));
        //printf("%d %zu\n", key, index);
        HashEntry* newEntry = (HashEntry*)malloc(sizeof(HashEntry));
        if (newEntry == NULL) {
            printf("Ошибка выделения памяти для элемента хэш-таблицы\n");
            fclose(file);
            return NULL;
        }
        newEntry->key = key;
        newEntry->value = key;
        newEntry->next = NULL;

        if (hashtable->table[index] == NULL) {
            hashtable->table[index] = newEntry;
        } else {
            HashEntry* current = hashtable->table[index];
            size_t len = 1;
            while (current->next != NULL) {
                current = current->next;
                len++;
                //printf("%zu\n", len);
            }
            current->next = newEntry;
            if (len >= 5)
            {
                // Реструктуризация таблицы, в hashtable->table должно быть TABLE_SIZE+1 элементов
                printf("Хеш-таблица реструктурирована!\n");
                hashtable->size++;
                hashtable = restructureHashTable(hashtable, hashtable->size);
            } 
        }
    }

    // fclose(file);
    return hashtable;
}

void printClosedAddressingHashTable(ClosedAddressingHashTable* hashtable)
{
    printf("\nХеш-таблица с закрытой адресацией\n");
    for (int i = 0; i < hashtable->size; i++) {
        HashEntry* current = hashtable->table[i];
        while (current != NULL) {
            printf("Key: %d, Value: %d, Index: %d, Adress: %p\n", current->key, current->value, i, (void *)current);
            current = current->next;
        }
    }
}

void freeClosedAddressingHashTable(ClosedAddressingHashTable* hashtable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        if (hashtable->table[i]->key != DEFAULT)
            free(hashtable->table[i]);
    free(hashtable);
}