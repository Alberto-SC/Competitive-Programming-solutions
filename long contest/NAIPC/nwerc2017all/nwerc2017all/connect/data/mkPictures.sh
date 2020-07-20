#!/bin/sh

# Compile Paul's submissions here
g++ -std=gnu++14 -o paul ../submissions/accepted/paul.cpp;

# And use it for all input files
for f in */*.in; do
    echo $f;
    ./paul -draw < $f | ./visualiser-rgl.py $f ${f%.in}.png;
done
