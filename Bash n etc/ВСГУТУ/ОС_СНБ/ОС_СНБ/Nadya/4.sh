cd $@
ls > $OLDPWD/4.txt
cd $OLDPWD
ls | grep 4.txt
cat 4.txt
