#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ITERATION_START 2
#define ITERATION_END 10
#define REPETITIONS 20

int main() {
    long long int iterations;
    double elapsed_time;

    // Loop over different iteration counts
    for (iterations = ITERATION_START; iterations <= ITERATION_END; iterations++) {
        elapsed_time = 0;

        // Repeat the measurement several times
        for (int repetition = 0; repetition < REPETITIONS; repetition++) {
            clock_t start_time = clock();

            // Your provided code
            for (long long int k = 0; k < pow(10, iterations); k++) {
                asm("nop"); // prevent compiler from optimizing loop
            }

            clock_t end_time = clock();
            double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            elapsed_time += time_taken;
        }

        // Calculate mean and standard deviation
        double mean_time = elapsed_time / REPETITIONS;
        double variance = 0;

        for (int repetition = 0; repetition < REPETITIONS; repetition++) {
            clock_t start_time = clock();

            for (long long int k = 0; k < pow(10, iterations); k++) {
                asm("nop");
            }

            clock_t end_time = clock();
            double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            variance += (time_taken - mean_time) * (time_taken - mean_time);
        }

        double std_deviation = sqrt(variance / REPETITIONS);

        // Print results
        printf("Iterations: %lld\t Mean Time: %f\t Standard Deviation: %f\n", iterations, mean_time, std_deviation);
    }

    return 0;
}
