#!/bin/bash

for file in input/tests/*.cfdg ; do echo -n "$file "; if ./cfdg -Pq "$file" output/test.png ; then echo '   pass' ; : ; else echo '          FAIL' ; break; fi ; done
