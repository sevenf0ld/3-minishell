#!/bin/bash

green='\033[0;42m'
none='\033[m'

args=("0"
	"2"
	"90"
	"254"
	"255"
	"256"
	"257"
	"1000"
	"-2147483648"
	"-2147483647"
	"-2147483649"
	"-214748364912"
	"-2"
	"-255"
	"-256"
	"-257"
	"-193"
	"2147483647"
	"2147483648"
	"2147483646"
        "abc"
        "9z"
	"2 a"
	"b 3"
	"4 4"
	"c c"
        "3 4 a"
    )

exe="./minishell"

make re --silent

reset

for arg in "${args[@]}"; do
	echo "exit $arg" | $exe
	echo -e "$green $? $none"

done
