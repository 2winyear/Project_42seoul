#!/bin/bash
builtinspeed=0
oursspeed=0
check_output() {
    read -rep "" a
	if [[ $a == "y"$'\n' ]]
	then
        echo "OK"; exit 0;
	else
        echo "KO"; exit 1;
	fi

}
test_speed_ours(){
	logfile=`mktemp`
	timeout 3 bash -c "./yes | dd of=/dev/null bs=16M status=progress 2>$logfile"
	oursspeed=`awk '{print $1;}' $logfile`
	rm -f $logfile
}

test_speed_builtin(){
	logfile=`mktemp`
	timeout 3 bash -c "yes | dd of=/dev/null bs=16M status=progress 2>$logfile"
	builtinspeed=`awk '{print $1;}' $logfile`
	rm -f $logfile
}



#check_output
test_speed_builtin
test_speed_ours

if [ "$oursspeed" -gt "$builtinspeed" ]; then
	echo "OK"
else
	echo "KO"
fi
