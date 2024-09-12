ls ~ > c.txt
cat c.txt
a=$(($(ls -l ~ | wc -l) - 1))
echo $a
