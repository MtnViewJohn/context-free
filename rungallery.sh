#!/bin/bash

if [[ $# == 0 ]]; then
	echo "usage: rungallery.sh list_of_batches";
	echo "  Where a batch is either a gallery id or a range id-id" 
	echo "  Failure code 1 means that id is not in the gallery. The remaining codes are from cfdg."
	exit 0;
fi

[ -d output ] || mkdir output

while [[ $# > 0 ]]; do
	if [[ $1 =~ ([0-9]+)-([0-9]+) ]]; then
		echo "From ${BASH_REMATCH[1]} to ${BASH_REMATCH[2]}"
		for (( id = ${BASH_REMATCH[1]}; id <= ${BASH_REMATCH[2]}; ++id )); do
			echo -n "$id";
			curl -fGLs "http://www.contextfreeart.org/gallery/data.php?id=$id&type=cfdg" | ./cfdg -qP -m 999999 - output/test.png
			if [[ $? == 0 ]]; then
				echo '   pass';
			else
				echo "          FAIL:$?";
			fi
		done
	else
		echo -n "$1";
		curl -fGLs "http://www.contextfreeart.org/gallery/data.php?id=$1&type=cfdg" | ./cfdg -qP -m 999999 - output/test.png
		if [[ $? == 0 ]]; then
			echo '   pass';
		else
			echo "          FAIL:$?";
		fi
	fi;
	shift;
done
