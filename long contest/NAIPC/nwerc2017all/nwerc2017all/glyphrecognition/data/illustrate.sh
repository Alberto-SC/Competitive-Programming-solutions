#!/bin/bash

name=(alphabet 1-without 1-triangle 1-hexagon)

ghc illustrate.hs

for k in {0..3}; do
	./illustrate sample/1.in $k -o tmp.svg
	inkscape tmp.svg --export-background=white --export-pdf=../problem_statement/${name[$k]}.pdf
	rm tmp.svg
done

rm illustrate illustrate.o illustrate.hi
