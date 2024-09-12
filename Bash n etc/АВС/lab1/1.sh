#!/bin/bash
echo "DoD 3"
echo "1. OS"
echo -n "Os name: "
uname  -o
echo -n "Os version: "
uname -r
echo -n "The Kernel name: "
uname -s
echo -n "The Kernel arch: "
uname -p
echo "2. CPU"
lscpu  | grep -i "model name"
cat /proc/cpuinfo | grep "cpu MHz"
lscpu  | grep -i "Core(s) per socket"
lscpu  | grep -i "L1d"
lscpu  | grep -i "L1i"
lscpu  | grep -i "L2"
lscpu  | grep -i "L3"
echo "3. RAM"
free -h -t
echo "DoD 4"
echo "1. Network interfaces:"
ls /sys/class/net/ | while read interface; do
    if [$interface != "lo"]; then
    	echo "Interface: $interface"
    	echo "IP: $(ip addr show $interface | grep "inet " | awk '{print $2}')"
    	echo "MAC: $(cat /sys/class/net/$interface/address)"  
    	echo "Actual connection speed: $(cat /sys/class/net/$interface/speed) Mb/s"
   fi
done

echo "2. System partitions"
df -h | grep ":"




