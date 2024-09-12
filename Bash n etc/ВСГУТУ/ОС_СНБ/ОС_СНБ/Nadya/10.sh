#!/bin/bash
name1=Иван; name2=Егор;name3=Женя 
echo -n "Твоё имя: "; read name
case $name in 
$name1)
        echo "Hi, $name";
	exit
;;
$name2)
        echo "Hi, $name";
	exit
;;
$name3)
	echo "Hi, $name";
	exit
;;
esac
echo "Ты ни $name1, ни $name2, ни $name3. Но всё равно привет, $name"
