#!/bin/bash
echo -e "1 - создать файл и скопировать его в другую папку\n2 - создать файл и переместить в другую папку\n3 - создать каталог"
read c
if [ $c -eq 3 ]; then
	echo Введите название директории; read p;
	mkdir $p;
	find . -name $p;
	exit;
fi
if [[ $c -gt 3 || $c -lt 1 ]]; then
	echo Нет таких действий;
	exit;
fi	
echo Введите название файла; read name
echo Введите путь; read p
touch $name
if [ $c -eq 1 ]; then
	cp $name $p;
fi
if [ $c -eq 2 ]; then
	mv $name $p;
fi
find $p -name $name
