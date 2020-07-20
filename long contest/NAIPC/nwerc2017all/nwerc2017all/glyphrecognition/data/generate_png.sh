#!/bin/bash

ghc visualize.hs

for input in `find . -name *.in`; do
	image=${input%.in}.png
	if [ ! -e $image ]; then
		./visualize $input -o tmp.svg
		inkscape tmp.svg --export-background=white --export-png=$image
		rm tmp.svg
	fi
done

rm visualize visualize.o visualize.hi
