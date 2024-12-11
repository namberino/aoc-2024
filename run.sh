#!/bin/bash

if [[ "$#" -eq 1 ]] && ([[ "$1" = "-h" ]] || [[ "$1" = "--help" ]]); then
    echo "Usage: $0 [day-n] [run | test]"
    exit 0
fi

# missing argument
if [[ "$#" -ne 2 ]]; then
    echo "Usage: $0 [day-n] [run | test]"
    exit 1
fi

# validate run argument (only 'run' or 'test' is allowed)
if [[ ! "$2" = "run" ]] && [[ ! "$2" = "test" ]]; then
    echo "Error: Invalid run argument."
    exit 1
fi

# check if argument is a valid directory
valid_dirs=$(ls -d day-*)
if [[ ! "$valid_dirs" =~ "$1" ]]; then
    echo "Error: '$1' is not found. Please use a valid directory name."
    exit 1
fi

# run the program
cd $1
make $2
cd ..
