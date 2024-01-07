# Interprocess Synchronization in Incremental Entropy Calculation (PA3)

## Overview
This repository contains an enhanced version of the multithreaded incremental entropy calculator from previous assignments. This version introduces interprocess synchronization using named POSIX semaphores, pthread mutex semaphores, and pthread condition variables.

## Objective
The goal of this assignment is to utilize interprocess synchronization mechanisms in UNIX for coordinating multiple threads. This is done in the context of calculating the entropy of CPUs in a multiprocessor system based on their scheduling information.

## Features
- **Multithreading with Synchronization**: Implements POSIX threads with synchronization using mutexes and condition variables.
- **STDIN Input Processing**: Reads scheduling information from STDIN, accommodating dynamic input scenarios.
- **Synchronized Output**: Coordinates thread output to prevent race conditions and ensure orderly display of results.

## How to Run