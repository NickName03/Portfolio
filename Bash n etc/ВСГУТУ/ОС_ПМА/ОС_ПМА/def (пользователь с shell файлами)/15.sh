#!/bin/bash
touch max.txt
echo Введите первое число; read f
echo Введите второе число; read s
echo Введите третье число; read t
if [ $f -gt $s ]; then
	if [ $f -gt $t ]; then
		echo $f > max.txt
	else
		echo $t > max.txt
	fi
elif [ $s -gt $t ]; then
	echo $s > max.txt
else
	echo $t > max.txt
fi
echo Максимальное из трех чисел
cat max.txt
