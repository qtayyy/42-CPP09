#!/bin/bash

# Generate 3000 random numbers between 1 and 100000, shuffle them, and pass to PmergeMe
./PmergeMe $(shuf -i 1-2147483647 -n 3500 | tr "\n" " ")
