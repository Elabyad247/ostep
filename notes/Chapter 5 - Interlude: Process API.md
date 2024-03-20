### Process API

In UNIX systems, process creation is done through a pair of [`fork()`](https://man7.org/linux/man-pages/man2/fork.2.html) + [`exec()`](https://man7.org/linux/man-pages/man3/exec.3.html) syscalls.

- Initialization of a process is done through `fork()` an existing process: creating an exact duplicate.
  
  - The original process is the **parent** process and the created duplicate becomes one of its **child** process; a process can have multiple children processes.
  - Returns twice, with value `0` in the child process and `PID` of the child in the calling parent.

- which one gets returned first is non-deterministic; the parent might run and terminate before the child, or vice-versa, so if you want the child done first, you call `wait()` in the parent branch, which gives the illusion of determinism.

- Executable loading is done through `exec()`; used to run a program that is different from the calling program. The call accepts as arguments the name of an executable and some arguments, and then *transforms* the currently running process into the one specified by the arguments. Thus, successful calls to `exec()` never return.

- Beyond the main three functions, Unix also provides interfaces for interacting
  with processes. For example, `kill()` is used to send *signals* to processes
  including `SIGINT` (interrupt) which generally terminates process and `SIGSTOP` which typically suspends them. Processes can also "catch" signals with `signal()`, allowing arbitrary code to be run in response to them.
