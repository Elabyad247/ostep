To virtualize the CPU and coordinate multiple processes, the virtualization must be both *performant* (no excessive overhead) and *controlled* (OS controls which one runs at which time).

OS balances these two goals with the following two techniques:

- **Limited Direct Execution** (LDE): just run the user program directly on the CPU; OS is not simulating processor hardware; but the OS must be able to re-gain control in some way to do the coordination.
- **Time-Sharing** (**Multiprogramming**): divide time into small slots, schedule a process to run for a few slots and switch to another one, constantly switching back between ready processes.

The OS needs to solve several problems to enable the combination of these two techniques.

#### Problem 1: Restricted Operations

If we just let a process run all possible instructions directly, it will have dominant control over the machine. Hence, the processor lists a set of sensitive instructions as *privileged* instructions, which can only be run in high privilege mode. A user process normally runs in **user mode**, with restricted permissions. When it invokes a syscall, it switches to **kernel mode** to execute the registered syscall handler containing privileged instructions. After the handler has done its work, it returns the process back to user mode.

The switching between modes is enabled through a mechanism called **trap**. The special trap instruction simultaneously jumps into somewhere in kernel mode and raises the privilege level to kernel mode. This also includes changing the stack pointer to the *kernel stack* reserved for this process, and saving the process's user registers into the kernel stack.

The kernel refers to a *trap table* to tell which code to execute (i.e. which *trap handler*) based on the exception that was raised. This table is initialized with the OS boots up and remains constant until the machine is rebooted.

> Trapping into kernel from software through a syscall is sometimes called a **software interrupt**.
> 
> We often use **trap** to name an active syscall made by the program. We use **exception** (or **fault**) to name a passive fall-through into kernel if the program misbehaves (e.g., tries to directly call a privileged instruction) or encounters an error (e.g., runs out-of-memory).

#### Problem 2: Switching Between Processes

Another big issue is that the OS must be able to re-gain control in the middle of the user-level execution of a process, and achieve a switch between processes.

Early systems attempted a *cooperative approach*, where the OS trusts processes to give up control. This obviously is problematic because it can't deal with malicious or problematic programs that don't cede control.

 We need help from a special hardware component - the *timer*.

The behavior of a hardware device sending a signal to the processor to pause it current user code execution and to run a specified handler is called an **interrupt**.

One particularly important type of interrupt is the **timer interrupt**, issued by the timer every configured interval

After a timer interrupt occurs, the OS *scheduler* decides whether to cede control back to that running process to switch to a new one.

> Interrupts need to be *disabled* during the handling of a trap/interrupt, so that every interrupt is handled to its completion.

#### Context Switch & Scheduler

The context of a process is defined as the set of important registers values. 
Switching from process A to process B is a **context switch** procedure:

1. Save the current registers values (the context of A) into A's PCB
2. Restore the saved register values (the context) of B from B's PCB
3. Jump to B

The timer interrupt typically calls the **scheduler**: a routine that chooses which process to run. It then performs a context switch to switch to the target process.

<img title="" src="file:///home/elabyad/CLionProjects/OSTEP/notes/assets/context-switch-procedure.png" alt="assets/context-switch-procedure.png" width="303" data-align="center">

> Note the difference between *user registers* (those at user-level execution of the program) and *kernel registers* (those actually stored in the context). At a timer interrupt, the user registers are already stored into the process's kernel stack and the registers have been switched to the set for kernel execution (PC pointing to the handler code, SP pointing to kernel stack, etc.). Hence, the context saved for a process is actually the set of its kernel registers, and the user registers are recovered by the "return-from-trap" operation - this is when the process returns back to user mode.
