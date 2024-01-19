#!/bin/bash

blue='\033[0;44m'
none='\033[m'

args=("./hey.c"
	"./hey1.c"
	"./nothing"
	"./smthn.txt"
    )

exe="./126"

clang -Wall -Werror -Wextra -fsanitize=address 126.c -o 126

for arg in "${args[@]}"; do
	echo -e "$none"
	echo -e "$blue"
	$exe $arg
	echo -e "$none"
done
