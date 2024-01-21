#!/bin/bash

# # Set a sample variable
# name="John"


# Test variable expansion with echo
echo 'Hello, $USER!'
echo '$USER'
./minishell << "eof"
eof
echo "END"