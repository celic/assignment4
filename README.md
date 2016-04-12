# assignment4

Questions:

* RNG provides doubles, what should be the conversion to unsigned int


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

* Total execution time
* I/O time

Time them both separately. Total execution includes I/O in the end. Use the clock cycles counter with 1.6GHz clock rate.
