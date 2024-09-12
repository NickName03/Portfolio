while true; do
    a=$(date +%H:%M);   
    if [ $a == $@ ]; then
        clear;
        break;
    fi;
done;
