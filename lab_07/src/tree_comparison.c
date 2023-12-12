#include "tree_comparison.h"

double avg(double *nums, size_t cnt)
{
    double sum = 0;
    for (size_t i = 0; i < cnt; i++)
    {
        sum += nums[i];
    }
    return sum / cnt;
}

double eff(double t1, double t2)
{
    return ((t1 - t2) / t1 * 100);
}