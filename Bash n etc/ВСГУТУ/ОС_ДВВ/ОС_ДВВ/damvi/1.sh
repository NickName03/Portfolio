#!/bin/bash 
i=1 
for param in "$@" ; 
do 
	echo "$param $i"
	i=$(($i+$1))
done
