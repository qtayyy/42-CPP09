#!/bin/bash

# Generate n random numbers between 1 and 2147483647 and pass to PmergeMe
./PmergeMe $(shuf -i 1-2147483647 -n 21 | tr "\n" " ")
