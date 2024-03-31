1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?
   
   ```c
   #include <stdio.h>
   #include <unistd.h>
   #include <assert.h>
   #include <sys/wait.h>
   
   int main(int argc, char *argv[]) {
       int x = 100;
       printf("parent x before fork(): %d\n", x); // 100
       int rc = fork();
       assert(rc >= 0);
       if (rc == 0) {
           x = 200;
           printf("child x after fork(): %d\n", x); // 200
       } else {
           wait(NULL);
           printf("parent x after fork(): %d\n", x); // 100
       }
       return 0;
   }
   ```

2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?
   
   ```c
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
   ```

3. Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?
   
   ```c
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
   ```

4. Write a program that calls fork() and then calls some form of exec() to run the program `/bin/ls`. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?
   
   ```c
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
   ```

5. Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?
   
   On success returns the process ID of the terminated child; on error returns -1
   If we use **wait()** in child process then **wait()** returns -1. Because, there is no child of child. So, there is no wait for any process (child process) to exit.
   
   ```c
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
   ```

6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?
   
   **waitpid()** is used when we want to wait or a specific child process
   
   ```c
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
   ```

7. Write a program that creates a child process, and then in the child closes standard output (STDOUT_FILENO). What happens if the child calls printf() to print some output after closing the descriptor?
   
   the output won't show in the terminal.
   
   ```c
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
   ```

8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
   
   ```c
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
   ```
