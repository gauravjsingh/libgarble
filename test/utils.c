#include "utils.h"
#include <garble/block.h>

#include <ctype.h>
#include <stdio.h>
#include <time.h>

int
countToN(int *a, int n)
{
	for (int i = 0; i < n; i++)
		a[i] = i;
	return 0;
}

mytime_t
current_time(void)
{
    unsigned int hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long) lo) | (((unsigned long long) hi) << 32);
    /* struct timespec tp; */
    /* (void) clock_gettime(CLOCK_MONOTONIC, &tp); */
    /* return 1000000000 * tp.tv_sec + tp.tv_nsec; */
}

static int
compare(const void * a, const void * b)
{
	return (*(mytime_t *) a - *(mytime_t *) b);
}

mytime_t
median(mytime_t *values, int n)
{
	qsort(values, n, sizeof(mytime_t), compare);
    if (n == 0)
        return 0;
    else if (n == 1)
        return values[0];
    else if (n % 2 == 1)
		return values[(n + 1) / 2 - 1];
	else
		return (values[n / 2 - 1] + values[n / 2]) / 2;
}

double
doubleMean(double *values, int n)
{
	double total = 0;
	for (int i = 0; i < n; i++)
		total += values[i];
	return total / n;
}