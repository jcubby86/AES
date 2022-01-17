#!/bin/bash

function usage (){
    printf "usage:\t./test.sh program {128|192|256|all} [-d]\n"
    printf "\tuse the -d flag to compare against expected files from FIPS spec\n"
    exit 0
}

function run_test (){
    INPUT="input.txt"
    KEY="key$TESTNUM.txt"
    ACTUAL="actual${TESTNUM}.txt"
    OUTPUT="expected${TESTNUM}.txt"
    DIFF="test${TESTNUM}issues.txt"

    printf "\nTest AES${TESTNUM}"
    printf "\nPLAINTEXT:\t\t"
    cat input.txt
    printf "\nKEY:      \t\t"
    cat $KEY
    printf "\n"
    (./main $INPUT $TESTNUM $KEY $VERBOSE) >$ACTUAL

    if [ "$VERBOSE" = "-d" ]; then
        (diff $OUTPUT $ACTUAL) >$DIFF
        if [ -s $DIFF ]; then
            printf "Test AES${TESTNUM} issues:\n"
            cat $DIFF
        else
            printf "\nTest AES${TESTNUM} passed!"
            rm $DIFF
            rm $ACTUAL
        fi
    else
        cat $ACTUAL
        rm $ACTUAL
    fi

    printf "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
}

if [ $# -lt 1 ]; then
    usage
fi

VERBOSE=""
if [ $# -eq 2 ]; then
    if [ $2 = "-d" ]; then
        VERBOSE="-d";
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


