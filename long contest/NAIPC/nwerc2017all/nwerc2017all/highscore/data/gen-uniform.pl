#!/usr/bin/env perl

use strict;
use warnings;

my $n = 7;
print "$n\n";

for my $i (1 .. $n) {
    my ($a, $b, $c, $d) = map {int rand 200000000} (1 .. 4);
    print "$a $b $c $d\n";
}
