// main.c
#include <stdio.h>

void runBenchmark(const char *executable, int iteration, double *mean, double *stddev);

int main() {
    for (int iteration = 1; iteration <= ITERATION_COUNTS; iteration++) {
        printf("Iteration %d:\n", iteration);

        double original_mean, original_stddev, modified_mean, modified_stddev;

        printf("Original Method:\n");
        runBenchmark("./original_benchmark", iteration, &original_mean, &original_stddev);

        printf("\nModified Method:\n");
        runBenchmark("./modified_benchmark", iteration, &modified_mean, &modified_stddev);
    }

    return 0;
}
