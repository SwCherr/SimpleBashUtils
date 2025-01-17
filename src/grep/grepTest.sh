#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"Linus test_1_grep.txt test_2_grep.txt"
"-e Linus test_1_grep.txt"
"-i LINUS test_1_grep.txt"
"-v Linus test_1_grep.txt"
"-c Linus test_1_grep.txt"
"-l Linus test_1_grep.txt test_2_grep.txt patterns_grep.txt"
"-n Linus test_1_grep.txt"

"-o Linus test_1_grep.txt"
"-h Linus test_1_grep.txt test_2_grep.txt"
"-s Linus find_me.txt"
"-f patterns_grep.txt test_2_grep.txt"

"-cv Linus test_1_grep.txt"
"-iv Linus test_1_grep.txt"
"-lv Linus test_1_grep.txt test_2_grep.txt patterns_grep.txt"
"-ho Linus test_1_grep.txt test_2_grep.txt"
"-nf patterns_grep.txt test_2_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "$FAIL/ $SUCCESS/ $COUNTER  success - grep $t"
    else
      (( FAIL++ ))
      echo "$FAIL/ $SUCCESS/ $COUNTER  fail - grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

for i in "${tests[@]}"
do
    var="-"
    testing $i
done


echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"