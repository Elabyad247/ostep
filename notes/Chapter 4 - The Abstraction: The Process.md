> Each peach-eater can eat their own *virtual* peach, even though there's only
> one *physical* peach.

One of the most important abstractions an OS provides is the **process**: a running instance of a program. We typically want to run many processes at the same time, more than the number of available CPU cores. The OS must be able to *virtualize* a physical resource and let multiple processes share the limited resource.

To implement virtualization of the CPU, the OS will need some *low-level machinery* and some *high-level intelligence*. We call the low-level machinery mechanisms; **mechanisms** are low-level methods or protocols that implement a needed piece of functionality. On top of these mechanisms resides some of the intelligence in the OS, in the form of policies. **Policies** are algorithms for making some kind of decision within the OS.

### Abstraction of Process

A process is simply an *instance* of a piece of *program* running in the system. There can be multiple processes executing the same piece of program code. Each process represents a somewhat isolated entity.

##### Machine State

Running a process instance of a program requires the OS to remember the *machine state* of the process, which typically consists of the following information:

- **Address space**: memory space that a process can address, typically also virtualized, which contains at least:
  
  - *Code*: compiled machine code of the program
  - *Data*: any initial static data/space the program needs
  - *Stack*: space reserved for the run-time function *stack* of the process
  - *Heap*: space reserved for any new run-time data

- **Registers context**: CPU registers' values; particularly special ones include:
  
  - *Program counter* (PC, or *instruction pointer*): which instruction of the program to execute next
  - *Stack pointer* (SP) & *Frame pointer* (FP): for managing the function stack

- **I/O information**: states related to storage or network, for example:
  
  - List of currently open files

### Process API

*Application programming interface* (API) means the set of interfaces a lower-layer system/library provides to upper-layer programs. The APIs that an OS provides to user programs are called **system calls** (*syscalls*). Everything a user program wants to do that might require system-level privileges, such as creating processes, accessing shared resources, and communicating with other processes, are typically done through invoking system calls.

- *Create*: An operating system must include some method to create new processes; *initialize* the states, *load* the program from persistent storage in some *executable format*, and get the process running at the entry point of its code; the process then runs. 

- *Destroy*: As there is an interface for process creation, systems also provide an interface to destroy processes forcefully.

- *Wait*: let a process wait for the termination of another process.

- *Miscellaneous Control*: provide some kind of method to suspend a process and then resume it.

- *Status*: get some status information about a process, such as how long it has run for, or what state it is in.

### Process Creation

The first thing that the OS must do to run a program is to load its code and any static data into the address space of the process. programs initially reside on disk in some kind of executable format; thus, the process of loading a program and static data into memory requires the OS to read those bytes from disk and place them in memory somewhere

Once the code and static data are loaded into memory, some memory must be allocated for the program’s run-time **stack**; the OS allocates this memory and gives it to the process. the stack is used for local variables, function parameters, and return addresses.

The OS may also create some initial memory for the program’s **heap**. the heap is used for explicitly requested dynamically allocated data; programs request such space by calling `malloc()` and free it explicitly by calling `free()`.

The OS will also do some other initialization tasks related to input/output (I/O). For example, in UNIX systems, each process by default has three open **file descriptors**, for *standard input*, *output*, and *error*.

By loading the code and static data into memory, by creating and initializing a stack, and by doing other work as related to I/O setup, the OS has now set the stage for program execution.

### Process States

A process can be in one of the following states at any given time:

- Initial: being created and hasn't finished initialization yet

- Ready: is ready to be scheduled onto a CPU to run, but not scheduled at this moment.

- Running: scheduled on a CPU and executing instructions.

- Blocked: waiting for some event to happen, e.g., waiting for disk I/O completion or waiting for another process to finish, hence not ready to be scheduled at this moment.

- Terminated (Final): has exited/been killed but its information data structures have not been cleaned up yet 

<img title="" src="file:///home/elabyad/CLionProjects/OSTEP/notes/assets/process-states.png" alt="Process States" width="362" data-align="center">

### Data Structures

A few key data structures are used to keep track of state in typical operating systems. 

Sometimes people refer to the individual structure that stores information about a process as a *Process Control Block (PCB)*. This structure must include the machine state of the process, the status of the process, the *register context* (register contents) of each stopped process, and any other necessary information related to the process.

The collection of PCBs is the *process list* (or task list), the first essential data structure we meet in an OS.

`struct context {
    int eip;
    int esp;
    int ebx;
    int ecx;
    int edx;
    int esi;
    int edi;
    int ebp;
};
enum proc_state { UNUSED, EMBRYO, SLEEPING,
RUNNABLE, RUNNING, ZOMBIE };
/** The PCB structure. */
struct proc {
    char *mem;                   // Start of process memory
    uint sz;                     // Size of process memory
    char *kstack;                // Bottom of kernel stack
    enum proc_state state;       // Process state
    int pid;                     // Process ID
    struct proc *parent;         // Parent process
    void *chan;                  // If !zero, sleeping on chan
    int killed;                  // If !zero, has been killed
    struct file *ofile[NOFILE];  // Open files
    struct inode *cwd;           // Current directory
    struct context context;      // Register values context
    struct trapframe *tf;        // Trap frame of current interrupt
};`
