# assignment4

Turns out Carothers made a mistake and there are no compact cases based on the specification. Follow the specification and relabel the compact to have a small boundary between ranks.

Runs:

* 64 MPI task with 0 threads
* 16 MPI tasks with 4 threads
* 4 MPI tasks with 16 threads
* 1 MPI task with 64 threads per node

Repeat with 32, 64, 128 nodes. 

I/O:

* 1 single file for all MPI ranks, with 8MB block boundaries between rank using MPI File write at all collective I/O operation.
* 1 single file for all MPI ranks, with compact boundaries between ranks MPI File write at all collective I/O operation.
* 4 ranks share the same file using MPI File write at (non-collective write call) with 8MB block boundaries between ranks.
* 4 ranks share the same file using MPI File write at (non-collective write call) with compact boundaries between ranks.
* 8 ranks share the same file using MPI File write at (non-collective write call) with 8MB block boundaries between ranks.
* 8 ranks share the same file using MPI File write at (non-collective write call) with compact boundaries between ranks.
* 32 ranks share the same file using MPI File write at (non-collective write call) with 8MB block boundaries between ranks.
* 32 ranks share the same file using MPI File write at (non-collective write call) with compact boundaries between ranks.

Compact refers to having no space between data of separate ranks.

Timing:

* Compute execution time
* I/O time

Time them both separately. Total execution includes I/O in the end. Use the clock cycles counter with 1.6GHz clock rate.

Looking at 96 data points total. 

Graph 1:
* 3 plot lines, 32 node, 64 node, 128 node
* Threads per node (x-axis)
* Compute execution time (y-axis)

Graph 2-4:
* 2 lines per graph, 8MB boundary or compact
* Level of file sharing, ranks per file (x-axis)
* I/O bandwidth (y-axis)

