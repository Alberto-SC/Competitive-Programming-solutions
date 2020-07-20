#!/usr/bin/env perl

use strict;
use warnings;

my $n = shift // 40;
print STDERR "n = $n\n";

my $s = '';
for my $i (1 .. $n) {
    $s .= int rand 3;
}
print "$s\n";
