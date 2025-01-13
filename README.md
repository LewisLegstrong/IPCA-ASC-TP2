# IPCA-ASC-TP2

## Intro  
---  
Fork and Thread project to simulate the acquisition of sensor data and actuate depending on the average read.

The student's goal is to create a program capable of reading simultaneous temperature and humidity data from four sensors, and write them to a buffer.  

Each process will have two threads, one for each sensor, and a single buffer accessed by both threads.

The two processes are created from the ```main``` process, with one responsible for reading both temperature sensors, and one for the two humidity sensors.  

Sensor data _writes_ should be stored in a 15 slot buffer and accessed by two concurrent threads, and read by a third concurrent thread per process. 

![alt text](<docs/images/Full flowchart.jpg>)

## Forks 

### _fork()_ function:

A process can create a copy of itself through the system call _`fork()`_. The new process (child process) is completely independent of the process that created it (parent process). Although they are independent, both processes have the same resources associated with them, but these resources are allocated in different memory regions.  

### Parent Process

The **parent process** is the process that calls the _`fork()`_ function. After executing this function, the parent process continues its execution but now has a copy of itself, the **child process**. The parent process **receives** the PID _(Process ID)_ of the child process as the return value of the _`fork()`_ function, making it possible to identify and interact with the child process.

### Child Process

The **child process** is an **almost identical copy** of the parent process, created by the _`fork()`_ function. Although they share the same code, the child process has its own memory space and a **unique PID**, which makes it **independent**. The return value of the _`fork()`_ function for the **child process** is always **0**, allowing the differentiation between the execution of the child process and the parent process.

### Wait 

The _`wait()`_ function makes the _parent process_ wait for the execution of the child processes to complete, before proceeding with it's own execution.

**We know that:**
- Although the child process is a copy of the parent process, it has its own PID (_Process ID_).
- The parent process does not transfer any memory locks or pending signals to the child process.

**When successfully executed, the _`fork()`_ function returns:**
- **In the parent process:** the PID of the child process; -1 in case of an error.
- **In the child process:** 0 (zero).

## Threads

### What is a thread?
A thread is a tool that allows tasks to run simultaneously within a process, making it ideal for applications that require parallel processing. Threads are used to improve the efficiency and responsiveness of programs on multi-core systems.

### Threads in a Program
- In a **single-threaded** program, there is only one flow of execution, and all instructions are processed sequentially.
- In a **multi-threaded** program, multiple threads can execute simultaneously, increasing the program's efficiency and responsiveness.

### Critical Sections

A critical section is a sequence of instructions that cannot be accessed simultaneously by more than one thread. Critical sections must be protected to prevent concurrent access. For example, critical sections occur when thread A and thread B attempt to access a shared variable (or memory space) at the same time.

Different synchronization mechanisms ensure that only one execution unit can access the critical section at a time:

- Mutex
- Condition signaling

## Code Explanation

Sensor behaviour definition is written in `void *read_sensor_data ( void *arg );`. `*arg` is a pointer to a `sensor_info_t` defined as follows:     
``` 
typedef struct {
    int sensor_name;
    int sensor_reads;
    int sensor_timing;
    fifo_buffer_t *buffer;
} sensor_info_t;
``` 

The sensor value is acquired by the `rand()` function. It then adds to the buffer tail using `void add_to_buffer_tail ( fifo_buffer_t *buffer, float sensor_data );`.

The FIFO is implemented as an array that has its values moved when `MAX_BUFFER_SIZE` is reached, replacing the first value of the array.

The other function required is void `void *read_buffer_data ( void *arg );`, that grabs the last 5 added values and does an average of them, performing an action to the actuator.

There are `#define DEBUG` clauses for file creation with buffers to analyze data output.


## Resources

FIFO implementation: https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/

1st iteration test used linked lists, this webiste gave the tools to understand some of the problems  
~valgrind: https://www.cs.tufts.edu/cs/40/docs/valgrind.html~