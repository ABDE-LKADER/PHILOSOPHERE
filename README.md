# Philosophers Project Breakdown

## Key Concepts

### 1. Multithreading
Multithreading is a technique where multiple threads are spawned by a process to perform tasks concurrently. In the context of this project, each philosopher will be represented by a separate thread.

**Key Functions:**
- `pthread_create`: Create a new thread.
- `pthread_join`: Wait for a thread to terminate.
- `pthread_detach`: Detach a thread to reclaim resources when it terminates.

### 2. Mutexes
Mutexes (mutual exclusions) are used to prevent race conditions by ensuring that only one thread can access a resource at a time. Each fork in the philosophers' problem is protected by a mutex to ensure safe concurrent access.

**Key Functions:**
- `pthread_mutex_init`: Initialize a mutex.
- `pthread_mutex_destroy`: Destroy a mutex.
- `pthread_mutex_lock`: Lock a mutex.
- `pthread_mutex_unlock`: Unlock a mutex.

### 3. Thread Synchronization
Synchronization is crucial in ensuring that threads operate in a controlled manner. In this project, synchronization is achieved using mutexes to manage the forks.

### 4. Memory Management
Proper allocation and deallocation of memory is crucial. Each philosopher may dynamically allocate memory, which must be freed correctly to avoid memory leaks.

**Key Functions:**
- `malloc`: Allocate memory.
- `free`: Deallocate memory.

### 5. Timers and Delays
Timing functions are used to simulate the time spent eating, thinking, and sleeping. Accurate timing is essential to ensure the simulation runs correctly.

**Key Functions:**
- `usleep`: Sleep for a specified number of microseconds.
- `gettimeofday`: Get the current time of day.

## Project Breakdown

### Mandatory Part

1. **Initialization**
   - Parse command-line arguments.
   - Initialize data structures for philosophers and forks.
   - Initialize mutexes for forks.

2. **Thread Creation**
   - Create a thread for each philosopher.
   - Each thread runs a routine that simulates the philosopher's actions.

3. **Philosopher Routine**
   - Loop where each philosopher alternates between eating, thinking, and sleeping.
   - Use mutexes to pick up and put down forks.
   - Check if the philosopher dies due to starvation.

4. **Cleanup**
   - Join all philosopher threads.
   - Destroy all mutexes.
   - Free any allocated memory.

### Bonus Part

1. **Process Creation**
   - Use processes instead of threads for philosophers.
   - Manage inter-process communication using semaphores.

2. **Semaphore Initialization**
   - Initialize semaphores for managing forks.

3. **Philosopher Routine with Processes**
   - Similar to the thread routine but with inter-process communication.

4. **Cleanup**
   - Ensure all processes are properly terminated.
   - Destroy semaphores.
