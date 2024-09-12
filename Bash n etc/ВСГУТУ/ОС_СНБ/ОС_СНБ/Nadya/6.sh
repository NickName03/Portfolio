echo "Введите имя файла: "
read name;
list=4.txt
while true; do
    if grep -w "$name" "$list"; then
        echo "Найдено!";
        break;
    fi;
done;
