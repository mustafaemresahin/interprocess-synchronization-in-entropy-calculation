# Interprocess Synchronization in Incremental Entropy Calculation (PA3)

## Overview
This repository contains an enhanced version of the multithreaded incremental entropy calculator from previous assignments. This version introduces interprocess synchronization using named POSIX semaphores, pthread mutex semaphores, and pthread condition variables. This project was developed as part of my Operating Systems course at the University of Houston.

## Objective
The goal of this assignment is to utilize interprocess synchronization mechanisms in UNIX for coordinating multiple threads. This is done in the context of calculating the entropy of CPUs in a multiprocessor system based on their scheduling information.

## Features
- **Multithreading with Synchronization**: Implements POSIX threads with synchronization using mutexes and condition variables.
- **STDIN Input Processing**: Reads scheduling information from STDIN, accommodating dynamic input scenarios.
- **Synchronized Output**: Coordinates thread output to prevent race conditions and ensure orderly display of results.

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/mustafaemresahin/interprocess-synchronization-in-entropy-calculation.git
```

2. Navigate to the repository directory:

```bash
cd interprocess-synchronization-in-entropy-calculation
```

3. Compile the program using g++ with thread support:

```bash
g++ -pthread -o entropyCalculator main.cpp
```

4. Run the program and input the scheduling information:

```bash
./entropyCalculator
```

Input the scheduling information when prompted or redirect from a file.

## Input Format
The program expects input in the following format, each line representing a CPU's scheduling information:

```bash
[Task] [Execution Time] [Task] [Execution Time] ...
```

Example:

```bash
A 2 B 4 C 3 A 7
B 3 A 3 C 3 A 1 B 1 C 1
```


## Output
The program outputs the scheduling information and calculated entropy for each CPU in an orderly manner, ensuring thread synchronization.

Example Output:

```bash
CPU 1
Task scheduling information: A(2), B(4), C(3), A(7)
Entropy for CPU 1
0.00 0.92 1.53 1.42

CPU 2
Task scheduling information: B(3), A(3), C(3), A(1), B(1), C(1)
Entropy for CPU 2
0.00 1.00 1.58 1.57 1.57 1.58
```

## Dependencies
- g++ compiler with support for C++11 or later.
- POSIX threads library.

## Acknowledgments
Special thanks to Dr. Rincon for the foundational algorithm and for their guidance and support.
