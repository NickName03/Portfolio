#!/bin/bash
echo -n "Введите число "; read n
fact=1
while true; do
        if [ $n -gt 0 ]; then
                fact=$(($fact * $n));
                n=$(($n - 1))
        else
                break;
        fi
done
echo "Факториал равен: $fact"
