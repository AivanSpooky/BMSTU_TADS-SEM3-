#include "abonent_funcs.h"
#include <stdbool.h>
#include <time.h>

bool isValidPhone(const char *phone)
{
    // Проверяем длину номера телефона (должна быть 12 символов)
    if (strlen(phone) != 12)
    {
        return false;
    }

    // Проверяем, что первый символ - это '+'
    if (phone[0] != '+')
    {
        return false;
    }

    // Проверяем, что остальные символы - цифры
    for (int i = 1; i < 12; i++)
    {
        if (!isdigit(phone[i]))
        {
            return false;
        }
    }

    // Если все проверки пройдены, номер телефона считается корректным
    return true;
}

void printKeyTable(size_t *keys, size_t cnt)
{
    printf("\n-----------\n");
    printf("|# | Ключ |\n");
    printf("-----------\n");
    for (size_t i = 0; i < cnt; i++)
    {
        printf("|%02zu|  %02zu  |\n", i, keys[i]);
    }
    printf("-----------\n");
}
// Функция для вывода информации об абонентах в виде таблицы
void printAbonentsTable(Abonent *abonents, size_t num_abonents, size_t *keys)
{
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("|# | Фамилия             | Имя                | Телефон       | Адрес                   | Информация                 \n");
    printf("|--|---------------------|--------------------|---------------|-------------------------|----------------------------\n");

    for (size_t i = 0; i < num_abonents; i++)
    {
        size_t ind = keys[i];
        printf("|%02zu| %-20s|%-20s|%-15s|%20s,h#%02d|",
               i, abonents[ind].last_name, abonents[ind].first_name, abonents[ind].phone, abonents[ind].address.street, abonents[ind].address.house_number);

        if (abonents[ind].status_type == PERSONAL)
        {
            printf("Дата рождения: %d-%02d-%02d \n",
                   abonents[ind].status.personal.year, abonents[ind].status.personal.month, abonents[ind].status.personal.day);
        }
        else
        {
            printf("Должность: %s, Организация: %s \n",
                   abonents[ind].status.professional.position, abonents[ind].status.professional.organization);
        }
    }
    if (num_abonents == 0)
        printf("|  | Пусто\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
}

void printAbonentsTableNoKey(Abonent *abonents, size_t num_abonents, size_t *keys)
{
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("|# | Фамилия             | Имя                | Телефон       | Адрес                   | Информация                 \n");
    printf("|--|---------------------|--------------------|---------------|-------------------------|----------------------------\n");

    for (size_t i = 0; i < num_abonents; i++)
    {
        size_t ind = keys[i];
        (void) ind;
        printf("|%02zu| %-20s|%-20s|%-15s|%20s,h#%02d|",
               i, abonents[i].last_name, abonents[i].first_name, abonents[i].phone, abonents[i].address.street, abonents[i].address.house_number);

        if (abonents[i].status_type == PERSONAL)
        {
            printf("Дата рождения: %d-%02d-%02d \n",
                   abonents[i].status.personal.year, abonents[i].status.personal.month, abonents[i].status.personal.day);
        }
        else
        {
            printf("Должность: %s, Организация: %s \n",
                   abonents[i].status.professional.position, abonents[i].status.professional.organization);
        }
    }
    if (num_abonents == 0)
        printf("|  | Пусто\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
}

void printWithinWeek(Abonent *abonents, size_t num_abonents, size_t *keys)
{
    size_t flag = 0;
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("|# | Фамилия             | Имя                | Телефон       | Адрес                   | Информация                 \n");
    printf("|--|---------------------|--------------------|---------------|-------------------------|----------------------------\n");
    for (size_t i = 0; i < num_abonents; i++)
    {
        size_t ind = keys[i];
        if (abonents[ind].status_type == PERSONAL)
        {
            if (isWithinWeek(abonents[ind]))
            {
                flag = 1;
                printf("|%02zu| %-20s|%-20s|%-15s|%20s,h#%02d|",
                   i, abonents[ind].last_name, abonents[ind].first_name, abonents[ind].phone, abonents[ind].address.street, abonents[ind].address.house_number);
                printf("Дата рождения: %d-%02d-%02d \n",
                   abonents[ind].status.personal.year, abonents[ind].status.personal.month, abonents[ind].status.personal.day);
            }

        }
    }
    if (!flag)
        printf("|  | Пусто\n");
    printf("|--|---------------------|--------------------|---------------|-------------------------|----------------------------\n");

}

void deleteAbonentByIndex(Abonent *abonents, size_t *cnt, int index)
{
    if (index < 0 || index >= (int)*cnt)
    {
        printf("Некорректный индекс для удаления.\n");
        return;
    }

    // Сдвигаем все элементы после удаляемого на одну позицию назад
    for (size_t i = index; i < *cnt - 1; i++)
    {
        abonents[i] = abonents[i + 1];
    }

    // Уменьшаем счетчик элементов на 1
    (*cnt)--;
    printf("\nЗапись успешно удалена!\n");
}

int addInfo(Abonent *abonents, size_t *cnt)
{
    if (*cnt >= MAX_ABONENTS)
    {
        printf("Количество абонентов максимально! (больше нельзя добавить)\n");
        return ERR_RANGE;
    }

    Abonent newAbonent;
    char tmp[2]; // Дополнительный буфер для символа перехода на новую строку

    char last_name[MAX_NAME_LEN + 2];

    printf("Введите фамилию: (20 англ. символов): ");
    if (!fgets(last_name, sizeof(last_name), stdin))
    {
        printf("Ошибка при вводе фамилии.\n");
        return ERR_EMPTY;
    }
    size_t len = strlen(last_name);
    //printf("%s - %zu\n", last_name, len);
    if (last_name[len - 1] == '\n')
        last_name[--len] = '\0';
    if (!len)
    {
        printf("Ошибка при вводе (ничего не введено).\n");
        return ERR_IO;
    }
    if (len > MAX_NAME_LEN)
    {
        printf("Ошибка при вводе (введено слишком много символов).\n");
        return ERR_RANGE;
    }
    // if (allspace(last_name))
    //     return ERR_DATA;
    strncpy(newAbonent.last_name, last_name, MAX_NAME_LEN);
    // fgets(tmp, sizeof(tmp), stdin);

    char name[MAX_NAME_LEN + 2];
    printf("Введите имя: (20 англ. символов): ");
    if (!fgets(name, sizeof(name), stdin))
    {
        printf("Ошибка при вводе имени.\n");
        return ERR_EMPTY;
    }
    len = strlen(name);
    //printf("%s - %zu\n", title, len);
    if (name[len - 1] == '\n')
        name[--len] = '\0';
    if (!len)
    {
        printf("Ошибка при вводе (ничего не введено).\n");
        return ERR_IO;
    }
    if (len > MAX_NAME_LEN)
    {
        printf("Ошибка при вводе (введено слишком много символов).\n");
        return ERR_RANGE;
    }
    // if (allspace(name))
    //     return ERR_DATA;
    strncpy(newAbonent.first_name, name, MAX_NAME_LEN);

    char phone[MAX_PHONE_LEN + 2];
    printf("Введите номер телефона (+71234567890) - 12 символов, начиная с +: ");
    if (!fgets(phone, sizeof(phone), stdin))
    {
        printf("Ошибка при вводе.\n");
        return ERR_EMPTY;
    }
    len = strlen(phone);
    //printf("%s - %zu\n", title, len);
    if (phone[len - 1] == '\n')
        phone[--len] = '\0';
    if (!len)
    {
        printf("Ошибка при вводе (ничего не введено).\n");
        return ERR_IO;
    }
    if (len > MAX_PHONE_LEN)
    {
        printf("Ошибка при вводе (введено слишком много символов).\n");
        return ERR_RANGE;
    }
    if (!isValidPhone(phone))
    {
        printf("Некорректный номера телефона.\n");
        return ERR_IO;
    }
    // if (allspace(phone))
    // {
    //     printf("Ошибка при вводе (введены все пробельные символы).\n");
    //     return ERR_DATA;
    // }
    strncpy(newAbonent.phone, phone, MAX_PHONE_LEN);

   

    printf("Введите улицу: ");
    char street[OTHER_INFO_LEN + 2];
    if (!fgets(street, sizeof(street), stdin))
    {
        printf("Ошибка при вводе.\n");
        return ERR_EMPTY;
    }
    len = strlen(street);
    //printf("%s - %zu\n", title, len);
    if (street[len - 1] == '\n')
        street[--len] = '\0';
    if (!len)
    {
        printf("Ошибка при вводе (ничего не введено).\n");
        return ERR_IO;
    }
    if (len > MAX_NAME_LEN)
    {
        printf("Ошибка при вводе (введено слишком много символов).\n");
        return ERR_RANGE;
    }
    // if (allspace(street))
    // {
    //     printf("Ошибка при вводе (введены все пробельные символы).\n");
    //     return ERR_DATA;
    // }
    strncpy(newAbonent.address.street, street, MAX_PHONE_LEN);

    // if (!isValidPhone(phone))
    // {
    //     printf("Некорректный номера телефона.\n");
    //     return ERR_IO;
    // }
    // strcpy(newAbonent.phone, phone);

    printf("Введите номер дома: ");
    if (scanf("%d", &newAbonent.address.house_number) != 1)
    {
        printf("Ошибка при вводе номера дома.\n");
        return ERR_IO;
    }
    if (newAbonent.address.house_number <= 0)
    {
        printf("Номер дома должен быть положительным.\n");
        return ERR_IO;
    }
    fgets(tmp, sizeof(tmp), stdin);

    char status[15];
    printf("Выберите тип статуса (personal/professional): ");
    fgets(status, sizeof(status), stdin);
    if (strcmp(status, "personal\n") == 0)
    {
        newAbonent.status_type = PERSONAL;
        printf("Введите день рождения: ");
        if (scanf("%d", &newAbonent.status.personal.day) != 1)
        {
            printf("Ошибка при вводе дня рождения.\n");
            return ERR_IO;
        }
        if (newAbonent.status.personal.day > 31 || newAbonent.status.personal.day <= 0)
        {
            printf("День рождения должен быть в диапазоне (от 1 до 31).\n");
            return ERR_IO;
        }
        getchar(); // Считываем символ перехода на новую строку, оставшийся после scanf

        printf("Введите месяц рождения: ");
        if (scanf("%d", &newAbonent.status.personal.month) != 1)
        {
            printf("Ошибка при вводе месяца рождения.\n");
            return ERR_IO;
        }
        if (newAbonent.status.personal.month > 12 || newAbonent.status.personal.month <= 0)
        {
            printf("Месяц должен быть в диапазоне (от 1 до 12).\n");
            return ERR_IO;
        }
        getchar(); // Считываем символ перехода на новую строку, оставшийся после scanf

        printf("Введите год рождения: ");
        if (scanf("%d", &newAbonent.status.personal.year) != 1)
        {
            printf("Ошибка при вводе года рождения.\n");
            return ERR_IO;
        }
        if (newAbonent.status.personal.year <= 0)
        {
            printf("Год должен быть положительным.\n");
            return ERR_IO;
        }
        getchar(); // Считываем символ перехода на новую строку, оставшийся после scanf
    }
    else if (strcmp(status, "professional\n") == 0)
    {
        newAbonent.status_type = PROFFESSIONAL;
        printf("Введите должность: ");
        fgets(newAbonent.status.professional.position, sizeof(newAbonent.status.professional.position), stdin);
        newAbonent.status.professional.position[strcspn(newAbonent.status.professional.position, "\n")] = '\0';

        printf("Введите организацию: ");
        fgets(newAbonent.status.professional.organization, sizeof(newAbonent.status.professional.organization), stdin);
        newAbonent.status.professional.organization[strcspn(newAbonent.status.professional.organization, "\n")] = '\0';
    }
    else
    {
        printf("Ошибка: некорректный тип статуса.\n");
        return ERR_IO;
    }

    abonents[*cnt] = newAbonent;
    (*cnt)++;
    printf("Запись успешно добавлена в таблицу.\n");

    return OK;
}

// ФУНКЦИИ СРАВНЕНИЯ
int lastname_cmp(const void *l, const void *r)
{
    const Abonent *pl = l;
    const Abonent *pr = r;
    return strcmp(pl->last_name, pr->last_name);
}

int firstname_cmp(const void *l, const void *r)
{
    const Abonent *pl = l;
    const Abonent *pr = r;
    return strcmp(pl->first_name, pr->first_name);
}

int phone_cmp(const void *l, const void *r)
{
    const Abonent *pl = l;
    const Abonent *pr = r;
    return strcmp(pl->phone, pr->phone);
}

int address_cmp(const void *l, const void *r)
{
    const Abonent *pl = l;
    const Abonent *pr = r;
    return strcmp(pl->address.street, pr->address.street);
}
//

void swap(void *l, void *r, size_t elem_size)
{
    char tmp[elem_size];
    memcpy(tmp, l, elem_size);
    memcpy(l, r, elem_size);
    memcpy(r, tmp, elem_size);
}

void mysort(Abonent *ptr, size_t cnt, size_t size, uni_cmp cmp)
{
    if (!ptr || !cnt)
        return;
    Abonent *pbeg = ptr;
    Abonent *pend = pbeg + (cnt - 1);
    size_t swapped = 1;

    while (swapped)
    {
        swapped = 0;
        for (Abonent *pcur = pbeg; pcur < pend; pcur++)
            if (cmp(pcur, pcur + 1) > 0)
            {
                swap(pcur, pcur + 1, size);
                swapped = 1;
            } 

        if (!swapped)
            break;

        swapped = 0;
        pend--;

        for (Abonent *pcur = pend; pcur > pbeg; pcur--)
        {
            if (cmp(pcur, pcur - 1) < 0)
            {
                swap(pcur - 1, pcur, size);
                swapped = 1;
            } 
        }  

        pbeg++;
    }
}

void mysort_keys(Abonent *ptr, size_t cnt, size_t size, uni_cmp cmp, void *keys)
{
    if (!ptr || !cnt)
        return;
    size_t *pbeg = keys;
    size_t *pend = pbeg + (cnt - 1);
    size_t swapped = 1;

    while (swapped)
    {
        swapped = 0;
        for (size_t *pcur = pbeg; pcur < pend; pcur++)
            if (cmp(&ptr[*pcur], &ptr[*(pcur + 1)]) > 0)
            {
                //printf("%zu -> %zu\n", *pcur, *(pcur + 1));
                swap(pcur, pcur + 1, size);
                swapped = 1;
            } 

        if (!swapped)
            break;

        swapped = 0;
        pend--;

        for (size_t *pcur = pend; pcur > pbeg; pcur--)
        {
            if (cmp(&ptr[*pcur], &ptr[*(pcur - 1)]) < 0)
            {
                //printf("%zu <- %zu\n", *pcur, *(pcur + 1));
                swap(pcur - 1, pcur, size);
                swapped = 1;
            } 
        }  

        pbeg++;
    }
}

// Функция для быстрой сортировки массива ключей
void qsort_keys(Abonent *abonents, size_t *keys, int left, int right, uni_cmp cmp)
{
    if (left < right)
    {
        int pivotIndex = left;
        int pivotNewIndex = left;

        for (int i = left + 1; i <= right; i++)
        {
            if (cmp(&abonents[keys[i]], &abonents[keys[pivotIndex]]) < 0)
            {
                pivotNewIndex++;
                // Меняем ключи
                size_t temp = keys[i];
                keys[i] = keys[pivotNewIndex];
                keys[pivotNewIndex] = temp;
            }
        }

        // Меняем ключи
        size_t temp = keys[left];
        keys[left] = keys[pivotNewIndex];
        keys[pivotNewIndex] = temp;

        // Рекурсивно сортируем левую и правую части
        qsort_keys(abonents, keys, left, pivotNewIndex - 1, cmp);
        qsort_keys(abonents, keys, pivotNewIndex + 1, right, cmp);
    }
}

int isWithinWeek(Abonent abonent)
{
    // Получаем текущую дату и время
    time_t now;
    struct tm *current_date;

    time(&now);
    current_date = gmtime(&now);

    // Создаем структуру для указанной даты
    struct tm target_date;
    target_date.tm_year = current_date->tm_year; // Текущий год
    target_date.tm_mon = abonent.status.personal.month - 1;    // Месяцы в библиотеке tm начинаются с 0
    target_date.tm_mday = abonent.status.personal.day;
    target_date.tm_hour = current_date->tm_hour;
    target_date.tm_min = current_date->tm_min;
    target_date.tm_sec = current_date->tm_sec;

    // Рассчитываем разницу в секундах между текущей датой и указанной датой
    time_t target_time = mktime(&target_date);
    // time_t current_time = mktime(current_date);
    time_t diff = target_time - now;

    // Разница в днях
    int days_diff = diff / (60 * 60 * 24);
    //printf("%d\n", days_diff);

    current_date->tm_min--;
    // Если разница в днях находится в диапазоне от -7 до 0,
    // то указанный день будет в течение недели от текущей даты
    return (days_diff < 7 && days_diff >= 0);
}
