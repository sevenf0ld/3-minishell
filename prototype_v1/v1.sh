#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd line arguments
args=("ls -la | cat | grep -wn c > outfile"
	"ls -l -a | cat | grep -w -n c > outfile"
	"ls -l -a | cat | grep -w -n c >> outfile"
	"< infile ls -l | wc -l > outfile"
	"cmd1 << LIMITER | cmd2 >> file"
	"echo -n -n -n"
	"echo -n"
	"ls txtfile"
	'echo "$example"'
	"echo '$example'"
	"echo '\$example'"
	"echo build.h '|' grep b"
	"echo build.h | grep b"
	"echo -n-n-n-n-n"
	"ls -llllllaaa"
	"ls -l-l-l-la"
	"ls -l -l -l -la"
	"ls --------la"
	"cat *.c | grep | -wn token"
	)

# create a variable with the name of the executable
exe="./v1"

set -e

make -f Makefile

for arg in "${args[@]}"; do
    echo -e "$red $exe $arg: $none"
    #leaks -atExit -- ./"$exe" "$arg"
    ./"$exe" "$arg"
done

rm -rf v1.dSYM v1
make fclean
