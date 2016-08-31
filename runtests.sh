#!/bin/sh

mkdir output
for file in input/tests/*.cfdg input/*.cfdg ; do if ./cfdg -Pq "$file" output/test.png ; then echo "$file   pass" ; : ; else echo "$file          FAIL" ; break; fi ; done
