#!/bin/bash

# create an array of cmd line arguments
args=("ls -la | cat | grep -wn c > outfile" "ls -l -a | cat | grep -w -n c > outfile" "< infile ls -l | wc -l > outfile" "echo -n -n -n" "echo -n" "ls txtfile" 'echo "$example"' "echo '$example'" "echo '\$example'" "echo build.h '|' grep b" "echo build.h | grep b"
	)

# create a variable with the name of the executable
exe="./minishell_split"

for arg in "${args[@]}"; do
    echo -e "$exe $arg:"
    ./"$exe" "$arg"
	echo ""
done
