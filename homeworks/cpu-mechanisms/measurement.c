#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 100000; ++i) {
        read(0, NULL, 0);
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    long long difference = (end.tv_sec - start.tv_sec) * 1000000LL + end.tv_usec - start.tv_usec;
    double average = (double)difference / 100000;
    printf("system call: %f ms\n", average);

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(1, &set);
    sched_setaffinity(0, sizeof(cpu_set_t), &set);
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    int child = fork();
    if (child == 0) {
        char buffer = '0';
        for (int i = 0; i < 100000; ++i) {
            read(fd1[0], &buffer, 1);
            write(fd2[1], &buffer, 1);
        }
    } else {
        gettimeofday(&start, NULL);
        char buffer = '0';
        for (int i = 0; i < 100000; ++i) {
            write(fd1[1], &buffer, 1);
            read(fd2[0], &buffer, 1);
        }
        gettimeofday(&end, NULL);
        difference = (end.tv_sec - start.tv_sec) * 1000000LL + end.tv_usec - start.tv_usec;
        average = (double)difference / 100000 / 2;
        printf("context switch: %f ms\n", average);
        wait(NULL);
    }
    return 0;
}
