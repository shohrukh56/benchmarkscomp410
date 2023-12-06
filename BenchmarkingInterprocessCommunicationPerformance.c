#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PARENT_SOCKET 0
#define CHILD_SOCKET 1
#define MESSAGE_SIZES {4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 524288}

void measure_latency(int fd[2], const char *message, size_t size) {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    write(fd[CHILD_SOCKET], message, size);
    read(fd[PARENT_SOCKET], NULL, 0);  // Wait for the acknowledgment
    clock_gettime(CLOCK_MONOTONIC, &end);

    double latency = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    latency /= 2;  // Divide by two for round-trip latency
    printf("Latency for %zu bytes: %.2f nanoseconds\n", size, latency);
}

void measure_throughput(int fd[2], const char *message, size_t size) {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    write(fd[CHILD_SOCKET], message, size);
    read(fd[PARENT_SOCKET], NULL, 0);  // Wait for the acknowledgment
    clock_gettime(CLOCK_MONOTONIC, &end);

    double duration = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
    double throughput = size / duration / 1024 / 1024;  // MB/s
    printf("Throughput for %zu bytes: %.2f MB/s\n", size, throughput);
}

int main() {
    int fd[2];
    pid_t pid;

    socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

    pid = fork();
    if (pid == 0) {
        // Child process
        close(fd[PARENT_SOCKET]);
        const char hello[] = "hello parent, I am child";
        write(fd[CHILD_SOCKET], hello, sizeof(hello));
    } else {
        // Parent process
        char buf[1024];
        close(fd[CHILD_SOCKET]);
        read(fd[PARENT_SOCKET], buf, sizeof(buf));
        printf("Parent received: '%s'\n", buf);

        // Measure latency and throughput for various message sizes
        size_t message_sizes[] = MESSAGE_SIZES;
        for (size_t i = 0; i < sizeof(message_sizes) / sizeof(message_sizes[0]); i++) {
            measure_latency(fd, "A", message_sizes[i]);
            measure_throughput(fd, "B", message_sizes[i]);
        }

        // Acknowledge completion to child
        write(fd[PARENT_SOCKET], NULL, 0);
    }

    return 0;
}
