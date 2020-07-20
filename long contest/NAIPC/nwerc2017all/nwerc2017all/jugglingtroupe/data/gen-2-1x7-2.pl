#!/usr/bin/env perl

use strict;
use warnings;

my $n = shift // 40;
print STDERR "n = $n\n";

my $s = '21111111';
my $reps = int($n / length $s);
my $rem = int($n % length $s);
print $s x $reps;
print substr((reverse $s), (length $s) - $rem);
print "\n";
