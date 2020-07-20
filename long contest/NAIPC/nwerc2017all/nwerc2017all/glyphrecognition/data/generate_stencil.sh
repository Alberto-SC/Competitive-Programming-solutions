#!/bin/bash

name=(_ _ _ triangle square pentagon hexagon heptagon octagon)
size=(small medium large)

g++ -std=c++11 stencil.cpp -o stencil

for k in {3..8}; do
	for n in {0..2}; do
		r=`echo "10 * (100^$n)" | bc`
		t=`echo "40 + ($k-3)*3 + $n" | bc`
		echo $t-${name[$k]}-${size[$n]}.in
		echo $k $r | ./stencil > $t-${name[$k]}-${size[$n]}.in
	done
done

rm stencil
