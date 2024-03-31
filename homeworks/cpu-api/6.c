#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        printf("child pid: %d\n", getpid());
    } else {
        int wc = waitpid(rc, NULL, 0);
        printf("Return code from parent wait(): %d\n", wc);
    }
    return 0;
}