// modified_benchmark.c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define INNER_ITERATIONS 20
#define ITERATION_COUNTS 10  // Added definition

void runBenchmark(int iteration, double *mean, double *stddev) {
    double runtimes[INNER_ITERATIONS];

    for (int i = 0; i < INNER_ITERATIONS; i++) {
        struct timespec tstart = {0, 0}, tend = {0, 0};

        clock_gettime(CLOCK_MONOTONIC, &tstart);

        // Modified computation
        for (int k = 0; k < 1000000000; k++) {
            asm("nop");
        }

        clock_gettime(CLOCK_MONOTONIC, &tend);

        double runtime = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);

        runtimes[i] = runtime;
    }

    // Calculate mean and standard deviation
    double sum = 0.0;
    for (int i = 0; i < INNER_ITERATIONS; i++) {
        sum += runtimes[i];
    }
    *mean = sum / INNER_ITERATIONS;

    double stddev_sum = 0.0;
    for (int i = 0; i < INNER_ITERATIONS; i++) {
        stddev_sum += (runtimes[i] - *mean) * (runtimes[i] - *mean);
    }
    *stddev = sqrt(stddev_sum / INNER_ITERATIONS);

    // Print mean and standard deviation
    printf("Modified Method - Iteration %d: Mean Runtime: %.5f seconds, Standard Deviation: %.5f seconds\n", iteration, *mean, *stddev);
}

int main() {
    for (int iteration = 1; iteration <= ITERATION_COUNTS; iteration++) {
        double modified_mean, modified_stddev;

        runBenchmark(iteration, &modified_mean, &modified_stddev);
    }

    return 0;
}
