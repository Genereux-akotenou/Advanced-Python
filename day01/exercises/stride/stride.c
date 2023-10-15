#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define MAX_STRIDE 20
#define SEED 86456

int main()
{
  int N = 1000000;
  double *a;

  a = malloc(N * MAX_STRIDE * sizeof(double));
  double mean, rate, msec, start, end;
  srand(time(NULL));

  for (int i = 0; i < N * MAX_STRIDE; i++)
    a[i] = rand() % 100 + 1.0;

  printf("stride , mean, time (msec), rate (MB/s)\n");

  for (int i_stride = 1; i_stride < MAX_STRIDE + 1; i_stride++)
  {
    mean = 0.0;
    start = (double)clock() / (double)CLOCKS_PER_SEC;

    for (int i = 0; i < N * i_stride; i += i_stride)
      mean = mean + a[i];

    end = (double)clock() / (double)CLOCKS_PER_SEC;
    mean = mean / N;

    msec = (end - start) * 1000.0; // time in milli-second;
    rate = sizeof(double) * N * (1000.0 / msec) / (1024 * 1024);

    printf("%d, %f, %f, %f,\n", i_stride, mean, msec, rate);
  }
}
