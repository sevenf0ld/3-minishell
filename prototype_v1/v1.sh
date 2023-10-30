#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd line arguments
args=("ls -la | cat | grep -wn c > outfile"
    "ls -l -a | cat | grep -w -n c > outfile"
    "ls -l -a | cat | grep -w -n c >> outfile"
    "ls-la"
    "ls txtfile"
    "ls -llllllaaa"
    "ls -l-l-l-la"
    "ls -l -l -l -la"
    "ls --------la"
    "ls > firstfile > lastfile"
    "ls - l"
    "ls -l bs.txt"
    "ls help.txt die.txt"
    "ls something.txt -l"
    "ls -la >> outone.txt >> outtwo.txt | wc -c"
    ">> outone.txt >> outtwo.txt ls -la | wc -l"
    "> outone.txt > outtwo.txt > outthree.txt ls -llllllla | wc -l"
    "< infile ls -l >> outfile | cat | ls"
    "< main.c ls -l >> outfile | cat | ls"
    "< infile ls -l | grep one > outfile"
    "< main.c ls -l | grep one > outfile"
    "cat *.c | grep | -wn token"
    "cat | cat | ls"
    "< infile ls -l | wc -l > outfile"
    "< main.c ls -l | wc -l > outfile"
    "cmd1 << LIMITER | cmd2 >> file"
    "echo -n -n -n"
    "echo -n"
    'echo " " " " " " | cat -e'
    'echo " " " " " "'
    "echo ' ' ' ' ' ' | cat -e"
    "echo '$example'"
    "echo '\$example'"
    'echo "$example"'
    "echo \$example"
    "echo \$HOME"
    'echo $USER'
    "echo \$MADi\$HATTER"
    'echo $HOME$USER'
    'echo $HOME$USERi'
    'echo i$HOME$USERi'
    'echo $HOMEi'
    'echo i$HOMEi'
    'echo i$HOME'
    "echo ''"
    "echo ' '"
    'echo " "'
    "echo ' \""
    "echo build.h '|' grep b"
    "echo build.h | grep b"
    "echo -n-n-n-n-n"
    "echo '\"'"
    "echo '\""
    "echo -n -n -n bs"
    "echo bs -n -n"
    "echo -nnn something"
    "rm -r-f bs"
    "rm ------rf bs"
    "rm bs -rf"
    )

# create a variable with the name of the executable
exe="./v1"

#set -e

# specify name of Makefile
# make re -f Makefile
make re --silent

for arg in "${args[@]}"; do
    echo -e "$red $exe $arg: $none"
    #leaks -atExit -- ./"$exe" "$arg"
    ./"$exe" "$arg"
done

rm -rf v1.dSYM v1 outfile firstfile lastfile outone.txt outtwo.txt outthree.txt file
make fclean -s
