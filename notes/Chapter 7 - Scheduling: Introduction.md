### Workload Assumptions

The *workload* is the set of all processes running on a system. Schedulers must make some assumptions about their workloads, and also employ a *scheduling metric* to compare different possible policies. a simple metric is turnaround time, the amount of time a job takes to complete. Alternatively, we could assess *fairness* (or some combination).
Assume that our workloads are:

- All jobs only use the CPU (so a single resource w/o blocking) and perform no I/O
- The run-time of each job is known

We look at these metrics to compare across policies:

- **Turnaround Time** &rarr; $T_{turnaround} = T_{completion} − T_{arrival}$

- **Response Time** &rarr; $T_{response} = T_{firstrun} − T_{arrival}$

- **Fairness**: we often need to *trade-off* between turnaround time and fairness

### Basic Policies

- **First-In-First-Out** (FIFO, or *First-Come-First-Serve*, FCFS)
  
  ![](https://www.josehu.com/assets/file/ostep-note/img/scheduling-FIFO.png)
  
  FIFO is intuitive but can often leads to the *convoy effect*: where a number of relatively short jobs get queued after a long job, yielding poor overall turnaround time. FIFO may work well in some cases such as caching, but not for CPU scheduling.

- **Shortest-Job-First** (SJF)
  
  ![](https://www.josehu.com/assets/file/ostep-note/img/scheduling-SJF.png)
  
  SJF is optimal on turnaround time if all jobs arrive at the same time, each job runs until completion, and their durations are known; however, in reality, this is rarely the case, and suppose A comes a little bit earlier than B & C in the above example, it encounters the same problem as in FIFO.

- **Shortest-Time-to-Completion-First** (STCF, or *Preemptive-Shortest-Job-First*, PSJF)
  
  ![](https://www.josehu.com/assets/file/ostep-note/img/scheduling-STCF.png)
  
  STCF is a *preemptive* policy - it can **preempt** a job in the middle if another one with shorter time to complete arrives. (Accordingly, FIFO and SJF schedulers are *non preemptive*.) STCF is optimal given our current assumption and the turnaround time metric.

- **Round-Robin** (RR)
  
  ![](https://www.josehu.com/assets/file/ostep-note/img/scheduling-RR.png)
  
  Above-mentioned policies are not really taking advantage of the time-sharing mechanisms. RR divides time into small slots (*scheduling quantum*) and then switches to the next job in the run queue in a determined order. RR is a **time slicing** scheduling policy. The time slice length should be chosen carefully: short enough to be responsive, and long enough to *amortize* the cost of context switches.
  
  RR is quite fair and responsive, but one of the worst on turnaround time. With RR, we can also take I/O into consideration: when job A blocks itself on doing a disk I/O, the scheduler schedules B for the next slot, *overlapping* these two jobs.
  
  ![](https://www.josehu.com/assets/file/ostep-note/img/scheduling-RR-with-IO.png)



### Considering IO

IO complicates things, because a single process ends up having periods where no useful work can be done. To get around this, the CPU treats each "burst" (normal period, not waiting on an IO request) as a separate job. This allows for *overlap*, which is generally good for resource utilization.

### Considering Unknown Time Requirements

Much of the prior discussion makes sense under the unrealistic assumption that we can know how long each job will take to run. Of course, in practice this isn't possible. It will turn out that operating systems use information from the recent past to make predictions about the future, here (known as a *multi-level feedback queue*).
