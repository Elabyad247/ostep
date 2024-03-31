#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>

void handler() {
    printf("goodbye\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    int parent_pid = getpid();
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        printf("hello\n");
        kill(parent_pid, SIGCONT);
    } else {
        signal(SIGCONT, handler);
        pause();
    }
    return 0;
}
