#!/bin/bash
name1=Вика; name2=Маша;name3=Марина 
echo -n "Твоё имя: "; read name
case $name in 
$name1)
        echo "Привет, $name!";
	exit
;;
$name2)
        echo "Привет, $name!";
	exit
;;
$name3)
	echo "Привет, $name!";
	exit
;;
esac
echo "Ты ни $name1, ни $name2, ни $name3. Но всё равно привет, $name"
