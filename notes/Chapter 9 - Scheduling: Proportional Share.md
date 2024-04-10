Proportional share schedulers optimize for fairness (guaranteeing each job a certain percentage of CPU time) rather than turnaround or response time. This is known as *lottery scheduling*: a lottery is periodically held to determine which process gets to run next.

#### Tickets Represent Shares

*Tickets* represent the share of a resource that a process should receive, so if process has tickets and has , then gets 75% of CPU time probabilistic-ally.

#### Ticket Mechanisms

Tickets can be manipulated. For example, a user can allocate their tickets to their jobs however they choose (*ticket currency*). Tickets can also be *transferred*, and even their value can be *inflated* within a group of trusted processes.

#### Implementation

Lottery scheduling can be implemented extremely easily. All we need is a random number generator, knowledge of the total number of tickets, and access to the process list. Then, finding the winner is just like indexing into a list.

#### Unfairness

In expectation, a random scheduler will allocate resources in accordance with the ticket distribution. Because this doesn't always happen, especially with small sample sizes, we can quantify the drift using an *unfairness metric*.

#### Ticket Assignment

It isn't obvious how to allocate tickets, particularly without getting information from the user.

#### Stride Scheduling

To deal with the unfairness that can arise due to randomness, there exist deterministic algorithms like *stride*. However, the trade-off these make is that they require that we maintain some global state.

#### Linux's Completely Fair Scheduler

Linux's scheduler aims to evenly divide CPU among competing processes. To achieve this, is uses a concept called `vruntime`. Running processes accumulate `vruntime`, and whenever a scheduling decision is made, the process with the *lowest* `vruntime` is chosen. Parameters tune things like how frequently the scheduler preempts running processes, with the trade-off being between perfect fairness and performance. Other parameters like `min_granularity` prevent the scheduler from preempting jobs too frequently, especially when there are many competing jobs at a time.

Rather than using tickets, Unix has a notion of "niceness", where programs that have more negative niceness have higher priority. Red-black trees (balanced binary trees) are used to ensure that the scheduler must do minimal work while selecting the next process to run.
