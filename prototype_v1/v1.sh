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
    'echo " " " " " " | cat -e'
    'echo " " " " " "'
    'echo " " " " "'
    "echo ' ' ' ' ' ' | cat -e"
    "echo '$example'"
    "echo '\$example'"
    'echo "$example"'
    "echo \$example"
    "echo \$HOME"
    'echo $USER'
    "echo \$MADi\$HATTER"
    'echo $HOME$USER'
    'echo $HOME$USER $HOME$USER'
    'echo $HOME$USERi'
    'echo i$HOME$USERi'
    'echo $HOMEi'
    'echo i$HOMEi'
    'echo i$HOME'
    'echo something something $HOME random $USER $PATHi$SHELL$LANG'
    "echo '\"\$PATH\"'"
    # heap buffer overflow in new_split if there is no space
    "echo '\"\$PATH\" \"\$USER\"'"
    "echo \"'\$PATH'\""
    # heap buffer overflow in new_split if there is no space
    "echo \"'\$PATH' '\$USER'\""
    "echo \"'\$PATH' '\$USER'\" \"'\$PATH' '\$USER'\""
    "echo \$"
    "echo '\$'"
    'echo "\$"'
    "echo ''"
    "echo ' '"
    'echo " "'
    "echo ' \""
    "echo build.h '|' grep b"
    "echo build.h | grep b"
    "echo -n-n-n-n-n"
    "echo '\"'"
    "echo '\$SHELL' '\$SHELL'"
    'echo "$SHELL$SHELL" "$HOME"'
    "echo \"'''\""
    "echo '\"\"'"
    "echo '  \"                   '"
    "echo '\""
    "echo -n -n -n bs"
    "echo bs -n -n"
    "echo -nnn something"
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
    'echo "cat main.c | wc"'
    "echo '\$?'"
    'echo "\$?"'
    "echo \$?"
    "echo \"cat lol.c | cat > lol.c\""
    "echo 'cat lol.c | cat > lol.c'"
    "echo \"cat lol.c | cat >\""
    #"echo 'sdf\n'"
    #"echo \"'sdf\n\""
    "echo \"'sdf\""
    "echo 'asd'"
    "echo '\"asd'"
    "echo '\"asd'"
    "rm -r-f bs"
    "rm ------rf bs"
    "rm bs -rf"
    "< main.c grep -n main | wc -l"
    "grep -n main main.c | wc -l"
    "< lexer.c cat | wc"
    "< lexer.c | wc"
    "cat << EOF > outone.txt"
    "cat << LIM"
        "< nothing cat | wc | wc"
        "wc main.c | < nothing cat | wc"
        "wc main.c | cat -e main.c | < nothing cat"
        "< main.c | wc | wc"
        "< main.c cat | < main.c | wc"
        "< main.c cat | wc | < main.c"
        "< nothing | wc | wc"
        "< nothing cat | < nothing | wc"
        "< nothing ca"
    )
# 1/1 & 4/1
in_re=(
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
    'echo $HOME$USER'
    'echo $HOME$USER $HOME$USER'
    'echo $HOME$USERi'
    'echo i$HOME$USERi'
    'echo $HOMEi'
    'echo i$HOMEi'
    'echo i$HOME'
    'echo something something $HOME random $USER $PATHi$SHELL$LANG'
    "echo '\"\$PATH\"'"
    # heap buffer overflow in new_split if there is no space
    "echo '\"\$PATH\" \"\$USER\"'"
    "echo \"'\$PATH'\""
    # heap buffer overflow in new_split if there is no space
    "echo \"'\$PATH' '\$USER'\""
    "echo \"'\$PATH' '\$USER'\" \"'\$PATH' '\$USER'\""
    "echo \$"
    "echo '\$'"
    'echo "\$"'
    "echo '\$SHELL' '\$SHELL'"
    'echo "$SHELL$SHELL" "$HOME"'
    'echo abc"$HOME"'
        )

# create a variable with the name of the executable
exe="./v1"

#set -e

# specify name of Makefile
# make re -f Makefile
make re --silent

#for arg in "${args[@]}"; do
#    echo -e "$red $exe $arg: $none"
#    #leaks -atExit -- ./"$exe" "$arg"
#    ./"$exe" "$arg"
#done

for inre in "${in_re[@]}"; do
    echo -e "$red $exe $inre: $none"
    ./"$exe" "$inre"
done

rm -rf v1.dSYM v1 outfile firstfile lastfile outone.txt outtwo.txt outthree.txt file
make fclean -s
