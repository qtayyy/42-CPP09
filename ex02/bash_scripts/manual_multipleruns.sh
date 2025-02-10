#!/bin/bash

# Generate n random numbers (last arg of shuf) between 1 and 2147483647 and
# pass to PmergeMe. Whole process is done x times (for loop).
for i in {1..1000}; do
    ./PmergeMe $(shuf -i 1-2147483647 -n 22 | tr "\n" " ")
	ret=$?

	if [ "$ret" -eq 123 ]; then
		exit 1
	fi
done
