#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(shuffle);

my $n = int(shift @ARGV // 10000);
my @weights = map {1 + int rand 500000} (1 ... $n);

my @sorted_weights = sort {$a <=> $b} @weights;
print "$n\n@sorted_weights\n";

my @edges = shuffle map {"@{[$_]} @{[$_+1]} " . ($weights[$_-1] + $weights[$_])} (1 ... $n-1);
{
  local $" = "\n";
  print @edges . "\n@edges\n";
}
