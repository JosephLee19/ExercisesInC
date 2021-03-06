## Chapter 1


### Compilation

1) Give an example of a feature common in interpreted languages that is rare in compiled languages.
Platform independance - since compiled languages are compiled into machine specific assembly, they are specific to that machine whereas interpreted languages work under the same interface regardless of platform. Another big one would be that the use of dynamic types is almost exclusively reserved for interpreted languages

2) Name two advantages of static typing over dynamic typing.
In static typing, many errors can be caught earlier in the development process (for instance, if an integer maps to a string, that would be caught compile-time in static typing, but not until run-time in dynamic typing.  Also since everything is pre-assigned compile-time in static typing, the run speed would probably be faster for static typing.

3) Give an example of a static semantic error.
Failure to declare a variable.  (quick note to self, a semantic error is an error that is different from syntactic errors...they are dynamic if not caught until run-time and static if the compiler can detect it)

4) What are two reasons you might want to turn off code optimization?
Debugging your code in assembly - turning off optimization might make it more readable. Another reason might be if you want to try to optimize your code manually or in a different way.

5) When you run `gcc` with `-S`, why might the results look different on different computers?
Since -S generates assembly code - could look different on different computers since assembly code is machine specific.  A different machine architecture would mean that the assembly code would be different.

6) If you spell a variable name wrong, or if you spell a function name wrong, 
the error messages you get might look very different.  Why?
Misspelled variables will be caught during compilation whereas a misspelled function would be caught during linking, hence the different error messages.

7) What is a segmentation fault?
Segmentation fault occurs when a program tries to read or write to the wrong type of memory (for instance trying to grab a global variable out of the stack).

## Chapter 2


### Processes

1) Give a real-world example of virtualization (ideally not one of the ones in the book).
Classrooms - each class (usually) feels like they 'own' all the space, but really it is a shared space where each class virtually owns the space when no other class is using it

2) What is the difference between a program and a process?
Put simply, a process is a running program...a program is a set of instructions.

3) What is the primary purpose of the process abstraction?  What illusion does the process abstraction create?
Process abstraction is a way of allowing users and developers to more easily work with complicated systems, a specific example is virtualization by which the process 'thinks' it has exclusive access to all of the resources on the computer.
4) What is the kernel?
The kernel is the part of the operating system responsible for core capabilities like starting threads

5) What is a daemon?
A daemon is a process that runs in the background to provide operating system services 

## Chapter 3


### Virtual memory

1) The Georgian alphabet has 33 letters.  How many bit are needed to specify a letter?
You would need 6 bits (2^5 only equals 32, 2^6 is 64.)

2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.  
Ignoring the details of the encoding scheme, how many different characters can be represented?
2^32 characters, or about 4.2 Billion characters

3) What is the difference between "memory" and "storage" as defined in Think OS?
If it is volatile then it is (typically) memory, if non-volatile then it is (typically) storage - i.e. if its contents are lost when the computer is powered down then memory, otherwise storage.

4) What is the difference between a GiB and a GB?  What is the percentage difference in their sizes?
GiB is a power of 2 (2^30) whereas GB is a power of 10 (10^9). The percentage difference is ~7%.

5) How does the virtual memory system help isolate processes from each other?
It helps isolate processes by using virtual memory addresses that are then mapped to physical address - such that there is NO virtual address that will map to the physical address that another process is using (unless specifically told to do so?)

6) Why do you think the stack and the heap are usually located at opposite ends of the address space?
The heap and stack are probably located at opposite ends because they are the memory segments that vary most in size...it gives room for both of them to 'grow' or 'shrink' without running into each other or bumping things around.
7) What Python data structure would you use to represent a sparse array?
I personally would probably use a dictionary, but I also think that there are libraries that allow you to create sparse arrays and sparce matrices directly (though under the hood, do they just use dictionaries?)
8) What is a context switch?
A context switch is when the CPU switches from one process to another

In this directory, you should find a subdirectory named `aspace` that contains `aspace.c`.  Run it on your computer and compare your results to mine.
  
1) Add a second call to `malloc` and check whether the heap on your system grows up (toward larger addresses).  

2) Add a function that prints the address of a local variable, and check whether the stack grows down.  

3) Choose a random number between 1 and 32, and allocate two chunks with that size.  
How much space is there between them?  Hint: Google knows how to subtract hexadecimal numbers.


## Chapter 4


### Files and file systems

1) What abstractions do file systems provide?  Give an example of something that is logically 
true about files systems but not true of their implementations.
File systems abstract everything as a stream of bytes rather than interfacing directly with the blocks on the hard drive.

2) What information do you imagine is stored in an `OpenFileTableEntry`?
I would imagine that it is similar to a page table, except instead of mapping virtual memory addresses to physical memory addresses it maps a table entry to the actual hard drive block location.

3) What are some of the ways operating systems deal with the relatively slow performance of persistent storage?
Block transfers, Prefetching, Buffering, and Caching - essentially the time it takes to retreive an 8 KiB block is about the same as it takes to load a single byte, sometimes the program can just load the whole block (making the assumption that it will probably need other parts of the block?). Prefetching is basically what it sounds like - the operating system predicts that it will need something and loads it ahead of time. Buffering is that after you write something, it is only stored in memory not storage - if you change the block several times before it is written to the disk then you only have to write to the disk once.  Caching is that if a process used a block of memory recently, the operating system keeps a copy of the block in its cache so it can handle future requests with greater speed.


4) Suppose your program writes a file and prints a message indicating that it is done writing.  
Then a power cut crashes your computer.  After you restore power and reboot the computer, you find that the 
file you wrote is not there.  What happened?
You probably never closed the file - in which case the information was likely still only stored in memory instead of being written to the disk.  When the power cut crashed the computer, memory was lost and the file was never written to storage, so it was lost.

5) Can you think of one advantage of a File Allocation Table over a UNIX inode?  Or an advantage of a inode over a FAT?
I feel like the FAT handles very large files better because you don't have a block that points to other blocks that points to other blocks...

6) What is overhead?  What is fragmentation?
Overhead is the data structures used by the allocator - fragmentation is when you have some blocks partially or completely unused

7) Why is the "everything is a file" principle a good idea?  Why might it be a bad idea?
It works pretty well because the file system is really more like a "stream of bytes" abstraction, which applies to a lot of things besides just files. I can't think of something specifically that would be a bad reason to use this abstraction, unless there was ever anything that you needed to know exactly how something worked under the hood, in which case an abstraction would be a bad idea.

If you would like to learn more about file systems, a good next step is to learn about journaling file systems.  
Start with [this Wikipedia article](https://en.wikipedia.org/wiki/Journaling_file_system), then 
[Anatomy of Linux Journaling File Systems](http://www.ibm.com/developerworks/library/l-journaling-filesystems/index.html).  
Also consider reading [this USENIX paper](https://www.usenix.org/legacy/event/usenix05/tech/general/full_papers/prabhakaran/prabhakaran.pdf).


## Chapter 5


### Bits and bytes

1) Suppose you have the value 128 stored as an unsigned 8-bit number.  What happens if you convert 
it to a 16-bit number and accidentally apply sign extension?

2) Write a C expression that computes the two's complement of 12 using the XOR bitwise operator. 
Try it out and confirm that the result is interpreted as -12.

3) Can you guess why IEEE floating-point uses biased integers to represent the exponent rather than a
sign bit or two's complement?

4) Following the example in Section 5.4, write the 32-bit binary representation of -13 in single precision 
IEEE floating-point.  What would you get if you accidentally interpreted this value as an integer?

5) Write a function that takes a string and converts from lower-case to upper-case by flipping the sixth bit.  
As a challenge, you can make a faster version by reading the string 32 or 64 bits at a time, rather than one
character at a time.  This optimization is made easier if the length of the string is a multiple of 4 or 8 bytes.



## Chapter 6


### Memory management

1) Which memory management functions would you expect to take constant time?  Which ones take time proportional to the size of the allocated chunk?

2) For each of the following memory errors, give an example of something that might go wrong:

a) Reading from unallocated memory.

b) Writing to unallocated memory.

c) Reading from a freed chunk.

d) Writing to a freed chunk.

e) Failing to free a chunk that is no longer needed.


3) Run

    ps aux --sort rss

to see a list of processes sorted by RSS, which is "resident set size", the amount of physical 
memory a process has.  Which processes are using the most memory?

4) What's wrong with allocating a large number of small chunks?  What can you do to mitigate the problem?

If you want to know more about how malloc works, read 
[Doug Lea's paper about dlmalloc](http://gee.cs.oswego.edu/dl/html/malloc.html)



## Chapter 7


### Caching

1) What happens if a program writes a new value into the program counter?

2) What is the fundamental problem caches are meant to solve?

3) If cache access time is 1 ns and memory access time is 10 ns, what is the average
access time of a program with hit rate 50%?  How about 90%?

4) The book gives several examples of programming language features, like loops, that tend 
to improve locality in the access pattern of instructions and/or data.  Can you think of other examples?  
Or counter-examples that might decrease locality?

5)  If you refactor a program to improve locality, would you say the program is "cache aware"?  Why not?

6) See if you can estimate the cost of a memory cache by comparing the prices of two similar CPUs with 
different cache sizes.

7) Why are cache policies generally more complex at the bottom of the memory hierarchy?

8) Can you think of a strategy operating systems could use to avoid thrashing or recover when it occurs?

Run the cache code on your laptop or another computer and see if you can infer the cache size and block size.  
If you can find the technical specifications for your computer, see if your inferences are right.

1) In this directory you should find a subdirectory named `cache` that contains `cache.c` and supporting files.  Read `cache.c`, then run `make` and `./cache`.

2) Run `python graph_data.py` to see the results.  What can you infer about the cache structure on your computer?


## Chapter 8


### Multitasking

1) What is the kernel's most basic task?
Interupts and context switches - interupt signals a process to stop, context switch is when switches from one process to another.


2) When an interrupt occurs, what part of the hardware state is saved by hardware?
Hardware state includes program counter (keeps track of where in the program) and registers (translating from virtual address to physical address).  Registers get saved to stack (memory). Program counter is what is saved by hardware so that it isn't overwritten by the program that actually conducts the interrupt..


3) What is the difference between an interrupt and a context switch?

4) Give an example of an event that might cause a process to move from the blocked to the ready state.

5) Why might a scheduler want to give higher priority to an I/O bound process?

When I make French toast, I usually make a batch of 12 slices.  But my griddle only has room for 8 slices.  Each piece of toast has to cook for 5 minutes on each side.  How can I schedule 12 slices onto 8 "cores" to minimize the elapsed time to cook all 12 slices?  (Note: this question is not hypothetical; this is really how I make French toast.)
8 cooking, flip half and put 4 new on, flip and add for half cooked on. Highest throughput.


## Chapter 9


### POSIX threads and mutexes

As you read Chapter 9, you should compile and run the example code.  By the nature of multi-threaded programs, you results will probably be different from mine, possibly in interesting ways.

1) Why does each thread have its own stack?

2) What does the `gcc flag -lpthread` do?

3) What does the argument of `pthread_exit` do?

4) Normally the same thread that created a thread also waits to join it.  What happens if another thread tries to join a thread it did not create?

5) What goes wrong if several threads try to increment a shared integer at the same time?

6) What does it mean to "lock a mutex"?



## Chapter 10


### Condition variables

1) What does it mean to say that a data structure is thread safe?

2) In the circular buffer implementation of a queue, why is the maximum number of elements in the queue `n-1`,
if `n` is the size of the array?

3) If there is no mutex to protect the queue, give an example of a sequence of steps that could leave
the queue in an inconsistent state.

4) When a thread calls cond_wait, why does it have to unlock the mutex before blocking?

5) When a thread returns from cond_wait, what do we know is definitely true?  What do we think is probably true?

6) What happens if you signal a condition variable when there are no waiting threads?

7) Do you have to lock the mutex to signal a condition variable?

8) Does the condition have to be true when you signal a condition variable?


 
## Chapter 11


### Semaphores in C
