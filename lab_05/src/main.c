#include "io.h"
#include "queueops.h"

#define errcheck(err, len, queuearr, queuelist, fmem, msg) \
    for (int i = 0; i < len; ++i)                          \
    {                                                      \
        if (errno == err[i])                               \
        {                                                  \
            printf("%s\n", msg);                             \
            /*freequeuearr(queuearr);                        \
            freequeuelist(queuelist, fmem);                \
            free_array(fmem); */                             \
            return EOK;                                    \
        }                                                  \
    }

int main()
{
    int capacity;
    int ltime_in, rtime_in;
    int ltime_out, rtime_out;
    int repeats;
    int adress_debug;
    arr_t *fmem = NULL;
    queuelist_t *queuelist = NULL;
    queuearr_t *queuearr = NULL;

    int inputerr[] = {EINVALIDINTINPUT, EINVALIDINTER};

    int cmd = -1;
    printf("%s",
        "Данная программа позволяет сравнить время, затраченное на обработку \n"
        "очереди, реализованной на основе массива и односвязного линейного списка. \n"
        "Под обработкой подразумевается обработка деятельности обслуживающего аппарата. \n\n");
    menu();

    while (cmd)
    {
        input_interval(&cmd, 0, 4);
        errcheck(inputerr, 2,
                 queuearr, queuelist, fmem,
                "Введено недопустимое значение! Повторите попытку.");

        if (cmd == 1)
        {
            if (queuearr)
            {
                printf("%s\n",
                       "Очередь уже существует! Выход из программы..");

                freequeuearr(queuearr);
                freequeuelist(queuelist, fmem);
                free_array(fmem);

                return EOK;
            }
            else
            {
                printf("%s\n", "Введите максимальное число элементов в очереди:");
                input_interval(&capacity, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку." );

                printf("%s\n", "Введите интервал прибытия заявки в очередь (2 целых числа через пробел):");
                input_interval(&ltime_in, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");
                input_interval(&rtime_in, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                if (rtime_in < ltime_in)
                {
                    printf("%s\n",
                           "Правая граница должна быть больше левой! Повторите попытку.");

                    return EOK;
                }

                printf("%s\n", "Введите интервал обработки заявки в очереди (2 целых числа через пробел):");
                input_interval(&ltime_out, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");
                input_interval(&rtime_out, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                if (rtime_out < ltime_out)
                {
                    printf("%s\n",
                           "Правая граница должна быть больше левой! Повторите попытку.");

                    return EOK;
                }

                printf("%s\n", "Введите количество обслуживаний одной заявки:");
                input_interval(&repeats, 1, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                queuearr = create_queuearr(capacity);
                uint64_t start, end;
                start = tick();
                array_model(queuearr, ltime_in, rtime_in, ltime_out, rtime_out, repeats);
                end = tick();
                printf("%s %ju\n",
                       "Время выполнения моделирования на основе массива:", end - start);
            }

            menu();
        }
        if (cmd == 2)
        {
            queuearr_t *test = create_queuearr(1000);
            uint64_t start, end;

            start = tick();
            for (int i = 0; i < 1000; ++i)
            {
                task_t task = {.num = i, .time_out = (double)i};
                enqueuearr(test, task);
            }
            end = tick();

            printf("%s %ju\n",
                   "Добавление элементов в очередь на основе массива:",
                   (end - start) / 1000);

            start = tick();
            for (int i = 0; i < 1000; ++i)
            {
                dequeuearr(test);
            }
            end = tick();

            printf("%s %ju\n",
                   "Удаление элементов из очереди на основе массива:",
                   (end - start) / 1000);

            menu();
        }

        if (cmd == 3)
        {
            if (queuelist)
            {
                printf("%s\n",
                       "Очередь уже существует! Выход из программы..");

                freequeuearr(queuearr);
                freequeuelist(queuelist, fmem);
                free_array(fmem);

                return EOK;
            }
            else
            {
                printf("%s\n", "Введите максимальное число элементов в очереди:");
                input_interval(&capacity, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                printf("%s\n", "Введите интервал прибытия заявки в очередь (2 целых числа через пробел):");
                input_interval(&ltime_in, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");
                input_interval(&rtime_in, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                if (rtime_in < ltime_in)
                {
                    printf("%s\n",
                           "Правая граница должна быть больше левой! Повторите попытку.");

                    return EOK;
                }

                printf("%s\n", "Введите интервал обработки заявки в очереди (2 целых числа через пробел):");
                input_interval(&ltime_out, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");
                input_interval(&rtime_out, 0, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                if (rtime_out < ltime_out)
                {
                    printf("%s\n",
                           "Правая граница должна быть больше левой! Повторите попытку.");

                    return EOK;
                }

                printf("%s\n", "Введите количество обслуживаний одной заявки:");
                input_interval(&repeats, 1, 99999);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                printf("%s\n", "Вывести дополнительно информацию об адресах элементов при удалении/добавлении? (0 - нет; 1 - да):");
                input_interval(&adress_debug, 0, 1);
                errcheck(inputerr, 2,
                         queuearr, queuelist, fmem,
                        "Введено недопустимое значение! Повторите попытку.");

                queuelist = create_queuelist(capacity);
                fmem = create_array(capacity);
                uint64_t start, end;
                start = tick();
                list_model(queuelist, fmem, ltime_in, rtime_in, ltime_out, rtime_out, repeats, adress_debug);
                end = tick();
                printf("%s %ju\n",
                       "Время выполнения моделирования на основе списка:", end - start);
            }

            menu();
        }
        if (cmd == 4)
        {
            queuelist_t *test = create_queuelist(1000);
            arr_t *fmem_test = create_array(1000);
            uint64_t start, end;

            start = tick();
            for (int i = 0; i < 1000; ++i)
            {
                task_t task = {.num = i, .time_out = (double)i};
                enqueuelist(test, &task);
            }
            end = tick();

            printf("%s %ju\n",
                   "Добавление элементов в очередь на основе списка:",
                   (end - start) / 1000);

            start = tick();
            for (int i = 0; i < 1000; ++i)
            {
                dequeuelist(test, fmem_test);
            }
            end = tick();

            printf("%s %ju\n",
                   "Удаление элементов из очереди на основе списка:",
                   (end - start) / 1000);

            menu();
        }
    }

    // freequeuearr(queuearr);
    // freequeuelist(queuelist, fmem);
    // free_array(fmem);

    return EOK;
}
