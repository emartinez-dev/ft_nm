#!/bin/bash

# Check if at least an argument was provided
if [ $# -eq 0 ]; then
  echo "Usage: $0 <file1> <file2> ..."
  exit 1
fi

for file in "$@"; do
  # Check if the file exists
  if [ -f "$file" ]; then
	./ft_nm $file > a ; LC_COLLATE=C nm $file > b

	# Save the diff output to a variable
	diff_output=$(diff a b)

	# Check if the diff_output is empty
	if [ -z "$diff_output" ]; then
		echo "For '$file' the outputs are identical."
	else
		echo "For '$file', the outputs are different. Here's the diff:"
		echo "$diff_output"
	fi

	rm a b
	fi
done