ls ~ > file6.txt
cat file6.txt
var=$(($(ls -l ~ | wc -l) - 1))
echo $var
