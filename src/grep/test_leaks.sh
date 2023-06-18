#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_command=(
    "./s21_grep"
    )
sys_command=(
    "grep"
    )

tests=(
"FLAGS Linus test_1_grep.txt"
"FLAGS Linus test_2_grep.txt"
"FLAGS Linus no_file.txt"
)
flags=(
    "e"
    "i"
    "v"
    "c"
    "l"
    "n"
    "h"
    "s"
    "f"
    "o"
)
manual=(
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

run_test_manual() {
    echo
    param=$(echo $@ | sed "s/FLAGS/$var/")
    echo $param
    # echo "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q --log-file="${s21_command[@]}".log ./"${s21_command[@]}" $param > /dev/null"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q --log-file="${s21_command[@]}".log ./"${s21_command[@]}" $param > /dev/null
    leak=$(grep -ic -A10000 "LEAK SUMMARY:" "${s21_command[@]}".log || true)
    # echo "Leak = $leak"
    leak2=$(grep -ic -A10000 "ERROR SUMMARY: [^0]" "${s21_command[@]}".log || true)
    # echo "Error (leak2) = $leak2"
    let "COUNTER++"
    if [ "$leak" -eq "0" ] && [ "$leak2" -eq "0" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${s21_command[@]}".log "${sys_command[@]}".log
}

run_test_parametrs() {
    echo
    param=$(echo $@ | sed "s/FLAGS/$var/")
    echo $param
    # echo "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q --log-file="${s21_command[@]}".log ./"${s21_command[@]}" $param > /dev/null"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q --log-file="${s21_command[@]}".log ./"${s21_command[@]}" $param > /dev/null
    leak=$(grep -ic -A10000 "LEAK SUMMARY:" "${s21_command[@]}".log || true)
    # echo "Leak = $leak"
    leak2=$(grep -ic -A10000 "ERROR SUMMARY: [^0]" "${s21_command[@]}".log || true)
    # echo "Error (leak2) = $leak2"
    let "COUNTER++"
    if [ "$leak" -eq "0" ] && [ "$leak2" -eq "0" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${s21_command[@]}".log "${sys_command[@]}".log
}

echo "#######################"
echo "MANUAL TESTS"
echo "#######################"
printf "\n"
for i in "${manual[@]}"
do
    var="-"
    run_test_manual $i
done
printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        run_test_parametrs $i
    done
done

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"