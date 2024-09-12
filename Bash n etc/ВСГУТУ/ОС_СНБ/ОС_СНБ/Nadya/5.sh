while true; do

    var=$(date +%H:%M);

    if [ $var == $@ ]; then
        clear;
        break;
    fi;

done;
