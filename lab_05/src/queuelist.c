#include <errno.h>
#include <stdio.h>
#include "rc.h"
#include "queuelist.h"

queuenode_t *create_queuenode(const task_t* task)
{
    queuenode_t *node = (queuenode_t *)malloc(sizeof(queuenode_t));
    if (!node)
    {
        return NULL;
    }
    node->task.num = task->num;
    node->task.time_out = task->time_out;
    node->next = NULL;
    node->value = 0;

    return node;
}

queuelist_t *create_queuelist(const unsigned capacity)
{
    queuelist_t *queue = (queuelist_t *)malloc(sizeof(queuelist_t));
    if (!queue)
    {
        return NULL;
    }
    queue->rear = NULL;
    queue->front = NULL;
    queue->size = 0;
    queue->capacity = capacity;

    return queue;
}

int is_emptylist(queuelist_t *const queue)
{
    return (queue->rear == NULL);
}

int is_fulllist(queuelist_t *const queue)
{
    return queue->size == queue->capacity;
}

void enqueuelist(queuelist_t *const queue, const task_t* task)
{
    if (is_fulllist(queue))
    {
        errno = EQUEUEOVERFLOW;
    }
    else
    {
        //printf("AHAH\n");
        queuenode_t *node = create_queuenode(task);
        if (node)
        {
            if (queue->rear == NULL)
            {
                queue->front = node;
                queue->rear = node;
                queue->size++;
            }
            else {

            queue->rear->next = node;
            queue->rear = node;
            queue->size++;
            }
        }
    }
}

task_t dequeuelist(queuelist_t *const queue, arr_t *const fmem)
{
    task_t task = {.num = 0, .time_out = 0};
    if (is_emptylist(queue))
    {
        errno = EQUEUEEMPTY;
        return task;
    }

    queuenode_t *node = queue->front;
    fmem->arr[fmem->ind++] = (size_t)node;
    task = node->task;
    queue->front = node->next;
    //printf("%p - %p - %d - %lf\n", (void *)node, (void *)node->next, node->task.num, node->task.time_out);
    // if (queue->front == queue->rear)
    // {
    //     queue->rear = NULL;
    //     queue->front = NULL;
    // }
    // else
    // {
    //     queue->front = queue->front->next;
    // }
    if (queue->front == NULL)
        queue->rear = NULL;
    if (node != NULL)
    {
        free(node);
        node = NULL;
    }

    queue->size--;
    //printf("%d - %lf\n", task.num, task.time_out);
    return task;
}

void freequeuelist(queuelist_t *queue, arr_t *const fmem)
{
    if (queue == NULL)
    {
        return;
    }

    while (!is_emptylist(queue))
    {
        dequeuelist(queue, fmem);
    }

    free(queue);
    queue->rear = NULL;
    queue->front = NULL;

    queue = NULL;
}

int check_rear(queuelist_t *queue, arr_t *fmem)
{
    size_t top = (size_t)queue->rear;
    int is_found = 0;

    for (int i = 0; i < fmem->ind; ++i)
    {
        if (top == fmem->arr[i])
        {
            is_found = 1;
            for (int j = i; j < fmem->ind - 1; ++j)
            {
                size_t temp = fmem->arr[j];
                fmem->arr[j] = fmem->arr[j + 1];
                fmem->arr[j + 1] = temp;
            }
        }
    }

    if (is_found)
    {
        fmem->ind--;
    }

    return is_found;
}
