#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(shuffle);

my @p = shuffle (1 .. 16);
for my $i (1 .. 16) {
    print $p[$i-1];
    print($i % 4 == 0 ? "\n" : " ");
}
