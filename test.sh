#!/bin/bash

function usage (){
    printf "usage:\t./test.sh program {128|192|256|all} [-v]\n"
    printf "\tuse the -v flag for verbose output\n"
    exit 0
}

function run_test (){
    INPUT="input.txt"
    KEY="key$TESTNUM.txt"

    printf "\nTest AES${TESTNUM}\nKey: "
    cat $KEY
    printf "\n"
    (./main $INPUT $TESTNUM $KEY $VERBOSE)
    printf "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
}

if [ $# -lt 1 ]; then
    usage
fi

VERBOSE=""
if [ $# -eq 2 ]; then
    if [ $2 = "-v" ]; then
        VERBOSE="-v";
    fi
fi


if [ $1 = "all" ]; then
    make clean
    make
    for TESTNUM in 128 192 256; do
        run_test
    done
else
    TESTNUM=$1
    if [ $TESTNUM -eq 128 ] || [ $TESTNUM -eq 192 ] || [ $TESTNUM -eq 126 ]; then 
        make clean
        make
        run_test
    else
        usage
    fi
fi


