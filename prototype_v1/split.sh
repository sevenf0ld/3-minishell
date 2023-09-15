#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd line arguments
args=("ls -la | cat | grep -wn c > outfile"
	"ls -l -a | cat | grep -w -n c > outfile"
	"< infile ls -l | wc -l > outfile"
	"echo -n -n -n"
	"echo -n"
	"ls txtfile"
	'echo "$example"'
	"echo '$example'"
	"echo '\$example'"
	"echo build.h '|' grep b"
	"echo build.h | grep b"
	)

# create a variable with the name of the executable
exe="./new_split"

cc -Wall -Werror -Wextra -g3 new_split.c -o new_split
# cc -Wall -Werror -Wextra -fsanitize=address -g3 new_split.c -o new_split

for arg in "${args[@]}"; do
    echo -e "$red $exe $arg: $none"
    leaks -atExit -- ./"$exe" "$arg"
    #./"$exe" "$arg"
done

rm -rf new_split.dSYM new_split
