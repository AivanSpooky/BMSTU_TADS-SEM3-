#include "stack_comparison.h"

extern double avg(double *nums, size_t cnt)
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

void runExperiment()
{
    printf("Замерный эксперимент сравнения stack_array и stack_list:\n");
    ArrayStack arrayStack;
    ListStack listStack;
    initializeArrayStack(&arrayStack);
    initializeListStack(&listStack);

    
    size_t tests = 100;
    double t1, t2;
    double t_1[tests];
    double t_2[tests];

    double pushes_1[tests];
    double pushes_2[tests];

    double pops_1[tests];
    double pops_2[tests];

    size_t sizes[5] = {10, 50, 100, 500, 1000};

    int value = 228;
    clock_t start, end;
    clock_t push_s, push_e;
    clock_t pop_s, pop_e;
    for (size_t i = 0; i < 5; i++)
    {
        size_t s1 = sizeof(int) + sizeof(int) * sizes[i];
        size_t s2 = (sizeof(ListNode) + sizeof(int)) * sizes[i];

        for (size_t test = 0; test < tests; test++)
        {
            start = clock();

            push_s = clock();
            for (size_t j = 0; j < sizes[i]; j++)
                pushArrayStack(&arrayStack, value);
            push_e = clock();
            t1 = ((double)(push_e - push_s));
            pushes_1[test] = t1;

            pop_s = clock();
            for (size_t j = 0; j < sizes[i]; j++)
                popArrayStack(&arrayStack);
            pop_e = clock();
            t1 = ((double)(pop_e - pop_s));
            pops_1[test] = t1;

            end = clock();

            t1 = ((double)(end - start));
            t_1[test] = t1;
        }

        for (size_t test = 0; test < tests; test++)
        {
            start = clock();

            push_s = clock();
            for (size_t j = 0; j < sizes[i]; j++)
                pushListStack(&listStack, value);
            push_e = clock();
            t2 = ((double)(push_e - push_s));
            pushes_2[test] = t2;

            pop_s = clock();
            for (size_t j = 0; j < sizes[i]; j++)
                popListStack(&listStack);
            pop_e = clock();
            t2 = ((double)(pop_e - pop_s));
            pops_2[test] = t2;

            end = clock();

            t2 = ((double)(end - start));
            t_2[test] = t2;
        }

        double t1_avg = avg(t_1, tests);
        double t2_avg = avg(t_2, tests);
        double push1_avg = avg(pushes_1, tests);
        double push2_avg = avg(pushes_2, tests);
        double pop1_avg = avg(pops_1, tests);
        double pop2_avg = avg(pops_2, tests);

        printf("РАЗМЕР СТЕКА: %zu\n", sizes[i]);
        printf("Статический массив:\n\tВремя (push X%zu): %.8lfмкс.\n\tВремя (pop X%zu): %.8lfмкс.\n\tВремя (push+pop X%zu): %.8lfмкс.\n\tЗанимаемая память: %zuБ\n", sizes[i], push1_avg, sizes[i], pop1_avg, sizes[i], t1_avg, s1);
        printf("Список:\n\tВремя (push X%zu): %.8lfмкс.\n\tВремя (pop X%zu): %.8lfмкс.\n\tВремя (push+pop X%zu): %.8lfмкс.\n\tЗанимаемая память: %zuБ\n", sizes[i], push2_avg, sizes[i], pop2_avg, sizes[i], t2_avg, s2);
        printf("Эффективность массива относительно списка:\n\tВремя (push X%zu): %.4lf\n\tВремя (pop X%zu): %.4lf\n\tВремя (push+pop X%zu): %.4lf\n\n", sizes[i], -eff(push1_avg, push2_avg), sizes[i], -eff(pop1_avg, pop2_avg), sizes[i], -eff(t1_avg, t2_avg));
    }
}
