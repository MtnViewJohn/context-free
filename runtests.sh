#!/bin/sh

mkdir output
for file in input/tests/*.cfdg input/*.cfdg
do 
    ./cfdg --jsonredacted "$file" - | cmp - "${file%.cfdg}.json"
    if [ $? -ne 0 ]
    then
        echo "$file          FAIL: $?"
        exit 1
    fi
    ./cfdg -qP "$file" output/test.png
    if [ $? -eq 0 ]
    then
        echo "$file   pass"
    else
        echo "$file          FAIL: $?"
        exit 2
    fi
done
./cfdg -a150 -s640x480 --quicktime -vffgh input/mtree.cfdg output/mtree.mov
if [ $? -ne 0 ]
then
    echo "$file          FAIL: $?"
    exit 3
fi

