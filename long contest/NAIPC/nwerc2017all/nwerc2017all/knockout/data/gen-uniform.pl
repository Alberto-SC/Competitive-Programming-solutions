#!/usr/bin/env perl

use strict;
use warnings;

my $n = int(shift // 115);
die unless 1 < $n && $n <= 1024;

print STDERR "n = $n\n";
print "$n\n";
for my $i (1 .. $n) {
  my $strength = 1 + int rand 100000;
  print "$strength\n";
}
