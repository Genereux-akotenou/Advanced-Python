#include "stdio.h"
#include "stdlib.h"
#include "time.h"

const int N = 1000;
double x[N][N];
double y[N][N];
double z[N][N];

int i, j, k;
double bandwidth, cpu_msec, start, end;

int block_sizes[] = {1, 2, 5, 8, 10, 20, 25, 40, 50, 100, 125, 200};
int block_sizes_length = 10;

int main()
{
    // We ensure that the sequence of random numbers generated will not be the same each time we run the program.
    srand(time(NULL));

    // Open file to save output data
    FILE *file_cpu = fopen("data/cputime.csv", "w");
    if (file_cpu == NULL) {
        perror("Error opening file");
        return 1;
    }
    FILE *file_band = fopen("data/bandwidth.csv", "w");
    if (file_band == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file_cpu, "%s, %s", "BLOCK_SIZE", "TIME");
    fprintf(file_cpu, "\n");
    fprintf(file_band, "%s, %s", "BLOCK_SIZE", "BANDWIDTH");
    fprintf(file_band, "\n");

    // Iterate over blocks
    for (int block_index = 0; block_index < block_sizes_length; block_index++) {
        int BLOCK_SIZE = block_sizes[block_index];

        // Initiallization sequence
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                x[i][j] = (double)rand() / RAND_MAX + 1.0;
                y[i][j] = (double)rand() / RAND_MAX + 1.0;
                z[i][j] = 0.0;
            }
        }

        // Start recording time
        start = (double)clock();

        // Matrix computing
        for (i = 0; i < N; i += BLOCK_SIZE) {
            for (j = 0; j < N; j += BLOCK_SIZE) {
                for (k = 0; k < N; k += BLOCK_SIZE) {
                    for (int ii = i; ii < i + BLOCK_SIZE; ii++) {
                        for (int jj = j; jj < j + BLOCK_SIZE; jj++) {
                            for (int kk = k; kk < k + BLOCK_SIZE; kk++) {
                                z[ii][jj] += x[ii][kk] * y[kk][jj];
                            }
                        }
                    }
                }
            }
        }
    
        // Take stop time
        end = (double)clock();
        cpu_msec = (end - start) / CLOCKS_PER_SEC;
        cpu_msec *= 1000.0;
        // bandwidth = sizeof(double) * N * cpu_msec / (1024 * 1024);
        // bandwidth = (2 * N * N * N * sizeof(double)) / (cpu_msec * 1024 * 1024);
        bandwidth = 2 * N * N * sizeof(double) * (1000.0 / cpu_msec) / (1024 * 1024);

        // Store
        fprintf(file_cpu, "%d, %f", BLOCK_SIZE, cpu_msec);
        fprintf(file_cpu, "\n");
        fprintf(file_band, "%d, %f", BLOCK_SIZE, bandwidth);
        fprintf(file_band, "\n");
    }
    return 0;
}
