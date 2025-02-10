#!/bin/bash

for n in {1..3000}; do  # Range of num of elements to sort
    for i in {1..5}; do # Num of runs
        output=$(./PmergeMe $(shuf -i 1-2147483647 -n "$n" | tr "\n" " ")) # capture output
        ret=$?

        if [ "$ret" -eq 123 ]; then
            echo "Fatal: found unsorted sequence"
            exit 1
        fi
		echo "$n" elements, test "$i": "ok"
    done
done

echo "Success! All sequences are sorted!"
