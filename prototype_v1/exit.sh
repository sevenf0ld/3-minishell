#!/bin/bash

blue='\033[0;44m'
none='\033[m'

# create an array of exit arguments
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
    )

reset

for arg in "${args[@]}"; do
	(exit "$arg")
	echo -e "exit $arg: $blue $? $none"
done

(exit 2 a)
echo -e "exit 2 a: $blue $? $none"
(exit b 3)
echo -e "exit b 3: $blue $? $none"
(exit 4 4)
echo -e "exit 4 4: $blue $? $none"
(exit c c)
echo -e "exit c b: $blue $? $none"
(exit 3 4 a)
echo -e "exit 3 4 a: $blue $? $none"
