!/bin/bash
path1=$1
path2=$2
path3=$3

s1="MemoryType;BlockSize;ElementType;BufferSize;LaunchNum;Timer;" s2="WriteTime;AverageWriteTime;WriteBandWIdth;AbsError(write);RelError(write);" s3="ReadTime;AverageReadTime;ReadBandWidth;AbsError(read);RelError(read)"
echo ${s1}${s2}${s3} > file.csv
g++ *.cpp -o memory_test
size=4
launchNum=5

for ((idx=1;idx<21;idx++))do
    echo ./memory_test -m RAM -b ${size}Mb -l 10 -p
    echo $(./memory_test -m RAM -b ${size}Mb -l 10 )
    size=$((size+4))
done
size=4
for ((idx=1;idx<21;idx++))
do
    echo ./memory_test -m HDD -b ${size}Mb -l 10 -p ${path1}
    echo $(./memory_test -m HDD -b ${size}Mb -l 10 -p ${path1})
    size=$((size+4))
done
size=4
for ((idx=1;idx<21;idx++)) do
    echo ./memory_test -m SSD -b ${size}Mb -l 10 -p ${path2}
    echo $(./memory_test -m SSD -b ${size}Mb -l 10 -p ${path2})
    size=$((size+4)) 
done
size=4
for ((idx=1;idx<21;idx++)) do
    echo ./memory_test -m flash -b ${size}Mb -l 10 -p ${path3}
    echo $(./memory_test -m flash -b ${size}Mb -l 10 -p ${path3}) 
    size=$((size+4)) 
done

for ((idx=1;idx<100;idx++)) do
    echo ./memory_test -m RAM -b 10Mb -l ${idx} 
    echo $(./memory_test -m RAM -b 10Mb -l ${idx} ) 
done