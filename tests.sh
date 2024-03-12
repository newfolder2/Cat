#!/bin/bash

SUCCESS=0
FAIL=0
DIFFERENCE=""
NC='\033[0m'
TC_YELLOW='\033[33m'
TC_GREEN='\033[92m'
BG_GREEN='\033[42m'

for var in -b -e -n -s -t
    do
        ./cat $var deploy.sh > cat.txt
        cat $var deploy.sh > cat2.txt
        DIFFERENCE="$(diff -s cat.txt cat2.txt)"
        if [ "$DIFFERENCE" = "Files cat.txt and cat2.txt are identical" ]
        then
            SUCCESS=$((SUCCESS + 1))
        else
            FAIL=$((FAIL + 1))
        fi
        rm cat.txt cat2.txt
    done

echo -e "${BG_GREEN}- - - CAT - - -$NC"
echo -e "${TC_YELLOW}Number of successful tests:$NC $SUCCESS"
echo -e "${TC_YELLOW}Number of failed tests:$NC $FAIL "

if [ $FAIL -eq 0 ]
    then
        echo -e "${TC_GREEN}Tests passed successfully$NC"
        exit 0
    else
        echo "Tests failed"
        exit 1
    fi
