#!/usr/bin/env perl

my $n = shift @ARGV // (5 + int rand 999995);
my $strategy = shift @ARGV // 'uniform';
die 'Too many arguments' if @ARGV;

my @people;

my $min = 70;
my $max = 250;

if ($strategy eq 'uniform') {
  @people = map {$min + int rand (1 + $max - $min)} (1 .. $n);
} elsif ($strategy eq 'randomwalk') {
  my $cur = int (($min + $max) / 2);
  my @diffs = map {(int rand 2)*2 - 1} (1 .. $n);
  for my $i (@diffs) {
    push @people, $cur;
    $cur = $cur + $i if $cur + $i >= $min && $cur + $i <= $max;
  }
} else{
  print STDERR "Unknown strategy: $strategy\n";
  exit 1;
}
print @people . "\n@people\n";
