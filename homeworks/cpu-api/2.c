#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    FILE *test = fopen("test.txt", "w+");
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        fprintf(test, "child\n");
    } else {
        wait(NULL);
        fprintf(test, "parent\n");
    }
    fclose(test);
    return 0;
}
