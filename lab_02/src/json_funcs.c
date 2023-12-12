#include "json_funcs.h"


int createJSON(Abonent *abonents)
{
    strcpy(abonents[0].last_name, "Иванов");
    strcpy(abonents[0].first_name, "Петр");
    strcpy(abonents[0].phone, "+71234567890");
    strcpy(abonents[0].address.street, "Улица 1");
    abonents[0].address.house_number = 1;
    abonents[0].status_type = PERSONAL;
    abonents[0].status.personal.day = 10;
    abonents[0].status.personal.month = 5;
    abonents[0].status.personal.year = 1990;

    strcpy(abonents[1].last_name, "Петров");
    strcpy(abonents[1].first_name, "Иван");
    strcpy(abonents[1].phone, "+79876543210");
    strcpy(abonents[1].address.street, "Улица 2");
    abonents[1].address.house_number = 2;
    abonents[1].status_type = PROFFESSIONAL;
    strcpy(abonents[1].status.professional.position, "Инженер");
    strcpy(abonents[1].status.professional.organization, "Компания ABC");

    // Создаем JSON объекты и добавляем абонентов в массив
    struct json_object *abonent_array = json_object_new_array();
    
    for (int i = 0; i < 2; i++)
    {
        struct json_object *abonent_object = json_object_new_object();
        json_object_object_add(abonent_object, "last_name", json_object_new_string(abonents[i].last_name));
        json_object_object_add(abonent_object, "first_name", json_object_new_string(abonents[i].first_name));
        json_object_object_add(abonent_object, "phone", json_object_new_string(abonents[i].phone));
        
        struct json_object *address_object = json_object_new_object();
        json_object_object_add(address_object, "street", json_object_new_string(abonents[i].address.street));
        json_object_object_add(address_object, "house_number", json_object_new_int(abonents[i].address.house_number));
        json_object_object_add(abonent_object, "address", address_object);
        
        struct json_object *status_object = json_object_new_object();
        if (abonents[i].status_type == PERSONAL)
        {
            json_object_object_add(status_object, "type", json_object_new_string("personal"));
            json_object_object_add(status_object, "day", json_object_new_int(abonents[i].status.personal.day));
            json_object_object_add(status_object, "month", json_object_new_int(abonents[i].status.personal.month));
            json_object_object_add(status_object, "year", json_object_new_int(abonents[i].status.personal.year));
        }
        else if (abonents[i].status_type == PROFFESSIONAL)
        {
            json_object_object_add(status_object, "type", json_object_new_string("professional"));
            json_object_object_add(status_object, "position", json_object_new_string(abonents[i].status.professional.position));
            json_object_object_add(status_object, "organization", json_object_new_string(abonents[i].status.professional.organization));
        }
        json_object_object_add(abonent_object, "status", status_object);
        
        json_object_array_add(abonent_array, abonent_object);
    }

    // Создаем и записываем JSON файл
    struct json_object *root_object = json_object_new_object();
    json_object_object_add(root_object, "abonents", abonent_array);

    const char *json_string = json_object_to_json_string_ext(root_object, JSON_C_TO_STRING_PRETTY);
    
    FILE *file = fopen("file.json", "w");
    if (file)
    {
        fprintf(file, "%s\n", json_string);
        fclose(file);
        printf("JSON файл успешно создан.\n");
    }
    else
    {
        printf("Ошибка при создании JSON файла.\n");
        return ERR_IO;
    }

    return OK;
}

// Функция для чтения данных из JSON файла и записи их в массив абонентов
int readAbonentsFromJSON(const char *filename, Abonent *abonents, int max_abonents, size_t *cnt)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Ошибка при открытии файла.\n");
        return ERR_IO;
    }

    char buffer[100000];  // Буфер для чтения данных из файла
    struct json_object *root_object = NULL;
    size_t file_size;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size >= sizeof(buffer))
    {
        fclose(file);
        printf("Файл слишком большой для буфера.\n");
        return ERR_DATA;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    root_object = json_tokener_parse(buffer);

    // Проверяем, является ли объект "abonents" массивом
    struct json_object *abonents_array = NULL;
    if (json_object_object_get_ex(root_object, "abonents", &abonents_array) && json_object_is_type(abonents_array, json_type_array))
    {
        int num_abonents = json_object_array_length(abonents_array);
        *cnt = (size_t) num_abonents; 
        if (num_abonents > max_abonents)
        {
            printf("Слишком много абонентов для данного массива.\n");
            json_object_put(root_object);
            return ERR_RANGE;
        }
        for (int i = 0; i < num_abonents; i++)
        {
            struct json_object *abonent_object = json_object_array_get_idx(abonents_array, i);
            
            Abonent *abonent = &abonents[i];

            struct json_object *last_name_obj, *first_name_obj, *phone_obj, *address_obj, *status_obj;

            json_object_object_get_ex(abonent_object, "last_name", &last_name_obj);
            //
            // char b[MAX_NAME_LEN + 2];
            // strcpy(b, json_object_get_string(last_name_obj));
            // size_t len = strlen(b);
            //printf("%s - %zu\n", last_name, len);
            // if (b[len - 1] == '\n')
            //     b[--len] = '\0';
            // if (!len)
            // {
            //     printf("Ошибка при вводе (ничего не введено).\n");
            //     return ERR_IO;
            // }
            // if (len > MAX_NAME_LEN)
            // {
            //     printf("Ошибка при вводе (введено слишком много символов).\n");
            //     return ERR_RANGE;
            // }
            //
            strcpy(abonent->last_name, json_object_get_string(last_name_obj));

            json_object_object_get_ex(abonent_object, "first_name", &first_name_obj);
            strcpy(abonent->first_name, json_object_get_string(first_name_obj));

            json_object_object_get_ex(abonent_object, "phone", &phone_obj);
            strcpy(abonent->phone, json_object_get_string(phone_obj));

            json_object_object_get_ex(abonent_object, "address", &address_obj);
            struct json_object *street_obj, *house_number_obj;
            json_object_object_get_ex(address_obj, "street", &street_obj);
            strcpy(abonent->address.street, json_object_get_string(street_obj));
            json_object_object_get_ex(address_obj, "house_number", &house_number_obj);
            abonent->address.house_number = json_object_get_int(house_number_obj);

            json_object_object_get_ex(abonent_object, "status", &status_obj);
            struct json_object *type_obj;
            json_object_object_get_ex(status_obj, "type", &type_obj);
            const char *type = json_object_get_string(type_obj);

            if (strcmp(type, "personal") == 0)
            {
                abonent->status_type = PERSONAL;
                struct json_object *day_obj, *month_obj, *year_obj;
                json_object_object_get_ex(status_obj, "day", &day_obj);
                abonent->status.personal.day = json_object_get_int(day_obj);
                json_object_object_get_ex(status_obj, "month", &month_obj);
                abonent->status.personal.month = json_object_get_int(month_obj);
                json_object_object_get_ex(status_obj, "year", &year_obj);
                abonent->status.personal.year = json_object_get_int(year_obj);
            }
            else if (strcmp(type, "professional") == 0)
            {
                abonent->status_type = PROFFESSIONAL;
                struct json_object *position_obj, *organization_obj;
                json_object_object_get_ex(status_obj, "position", &position_obj);
                strcpy(abonent->status.professional.position, json_object_get_string(position_obj));
                json_object_object_get_ex(status_obj, "organization", &organization_obj);
                strcpy(abonent->status.professional.organization, json_object_get_string(organization_obj));
            }
        }

        printf("Данные успешно считаны из JSON файла.\n");
        json_object_put(root_object);
    }
    else
    {
        printf("Неверный формат JSON файла (ожидался массив).\n");
        json_object_put(root_object);
        return ERR_DATA;
    }
    return OK;
}
