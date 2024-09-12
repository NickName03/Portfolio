while true; do
    
    CURRTIME=$(date +%H:%M);
    
    if [ $CURRTIME == $@ ]; then
        clear;
        break; # ?
    fi;
 
done;
