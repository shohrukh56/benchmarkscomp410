#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>

#define NUM_SAMPLES 1
#define GETPID_ITERATIONS 1 // Adjust as needed

void benchmark_system_call(void (*system_call)(), double *mean, double *stddev) {
    struct timeval start_time, end_time;
    double runtimes[NUM_SAMPLES];

    for (int i = 0; i < NUM_SAMPLES; ++i) {
        gettimeofday(&start_time, NULL);

        for (int j = 0; j < GETPID_ITERATIONS; ++j) {
            system_call();
        }

        gettimeofday(&end_time, NULL);

        double runtime = (end_time.tv_sec - start_time.tv_sec) +
                         (end_time.tv_usec - start_time.tv_usec) / 1e6;

        // Store the runtime for each sample (mean is calculated per iteration)
        runtimes[i] = runtime / GETPID_ITERATIONS;
    }

    // Calculate mean
    *mean = 0.0;
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        *mean += runtimes[i];
    }
    *mean /= NUM_SAMPLES;

    // Calculate standard deviation
    *stddev = 0.0;
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        *stddev += pow(runtimes[i] - *mean, 2);
    }
    *stddev = sqrt(*stddev / NUM_SAMPLES);
}

void getpid_call() {
    getpid();
}

void open_call() {
    int fd = open("benchmark_file.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void fork_call() {
    fork();
}

int main() {
    // Benchmark system calls
    double getpid_mean, getpid_stddev;
    benchmark_system_call(getpid_call, &getpid_mean, &getpid_stddev);

    double open_mean, open_stddev;
    benchmark_system_call(open_call, &open_mean, &open_stddev);

    double fork_mean, fork_stddev;
    benchmark_system_call(fork_call, &fork_mean, &fork_stddev);

    // Print the results
    printf("getpid() Mean Runtime: %f seconds, Standard Deviation: %f seconds\n", getpid_mean, getpid_stddev);
    printf("open() Mean Runtime: %f seconds, Standard Deviation: %f seconds\n", open_mean, open_stddev);
    printf("fork() Mean Runtime: %f seconds, Standard Deviation: %f seconds\n", fork_mean, fork_stddev);

    return 0;
}
