echo Введите имя файла: ; read name;
list=file7.txt
while true; do
    if grep -w "$name" "$list"; then
        echo found;
        break;
    fi;
done;
