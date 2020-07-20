#!/usr/bin/env perl

use strict;
use warnings;

my $n = shift // 40;
print STDERR "n = $n\n";

my $a = int($n / 3);
my $b = int($n / 3);
my $c = int($n - $a - $b) / 2;
$b += $n - $a - $b - 2*$c;

my $s = ('0' x $a) . ('1' x $b) . ('20' x $c);
print "$s\n";
