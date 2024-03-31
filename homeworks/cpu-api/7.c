#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        close(STDOUT_FILENO);
        printf("child printf()\n");
    } else {
        wait(NULL);
        printf("parent printf()\n");
    }
    return 0;
}