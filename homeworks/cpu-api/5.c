#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        int wc = wait(NULL);
        printf("child\n");
        printf("Return code from child wait(): %d\n", wc);
    } else {
        int wc = wait(NULL);
        printf("parent\n");
        printf("Return code from parent wait(): %d\n", wc);
    }
    return 0;
}