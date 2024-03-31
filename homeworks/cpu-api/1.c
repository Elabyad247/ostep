#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;
    printf("parent x before fork(): %d\n", x);
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        x = 200;
        printf("child x after fork(): %d\n", x);
    } else {
        wait(NULL);
        printf("parent x after fork(): %d\n", x);
    }
    return 0;
}
