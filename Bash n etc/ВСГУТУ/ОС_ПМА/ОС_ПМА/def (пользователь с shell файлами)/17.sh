#!/bin/bash
echo -n "Введите число "; read n
res=1
while true; do
	if [ $n -gt 0 ]; then
		res=$(($res * $n));
		n=$(($n - 1))
	else
		break;
	fi
done
echo "Факториал равен: $res"
