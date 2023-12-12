#include "rc.h"
#include "queuearr.h"

queuearr_t *create_queuearr(const unsigned capacity)
{
    queuearr_t *queue = (queuearr_t *)malloc(sizeof(queuearr_t));
    if (!queue)
    {
        return NULL;
    }
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity - 1;
    queue->arr = (task_t *)malloc(queue->capacity * sizeof(task_t));
    if (!queue->arr)
    {
        free(queue);
        queue = NULL;
        return NULL;
    }

    return queue;
}

int is_fullarr(queuearr_t *const queue)
{
    return queue->size == queue->capacity;
}

int is_emptyarr(queuearr_t *const queue)
{
    return queue->size == 0;
}

void enqueuearr(queuearr_t *const queue, const task_t task)
{
    if (is_fullarr(queue))
    {
        errno = EQUEUEOVERFLOW;
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = task;
    queue->size++;
}

task_t dequeuearr(queuearr_t *const queue)
{
    task_t task = {.time_out = 0, .num = 0};
    if (is_emptyarr(queue))
    {
        errno = EQUEUEEMPTY;
        return task;
    }
    task = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return task;
}

void freequeuearr(queuearr_t *queue)
{
    if (queue)
    {
        if (queue->arr)
        {
            free(queue->arr);
            queue->arr = NULL;
            free(queue);
            queue = NULL;
            errno = EOK;

            return;
        }

        free(queue);
        queue = NULL;
        errno = EOK;

        return;
    }
}
