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
    "ls -l > > > outfile firstfile"
    "ls -l >> > file lastfile"
    "ls -l > > file lastfile"
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
    "ls -i | < main.c cat -e"
    "ls -i | < main.c"
    "cmd1 << LIMITER | cmd2 >> file"
    "echo -n -n -n"
    "echo -n"
    "echo build.h | grep b"
    "echo -n-n-n-n-n"
    "echo -n -n -n bs"
    "echo bs -n -n"
    "echo -nnn something"
    #"echo 'sdf\n'"
    #"echo \"'sdf\n\""
    "rm -r-f bs"
    "rm ------rf bs"
    "rm bs -rf"
    "< main.c grep -n main | wc -l"
    "grep -n main main.c | wc -l"
    "< lexer.c cat | wc"
    "< lexer.c | wc"
    "cat << EOF > outone.txt"
    "cat << LIM"
    # 3 in_re checks
    "< nothing cat | wc | wc"
    "wc main.c | < nothing cat | wc"
    "wc main.c | cat -e main.c | < nothing cat"
    "< main.c | wc | wc"
    "< main.c cat | < main.c | wc"
    "< main.c cat | wc | < main.c"
    "< nothing | wc | wc"
    "< nothing cat | < nothing | wc"
    "< nothing ca"
    # EXPANSION
    "echo \$SHELL"
    "echo '\$SHELL'"
    'echo "$SHELL"'
    'echo "$SHELL" $SHELL'
    "echo "\$SHELL" '\$SHELL'"
    'echo "$SHELL" "$SHELL"'
    "echo '\$SHELL' \"\$SHELL\""
    "echo '\$SHELL' \"\$SHELL\" \"\$SHELL\""
    "echo \"\$SHELL\" \"\$SHELL\" '\$SHELL'"
    "echo \"\$SHELL\" \"\$SHELL\" '\$SHELL' \"\$SHELL\""
    "echo '\$?'"
    'echo "\$?"'
    "echo \$?"
    "echo '$example'"
    "echo '\$example'"
    'echo "$example"'
    "echo \$example"
    "echo \$HOME"
    'echo $USER'
    "echo \$MADi\$HATTER"
    "echo \$"
    "echo '\$'"
    'echo "\$"'
    "echo '\$SHELL' '\$SHELL'"
    'echo "$SHELL$SHELL" "$HOME"'
    'echo abc"$HOME"'
    'echo abc"$HOME"hh'
    'echo abc"$HOME                      "hh'
    # BONUS
#"echo '\"\$PATH\"'"
    # heap buffer overflow in new_split if there is no space
#"echo '\"\$PATH\" \"\$USER\"'"
#"echo \"'\$PATH'\""
    # heap buffer overflow in new_split if there is no space
#"echo \"'\$PATH' '\$USER'\""
#"echo \"'\$PATH' '\$USER'\" \"'\$PATH' '\$USER'\""
    # QUOTE NO EXPANSION
    "echo \"'sdf\""
    "echo 'asd'"
    "echo '\"asd'"
    "echo '\"asd'"
    "echo '\"'"
    "echo \"'''\""
    "echo '\"\"'"
    "echo '  \"                   '"
    "echo '\""
    'echo "cat main.c | wc"'
    "echo \"cat lol.c | cat > lol.c\""
    "echo 'cat lol.c | cat > lol.c'"
    "echo \"cat lol.c | cat >\""
    'echo " " " " " " | cat -e'
    'echo " " " " " "'
    'echo " " " " "'
    "echo ' ' ' ' ' ' | cat -e"
    "echo ''"
    "echo ' '"
    'echo " "'
    "echo ' \""
    "echo build.h '|' grep b"
    "echo build.h '>' outfile"
    "echo '     '"
    'echo "     "'
    # ERROR HANDLING
    "cat *.c || | grep -wn token"
    "cat *.c ||| grep -wn token"
    "cat *.c || || grep -wn token"
    "cat *.c |||| grep -wn token"
    "cat *.c | grep | -wn token"
    )

# create a variable with the name of the executable
exe="./v1"

set -e

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
