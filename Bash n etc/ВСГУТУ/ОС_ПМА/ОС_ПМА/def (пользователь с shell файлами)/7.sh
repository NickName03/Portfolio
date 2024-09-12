cd $@
ls > $OLDPWD/file7.txt
cd $OLDPWD
cat file7.txt
