#!/usr/bin/env perl

use strict;
use warnings;

my $n = 500;
my $disk = 10000;

print "$n $disk\n";

for my $i (1 .. $n) {
  my $b = 50 + int rand 5;
  my $a = $b + int rand 550;
  if ($i * 2 < $n) {
      $b = 770 + int rand 12;
      $a = $b + int rand 100;
  }
  print "$a $b\n";
}
