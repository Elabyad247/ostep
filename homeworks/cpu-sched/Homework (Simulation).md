1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.
   **ANSWER:**
   FIFO: 
   
   - JOB 1: Response = 0, Turnaround = 100
   
   - JOB 2: Response = 100, Turnaround = 200
   
   - JOB 3: Response = 200, Turnaround = 300
   
   - Average: Response = 100,  Turnaround 200
   
   SJF:
   
   - JOB 1: Response = 0, Turnaround = 100
   
   - JOB 2: Response = 100, Turnaround = 200
   
   - JOB 3: Response = 200, Turnaround = 300
   
   - Average: Response = 100, Turnaround 200

2. Now do the same but with jobs of different lengths: 100, 200, and 300.
   **ANSWER:** 
   FIFO:
   
   - JOB 1: Response = 0, Turnaround = 100
   
   - JOB 2: Response = 100, Turnaround = 300
   
   - JOB 3: Response = 300, Turnaround = 600
   
   - Average: Response = 133.33, Turnaround 333.33
   
   SJF:
   
   - JOB 1: Response = 0, Turnaround = 100
   
   - JOB 2: Response = 100, Turnaround = 300
   
   - JOB 3: Response = 300, Turnaround = 600
   
   - Average: Response = 133.33, Turnaround 333.33

3. Now do the same, but also with the RR scheduler and a time-slice of 1.
   **ANSWER:** 
   RR:
   
   - JOB 1: Response = 0, Turnaround = 298
   
   - JOB 2: Response = 1, Turnaround = 499
   
   - JOB 3: Response = 2, Turnaround = 600
   
   - Average: Response = 1, Turnaround 465.67

4. For what types of workloads does SJF deliver the same turnaround times as FIFO?
   **ANSWER:** Job lengths are equal or arrive in ascending order.

5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?
   
   **ANSWER:** Jobs length are same and quantum length equals the job length.

6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?
   
   **ANSWER:** Response time will increase, there is linear relationship between job length and response time.

7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?
   
   **ANSWER:** Response time increases linearly with quantum length increase, the worst-case response time is $(N-1)*q/N$


