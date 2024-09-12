#!/bin/bash
touch 9.txt
echo -n "Введите первое число: "; read a
echo -n "Введите второе число: "; read b
echo -n "Введите третье число: "; read c
if [ $a -gt $b ]; then
        if [ $a -gt $c ]; then
                echo $a > 9.txt
        else
                echo $c > 9.txt
        fi
elif [ $b -gt $c ]; then
        echo $b > 9.txt
else
        echo $c > 9.txt
fi
echo -n "Максимальное из трех чисел: "
cat 9.txt
