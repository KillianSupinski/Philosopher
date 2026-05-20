# Philosophers

`Philosophers` is a 42 School project based on the classic dining philosophers problem.

The goal of the project is to understand how to manage multiple threads, shared resources and synchronization using mutexes in C.

This project helped me improve my understanding of concurrency, race conditions, deadlocks, timing precision and memory management.

## Project Context

Philosophers is an individual project from the 42 curriculum.

The objective is to simulate philosophers sitting around a table.  
Each philosopher alternates between eating, sleeping and thinking.  
To eat, a philosopher needs two forks, represented as shared resources protected by mutexes.

The challenge is to avoid race conditions, prevent deadlocks and correctly detect when a philosopher dies.

## Features

- Multi-threaded simulation
- One thread per philosopher
- Mutex-based fork management
- Death detection
- Eating, sleeping and thinking cycles
- Optional meal limit
- Timestamped logs
- Protection against data races
- Clean memory and mutex destruction

## Technologies

- C
- POSIX threads
- Mutexes
- Time management
- Makefile
- Linux / UNIX system calls

## Rules

Each philosopher can be in one of the following states:

- Eating
- Sleeping
- Thinking
- Dead

A philosopher must take two forks before eating.  
If a philosopher does not eat before `time_to_die`, the simulation stops and the philosopher is declared dead.

## Usage

The program takes 4 or 5 arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

```text
number_of_philosophers
Number of philosophers and forks.

time_to_die
Time in milliseconds before a philosopher dies if they do not eat.

time_to_eat
Time in milliseconds a philosopher spends eating.

time_to_sleep
Time in milliseconds a philosopher spends sleeping.

number_of_times_each_philosopher_must_eat
Optional argument. If provided, the simulation stops when all philosophers have eaten at least this number of times.
```

## Installation

Clone the repository:

```bash
git clone https://github.com/KillianSupinski/philosophers.git
cd philosophers
```

Compile the project:

```bash
make
```

## Makefile Commands

```bash
make
```

Compiles the project.

```bash
make clean
```

Removes object files.

```bash
make fclean
```

Removes object files and the executable.

```bash
make re
```

Recompiles the project from scratch.

## Examples

Run a simulation with 5 philosophers:

```bash
./philo 5 800 200 200
```

Run a simulation where each philosopher must eat 7 times:

```bash
./philo 5 800 200 200 7
```

Example where a philosopher may die:

```bash
./philo 4 310 200 100
```

Example with only one philosopher:

```bash
./philo 1 800 200 200
```

## Output Example

```text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
400 1 is thinking
```

If a philosopher dies:

```text
410 3 died
```

## What I Worked On

My main work on this project included:

- Creating and managing philosopher threads
- Implementing mutex protection for forks
- Managing shared simulation data
- Handling precise timing in milliseconds
- Detecting philosopher death
- Preventing data races
- Avoiding deadlocks
- Managing the optional meal limit
- Cleaning allocated memory and destroying mutexes
- Debugging thread synchronization issues

## What I Learned

Through this project, I improved my understanding of:

- Multi-threaded programming in C
- POSIX threads
- Mutexes and shared resources
- Race conditions
- Deadlock prevention
- Timing and simulation loops
- Memory management
- Debugging concurrent programs
- Structuring a C project with multiple files

## Project Status

Project completed as part of the 42 curriculum.
