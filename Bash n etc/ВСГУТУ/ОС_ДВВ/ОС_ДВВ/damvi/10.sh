echo Введите имя файла: ; read name;
ls > ~/list.txt
list=~/list.txt
while true; do
    if grep -w "$name" "$list"; then
        echo Найдено;
        break;
    fi;
done;
