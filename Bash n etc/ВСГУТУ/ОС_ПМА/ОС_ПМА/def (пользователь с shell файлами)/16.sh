#!/bin/bash
echo -n Введите имя:  ; read name
cd /home
for dir in */ 
do
	dir=${dir%*/}
	if [ $name == $dir ]; then
		echo Привет, $name; exit
	fi
done
echo -n Ты ни: ; 
for dir in */ 
do
	dir=${dir%*/}
	echo -n "$dir, " 
done
echo -e но привет, $name!
