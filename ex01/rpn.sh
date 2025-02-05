#!/bin/bash

inputs=(
	"5 3 +"
	"2 7 -"
	"6 4 *"
	"8 2 /"
	"3 4 + 2 *"
	"9 1 2 + *"
	"2 3 4 * +"
	"4 2 3 - * 7 +"
	"3 4 + 2 * 7 /"
	"6 3 2 * + 8 -"
	"5 1 2 - 4 * + 3 -"
	"7 2 8 * + 3 -"
	"2 7 1 1 + - / 3 * 2 1 1 + + -"
	"6 3 / 2 * 5 +"
	"4 5 2 - /"
	"7 1 - 3 2 * /"
	"8 3 2 / /"
	"3 +"
	"4 0 /"
	"7 2 3"
	"9 2 - 4"
	"5 6 * 0 /"
	"2 2 + 5 * 0 3 /"
	"1 2 3 +"
)

# Iterate over each input string and pass it to the RPN program
for input in "${inputs[@]}"; do
  echo "Input: $input"
  ./RPN "$input"
  echo "-----------------------"
done
