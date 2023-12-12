#ifndef IO_H__
#define IO_H__

#include <stdio.h>
#include <errno.h>

#include "rc.h"
#include "macro.h"

void menu();

void clean_input_stream();

void input_interval(int *const num, const int left, const int right);

#endif
