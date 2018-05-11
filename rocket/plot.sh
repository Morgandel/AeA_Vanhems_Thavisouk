#!/bin/bash

>ratio_sort.dat

it=10
while [ $it -le 400 ]
do
	average=0
	for i in $(seq 1 10)
	do
		res=`./pareto -n $it`
		echo $res
		one_time=`echo $res | cut -d' ' -f2`
		average=`echo "$average + $one_time" | bc`
	done
	average=`echo "scale=7; $average / 10" | bc`
	echo "$it $average" >> ratio_sort.dat
	it=`echo "$it + 10" | bc`
done
