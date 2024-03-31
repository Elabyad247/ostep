#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    assert(rc >= 0);
    if (rc == 0) {
        char* const argv[] = {"ls", NULL};
        // char* const envp[] = {NULL};

        execv("/bin/ls", argv);
        //execl("/bin/ls", "ls", NULL);
        //execle("/bin/ls", "ls", NULL, envp);
        //execlp("ls", "ls", NULL);
        //execvp("ls", argv);
        //execve("/bin/ls", argv, envp);
    } else {
        wait(NULL);
    }
    return 0;
}