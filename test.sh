#!/bin/bash

# Check if an argument was provided
if [ -z "$1" ]; then
  echo "Usage: $0 <file>"
  exit 1
fi

filename=$1

./ft_nm $filename > a ; LC_COLLATE=C nm $filename > b

# Save the diff output to a variable
diff_output=$(diff a b)

# Check if the diff_output is empty
if [ -z "$diff_output" ]; then
  echo "The outputs are identical."
else
  echo "The outputs are different. Here's the diff:"
  echo "$diff_output"
fi

rm a b
