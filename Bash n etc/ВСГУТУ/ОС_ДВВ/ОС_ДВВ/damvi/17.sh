#!/bin/bash
echo -n "Введите число: "; read n
f=1
while true; do
	if [ $n -gt 0 ]; then
		f=$(($f * $n));
		n=$(($n - 1))
	else
		break;
	fi
done
echo "Факториал равен: $f"
