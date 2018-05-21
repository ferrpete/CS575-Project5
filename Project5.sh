#!/bin/bash

# number of threads:
for t in 1 2 4 6 8
do
	echo NUMT = $t
	# number of subdivisions:
	for s in 1000 4000 16000 64000 256000 1024000 4096000 16384000 65536000
	# for s in 4
	do
		echo NUMS = $s
		icpc -DNUMS=$s -DNUMT=$t Project5.cpp -o Project5 -O3 -lm -qopenmp -align -qopt-report=3 -qopt-report-phase=vec
		./Project5
	done
done
