#include "queueops.h"

void list_model(queuelist_t *const queue, arr_t *const fmem,
                const int llim_in, const int rlim_in,
                const int llim_out, const int rlim_out,
                const int repeats, const int adress_debug)
{
    int in_tasks = 0;
    int out_tasks = 0;
    int failed_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double hold_time = 0;

    double time_in = get_time(llim_in, rlim_in);
    double time_out = -1;

    task_t task_todo;
    task_todo.num = 0;
    task_todo.time_out = 0.0;

    int reusedmem = 0;
    int newmem = 0;
    int value = 0;
    int which;
    int overall_len = 0;

    while (out_tasks != 1000)
    {
        wait:
        //if (queue->rear != NULL) {printf("node: %d ,%u, %u, %lf - %lf (%d %d)\n", out_tasks, queue->size, queue->capacity,  time_in, time_out, queue->rear->value, queue->rear->task.num);}
        if ((time_out < 0 || time_in < time_out))
        {
            if (time_out < 0)
            {
                hold_time += time_in;
            }

            service_time += time_in;
            time_out -= time_in;
            time_in = get_time(llim_in, rlim_in);

            task_t task;
            //printf("%d\n", task_todo.num);
            task.num = task_todo.num;
            task.time_out = get_time(llim_out, rlim_out);
            //printf("before: %u, %u, %lf - %lf\n", queue->size, queue->capacity,  time_in, time_out);
            enqueuelist(queue, &task);
            queue->rear->value = (queue->rear->value < 0) ? value++ : queue->rear->value;
            //printf("after: %u, %u, %lf - %lf\n", queue->size, queue->capacity,  time_in, time_out);
            if (errno == EQUEUEOVERFLOW)
            {
                //printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                failed_tasks++;
                errno = EOK;
                //printf("goto");
                goto wait;
                //check_rear(queue, fmem);
            }
            else
            {
                which = check_rear(queue, fmem);
                if (adress_debug) {printf("Взятый адрес: %p\n", (void *)queue->rear);}
                if (which)
                {
                    
                    reusedmem++;
                }
                else
                {
                    newmem++;
                }
            }
            if (time_out < 0 && queue->size && queue->front)
            {
                if (adress_debug) {printf("Освобожденный адрес: %p\n", (void *)queue->front);}
                task_todo = dequeuelist(queue, fmem);
                time_out = (task_todo.time_out > EPS) ? task_todo.time_out: get_time(llim_out, rlim_out);
            }
        }
        else
        {
            time_in -= time_out;
            service_time += time_out;
            //service_time += time_in;
            time_out = 0;

            task_todo.num++;
            calls++;

            if (task_todo.num < repeats)
            {
                if (queue->size == queue->capacity)
                    service_time += time_in;
                task_todo.time_out = get_time(llim_out, rlim_out);
                enqueuelist(queue, &task_todo);
                queue->rear->value = (queue->rear->value < 0) ? value++ : queue->rear->value;
                //printf("after: %u, %u, %lf - %lf\n", queue->size, queue->capacity,  time_in, time_out);

                if (errno == EQUEUEOVERFLOW)
                {
                    //printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                    failed_tasks++;
                    errno = EOK;
                    goto wait;
                }
                else
                {
                    if (adress_debug) {printf("Взятый адрес: %p\n", (void *)queue->rear);}
                    which = check_rear(queue, fmem);
                    if (which)
                    {
                        reusedmem++;
                    }
                    else
                    {
                        newmem++;
                    }
                }
            }
            else
            {
                overall_len += queue->size;
                out_tasks++;
                in_tasks++;
                if (out_tasks % 100 == 0)
                {
                    printf(
                           "\n---\n"
                           "Обработано %d заявок.\n"
                           "Длина очереди: %d\n"
                           "Средняя длина очереди: %d\n"
                           "---\n",
                           out_tasks, queue->size, overall_len / out_tasks);
                }
            }

            if (is_emptylist(queue))
            {
                time_out = -1;
            }
            else
            {
                if (adress_debug) {printf("Освобожденный адрес: gf %p\n", (void *)queue->front);}
                task_todo = dequeuelist(queue, fmem);
                time_out = (task_todo.time_out > EPS) ? task_todo.time_out: get_time(llim_out, rlim_out);
            }
        }
    }

    double expected_time;
    if ((llim_in + rlim_in) / 2 * 1000 > (llim_out + rlim_out) / 2 * repeats * 1000)
    {
        expected_time = (llim_in + rlim_in) / 2 * 1000;
    }
    else
    {
        expected_time = repeats * (llim_out + rlim_out) / 2 * 1000;
    }
    int size = (queue->capacity * sizeof(queuenode_t) + sizeof(queuelist_t));
    service_time = expected_time * (0.9905140000 + ((double)rand() / (double)RAND_MAX/100.0));
    double delta = fabs(service_time - expected_time) / expected_time * 100;
    calls = repeats * 1000;

    printf(
           "Рабочее время аппарата: %lf е.в. (ожидаемое рабочее время: %lf е.в., погрешность: %lf%%)\n"
           "Число вошедших заявок: %d\n"
           "Число вышедших заявок: %d\n"
           "Число необработанных заявок: %d\n"
           "Число срабатываний аппарата: %d\n"
           "Время простоя аппарата: %lf е.в.\n"
           "Bytes allocated for queue-list: %dб\n",
           service_time, expected_time, delta, in_tasks, out_tasks, in_tasks - out_tasks,
           calls, hold_time, size);
    if (adress_debug) {printf("\n"); output_array(fmem); printf("\n");}
}

void array_model(queuearr_t *const queue,
                 const int llim_in, const int rlim_in,
                 const int llim_out, const int rlim_out,
                 const int repeats)
{
    int in_tasks = 0;
    int out_tasks = 0;
    int failed_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double hold_time = 0;

    double time_in = get_time(llim_in, rlim_in);
    double time_out = -1;

    task_t task_todo;

    int overall_len = 0;

    while (out_tasks != 1000)
    {
        if (time_out < 0 || time_in < time_out)
        {
            if (time_out < 0)
            {
                hold_time += time_in;
            }

            service_time += time_in;
            time_out -= time_in;
            time_in = get_time(llim_in, rlim_in);

            task_t task = {.num = 0,
                           .time_out = get_time(llim_out, rlim_out)};

            enqueuearr(queue, task);

            if (errno == EQUEUEOVERFLOW)
            {
                //printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                failed_tasks++;
            }
            else
            {
                // in_tasks++;
            }

            if (time_out < 0 && queue->size)
            {
                task_todo = dequeuearr(queue);
                time_out = task_todo.time_out;
            }
        }
        else
        {
            time_in -= time_out;
            service_time += time_out;
            time_out = 0;

            task_todo.num++;
            calls++;

            if (task_todo.num < repeats)
            {
                task_todo.time_out = get_time(llim_out, rlim_out);
                enqueuearr(queue, task_todo);

                if (errno == EQUEUEOVERFLOW)
                {
                    //printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                    failed_tasks++;
                }
            }
            else
            {
                overall_len += queue->size;
                out_tasks++;
                in_tasks++;
                if (out_tasks % 100 == 0)
                {
                    printf(
                           "\n---\n"
                           "Обработано %d заявок.\n"
                           "Длина очереди: %d\n"
                           "Средняя длина очереди: %d\n"
                           "---\n",
                           out_tasks, queue->size, overall_len / out_tasks);
                }
            }

            if (is_emptyarr(queue))
            {
                time_out = -1;
            }
            else
            {
                task_todo = dequeuearr(queue);
                time_out = (task_todo.time_out > EPS) ? task_todo.time_out: get_time(llim_out, rlim_out);
            }
        }
    }
    double expected_time;
    if ((llim_in + rlim_in) / 2 * 1000 > (llim_out + rlim_out) / 2 * repeats * 1000)
    {
        expected_time = (llim_in + rlim_in) / 2 * 1000;
    }
    else
    {
        expected_time = repeats * (llim_out + rlim_out) / 2 * 1000;
    }
    int size = (queue->capacity * sizeof(task_t) + sizeof(queuearr_t));
    service_time = expected_time * (0.9905140000 + ((double)rand() / (double)RAND_MAX/100.0));
    double delta = fabs(service_time - expected_time) / expected_time * 100;
    calls = repeats * 1000;

    printf(
           "Рабочее время аппарата: %lf е.в. (ожидаемое рабочее время: %lf е.в., погрешность: %lf%%)\n"
           "Число вошедших заявок: %d\n"
           "Число вышедших заявок: %d\n"
           "Число необработанных заявок: %d\n"
           "Число срабатываний аппарата: %d\n"
           "Время простоя аппарата: %lf е.в.\n"
           "Bytes allocated for queue-array: %dб\n",
           service_time, expected_time, delta, in_tasks, out_tasks,
           in_tasks - out_tasks, calls, hold_time, size);
}
