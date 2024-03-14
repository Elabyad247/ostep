1. Run process-run.py with the following flags: `-l 5:100,5:100`.
	What should the CPU utilization be (e.g., the percent of time the CPU is in use?), Why do you know this? Use the -c and -p flags to	see if you were right.
	
	Answer: 100%, because there is no I/O Operation

2. Now run with these flags: `./process-run.py -l 4:100,1:0`.
	These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use -c and -p to find out if you were right.
	
	Answer: 11 = 4 (process 0) + 1 (Run IO) + 5 (process 1) + 1 (IO Done)

3. Switch the order of the processes: `-l 1:0,4:100`. 
	What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)
	
	Answer: 7 = 1 (Run IO) + 4 (Process 0 & Process 1) + 1 (Remaining Process 0) + 1 (IO Done), yes the order matters, Process 1 using the CPU while process 0 waiting IO to be done. 

4. What happens when you run the following two processes `-l 1:0,4:100 -c -S SWITCH_ON_END`, one doing I/O and the other doing CPU work?
	
	Answer: process 1 will not start until process 0 finish

5. run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O `-l 1:0,4:100 -c -S SWITCH_ON_IO`. What happens now? Use -c and -p to confirm that you are right.
	
	Answer: process 1 will start when process 0 waits IO

6. One other important behavior is what to do when an I/O completes. With -I IO_RUN_LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes?
	`./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_LATER`
	Are system resources being effectively utilized?
	
	Answer: Process 0 will start the first IO instruction then waits until other processes finished then starts the remaining IO instructions, No because there are IO instructions can be done while the other processes using the CPU

7. Now run the same processes, but with `-I IO_RUN_IMMEDIATE` set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?

	Answer: Process 0 will start the IO instruction and another process will use the CPU, when IO is done we will switch to Process 0 and start the next IO instruction then another process uses the CPU, and so on until we finish all of them....
	because now we are using IO whenever it is available will using the CPU in the same time, and system resources being effectively utilized

8. Now run with some randomly generated processes using flags `-s 1 -l 3:50,3:50` or `-s 2 -l 3:50,3:50` or `-s 3 -l 3:50, 3:50`. 
	See if you can predict how the trace will turn out.
	What happens when you use the flag `-I IO_RUN_IMMEDIATE` vs that flag `-I IO_RUN_LATER`?
	What happens when you use the flag `-S SWITCH_ON_IO` versus `-S SWITCH_ON_END`?