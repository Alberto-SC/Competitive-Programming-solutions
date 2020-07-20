#!/usr/bin/env perl

#
# Generates test data using a simple numeric input spec.
#
# Example:
#   1 1 2  // 1 occurrence, 1 right, 2 wrong
#   2 1 1  // 2 occurrences, 1 right, 1 wrong
# Becomes something similar to:
#   a b b
#   a x correct, a {y,z} incorrect
#   b x correct, b {y} incorrect
#

use strict;
use warnings;
use List::Util qw(shuffle);

my @words = ();
my @translations = ();

sub gen_word {return join '',map {('a' ... 'z')[int rand 26]} (1 ... 20)}

while (<STDIN>) {
    my ($occurrences, $good, $bad) = $_ =~ /(\d+) (\d+) (\d+)/;
    my $word = gen_word;

    for my $i (1 ... $occurrences) {
        push @words, $word;
    }
    for my $i (1 ... $good + $bad) {
        push @translations, "$word " . gen_word . ($i <= $good ? ' correct' : ' incorrect');
    }
}

@words = shuffle @words;
print @words . "\n";
print "@words\n";

@translations = shuffle @translations;
print @translations . "\n";
print join "\n", @translations;
print "\n";
