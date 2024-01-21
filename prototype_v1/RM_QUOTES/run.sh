#!/bin/bash

# [1] variables
EXECUTABLE="./a.out"
OPTIONS="-s --leak-check=full --track-origins=yes"
OP_EXTRA="--show-leak-kinds=all"
OUTPUT="_valgrind.txt"

# [2] functions
valgrind $OPTIONS $OP_EXTRA $EXECUTABLE 2> $OUTPUT
# valgrind $OPTIONS $OP_EXTRA $EXECUTABLE $OP_EXTRA 2> $OUTPUT