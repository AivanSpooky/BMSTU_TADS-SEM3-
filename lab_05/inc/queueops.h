#ifndef QUEUEOPS_H__
#define QUEUEOPS_H__

#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "rc.h"
#include "macro.h"

#include "array.h"
#include "queuearr.h"
#include "queuelist.h"
#include "utils.h"

void list_model(queuelist_t *const queue, arr_t *const fmem,
                const int llim_in, const int rlim_in,
                const int llim_out, const int rlim_out,
                const int repeats, const int adress_debug);

void array_model(queuearr_t *const queue,
                 const int llim_in, const int rlim_in,
                 const int llim_out, const int rlim_out,
                 const int repeats);

#endif
