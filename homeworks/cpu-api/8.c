#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);
    int a = fork();
    assert(a >= 0);
    if (a == 0) {
        printf("child a\n");
        dup2(fd[1], 1); // redirect stdout to the write end of the pipe
        printf("in the ma9ora\n");
    } else {
        int b = fork();
        assert(b >= 0);
        if (b == 0) {
            printf("child b\n");
            dup2(fd[0], 0); // redirect stdin to the read end of the pipe
            char buffer[512];
            read(0, buffer, 512);
            printf("%s", buffer);
        } else {
            waitpid(b, NULL, 0);
            printf("Big baba\n");
        }
    }
    return 0;
}