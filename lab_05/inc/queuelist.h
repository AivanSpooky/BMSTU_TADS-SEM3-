#ifndef QUEUELIST_H__
#define QUEUELIST_H__

#include <stdlib.h>

#include "array.h"
#include "task.h"

typedef struct queuenode
{
    int value;
    task_t task;
    struct queuenode *next;
} queuenode_t;

typedef struct
{
    unsigned capacity, size;
    queuenode_t *front, *rear;
} queuelist_t;

queuenode_t *create_queuenode(const task_t* task);

queuelist_t *create_queuelist();

int is_emptylist(queuelist_t *const queue);

int is_fulllist(queuelist_t *const queue);

void enqueuelist(queuelist_t *const queue, const task_t* task);

task_t dequeuelist(queuelist_t *const queue, arr_t *const fmem);

void freequeuelist(queuelist_t *queue, arr_t *const fmem);

int check_rear(queuelist_t *queue, arr_t *fmem);

#endif
