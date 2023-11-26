#!/bin/bash
date +'%m/%d/%Y';
echo "$USER;"
echo "$HOSTNAME;"
echo "CPU:"
system_profiler SPSoftwareDataType SPHardwareDataType | grep "Processor Name";
system_profiler SPSoftwareDataType SPHardwareDataType | grep "Processor Speed";
system_profiler SPSoftwareDataType SPHardwareDataType | grep "Total Number of Cores";
echo "      Architecture: $(lscpu | grep "Architecture" | awk '{print $2}')";

echo "RAM:"
system_profiler SPSoftwareDataType SPHardwareDataType | grep -m2 "Memory: " | tail -n1;
echo "      Used: $(top -l 1 -s 0 | grep PhysMem | awk '{print $2}')";
echo "HDD:"
echo "      $(system_profiler SPSoftwareDataType SPNVMeDataType | grep -m1 "Capacity: " | xargs)";
echo "      Available: $(df -H | xargs | awk '{print $14}')";

echo "      SWAP total: $(sysctl vm.swapusage | awk '{print $4}')";
echo "      SWAP used: $(sysctl vm.swapusage | awk '{print $7}')";
echo "      SWAP free: $(sysctl vm.swapusage | awk '{print $10}')";

echo "      Mounted on / : $(df -h | grep "/$" | awk '{print $1}')"
echo "ICONFIG:";
counter=0

interfaces=$(ifconfig -l)
for interface in $interfaces
do
    counter=$(( counter + 1))
done
echo "      Amount of network interfaces: $counter"
counter=1
printf "#\t\tInterface\tSpeed\t\t\tMacaddress\tAddress\n"
for interface in $interfaces
do
    macaddress=$(ifconfig "$interface" | grep "ether" | awk '{print $2}')
    ipaddress=$(ifconfig "$interface" | grep "inet" | awk '{print $2}')
    speed=$(ifconfig "$interface" | grep "mtu" | awk '{print $4}')
    printf "%2d\t\t%7s\t\t%5s\t\t%20s\t%s\t\n" "$(echo $counter)" "$(echo $interface)" "$(echo $speed)" "$(echo $macaddress)" "$(echo $ipaddress)" ;
    counter=$(( counter + 1))
done 

