#include "utils.h"

// Функция создает случайное время в диапазоне (llim; rlim)
double get_time(const int llim, const int rlim)
{
    double rnd = (double)rand() / (double)RAND_MAX;

    return (rlim - llim) * rnd + llim;
}

// Функция считает количество тиков проццессора (на момент вызова функции)
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}
