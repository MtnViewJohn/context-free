#!/bin/sh

mkdir output
for file in input/tests/*.cfdg input/*.cfdg
do 
    ./cfdg -qP "$file" output/test.png
    if [ $? -eq 0 ]
    then
        echo "$file   pass"
    else
        echo "$file          FAIL: $?"
        break
    fi
done
./cfdg -a150 -s640x480 --quicktime -vffgh input/mtree.cfdg output/mtree.mpeg

