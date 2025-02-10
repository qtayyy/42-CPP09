#!/bin/bash

# Known max comparisons for the Ford-Johnson algorithm
declare -A limits=( [1]=0 [2]=1 [3]=3 [4]=5 [5]=7 [6]=10 [7]=13 [8]=16 [9]=19 [10]=22 [11]=26 [12]=30)

for n in {3..12}; do  # Run for n = 1 to 12
    for i in {1..200}; do # Run 200 times each for n elements
        output=$(./PmergeMe_bench $(shuf -i 1-2147483647 -n $n | tr "\n" " "))
        ret=$?
		num1=$(echo "$output" | sed -n '1p')
		num2=$(echo "$output" | sed -n '2p')

        if [ "$ret" -eq 123 ]; then
            echo "Fatal: found unsorted sequence"
            exit 1
        fi
		if [[ "$num1" -gt "${limits[$n]}" || "$num2" -gt "${limits[$n]}" ]]; then
            echo "Error: Output exceeded limit for n=$n (Max allowed: ${limits[$n]}, Found: deque: $num1; vector: $num2)"
            exit 1
        fi
		echo "Num of comparisons: deque: $num1; vector: $num2"
		echo "$n elements, test $i: ok"
    done
done

echo "Success! All sequences are sorted and num of comparisons used are within limits!"
