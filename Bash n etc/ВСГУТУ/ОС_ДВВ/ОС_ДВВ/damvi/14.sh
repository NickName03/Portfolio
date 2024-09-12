#!/bin/bash
echo -e "1 - создать файл и скопировать его в другую папку\n2 - создать файл и переместить в другую папку\n3 - создать каталог"
read a
if [ $a -eq 3 ]; then
	echo -n "Введите название директории: "; read p;
	mkdir -p $p;
	ls -l $p
	exit;
fi
echo -n "Введите название файла: "; read name
echo -n "Введите путь: "; read p
touch $name
if [ $a -eq 1 ]; then
	cp $name $p;
fi
if [ $a -eq 2 ]; then
	mv $name $p;
fi
ls $p | grep $name

