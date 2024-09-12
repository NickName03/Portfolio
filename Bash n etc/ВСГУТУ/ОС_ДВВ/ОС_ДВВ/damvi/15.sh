#!/bin/bash
touch bol
echo -n "Введите первое число: "; read f
echo -n "Введите второе число: "; read s
echo -n "Введите третье число: "; read t
if [ $f -gt $s ]; then
	if [ $f -gt $t ]; then
		echo $f > bol
	else
		echo $t > bol
	fi
elif [ $s -gt $t ]; then
	echo $s > bol
else
	echo $t > bol
fi
echo -n "Максимальное из трех чисел: "
cat bol

