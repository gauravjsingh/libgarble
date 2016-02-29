#ifndef LIBGARBLE_TEST_UTILS_H
#define LIBGARBLE_TEST_UTILS_H

#include <stdint.h>

typedef unsigned long long mytime_t;
/* typedef uint64_t mytime_t; */

int
countToN(int *a, int N);

mytime_t
current_time(void);
mytime_t
median(mytime_t *values, int n);
double
doubleMean(double A[], int n);

#endif
