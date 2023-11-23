#!/ bin / bash
SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""
TEST_FILE=(
    "tests/test1.txt"
    "tests/test2.txt"
)

s21_grep="./s21_grep"
grep="grep"

flags=(
    "i"
    "v"
    "c"
    "l"
    "n"
    "h"
    "s"
)

patterns=(
    "main"
    "int"
    "1"
)

flags_e=(
    "-e main -e int -e 1"
)

flags_f=(
    "f"
)

printf "\n"
echo "#######################"
echo "MANUAL TEST FOR -e"
echo "#######################"
printf "\n"

for var1 in "${flags_e[@]}"
do
    for var2 in "${TEST_FILE[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"

        $s21_grep $TEST1 > test_result_s21_grep.txt
        $grep $TEST1 > test_result_grep.txt
        DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
        if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm test_result_s21_grep.txt test_result_grep.txt
    done
done

printf "\n"
echo "#######################"
echo "MANUAL TEST FOR -f"
echo "#######################"
printf "\n"

for var1 in "${flags_f[@]}"
do
    for var2 in "${TEST_FILE[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"

        $s21_grep $TEST1 > test_result_s21_grep.txt
        $grep $TEST1 > test_result_grep.txt
        DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
        if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm test_result_s21_grep.txt test_result_grep.txt
    done
done



printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "0 FLAG - 1 PATTERN - 1 FILE"
echo "======================="
printf "\n"

for var1 in "${patterns[@]}"
do
    for var2 in "${TEST_FILE[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"

        $s21_grep $TEST1 > test_result_s21_grep.txt
        $grep $TEST1 > test_result_grep.txt
        DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
        if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm test_result_s21_grep.txt test_result_grep.txt
    done
done

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 FLAG - 1 PATTERN - 1 FILE"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${patterns[@]}"
    do 
        for var3 in "${TEST_FILE[@]}"
        do
            (( COUNTER++ ))
            TEST1="-$var1 $var2 $var3"

            $s21_grep $TEST1 > test_result_s21_grep.txt
            $grep $TEST1 > test_result_grep.txt
            DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
            if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
                then
                    (( SUCCESS++ ))
                    echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
                else
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                    echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
            fi
            rm test_result_s21_grep.txt test_result_grep.txt
        done
    done
done


printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "2 FLAG - 1 PATTERN - 1 FILE"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then 
            for var3 in "${patterns[@]}"
            do 
                for var4 in "${TEST_FILE[@]}"
                do
                    (( COUNTER++ ))
                    TEST1="-$var1$var2 $var3 $var4"

                    $s21_grep $TEST1 > test_result_s21_grep.txt
                    $grep $TEST1 > test_result_grep.txt
                    DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
                    if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
                        then
                            (( SUCCESS++ ))
                            echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
                        else
                            echo "$TEST1" >> log.txt
                            (( FAIL++ ))
                            echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
                    fi
                    rm test_result_s21_grep.txt test_result_grep.txt
                done
            done
        fi
    done
done


printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "2 FLAG - 1 PATTERN - 1 FILE"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then 
                for var4 in "${patterns[@]}"
                do 
                    for var5 in "${TEST_FILE[@]}"
                    do
                        (( COUNTER++ ))
                        TEST1="-$var1$var2$var3 $var4 $var5"

                        $s21_grep $TEST1 > test_result_s21_grep.txt
                        $grep $TEST1 > test_result_grep.txt
                        DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
                        if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
                            then
                                (( SUCCESS++ ))
                                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
                            else
                                echo "$TEST1" >> log.txt
                                (( FAIL++ ))
                                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
                        fi
                            rm test_result_s21_grep.txt test_result_grep.txt
                    done
                done
            fi
        done
    done   
done


printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 FLAG - 1 PATTERN - 2 FILE"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${patterns[@]}"
    do 
        for var3 in "${TEST_FILE[@]}"
        do
            for var4 in "${TEST_FILE[@]}"
            do        
                if [ $var3 != $var4 ]
                then     
                    (( COUNTER++ ))
                    TEST1="-$var1 $var2 $var3 $var4"

                    $s21_grep $TEST1 > test_result_s21_grep.txt
                    $grep $TEST1 > test_result_grep.txt
                    DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
                    if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
                        then
                            (( SUCCESS++ ))
                            echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
                        else
                            echo "$TEST1" >> log.txt
                            (( FAIL++ ))
                            echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
                    fi
                    rm test_result_s21_grep.txt test_result_grep.txt
                fi
            done
        done
    done
done

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"
##############################