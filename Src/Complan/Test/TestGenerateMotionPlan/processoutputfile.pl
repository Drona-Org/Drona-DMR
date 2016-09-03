#!/usr/local/bin/perl

$file = "z3_output";
open(FH, $file);
@lines = <FH>;
close(FH);

$file = "planner_output";
open(FH, ">$file");

$flag = 0;
$flag1 = 0;
foreach $line (@lines)
{
  if($line =~ "vel")
  {
    $line =~ s/\(\(//g;
    $line =~ s/\)\)//g;
    print FH "$line";
  }
  if($line =~ "x_" && !($line =~ "x_f"))
  {
    $line =~ s/\(\(//g;
    $line =~ s/\)\)//g;
    print FH "$line";
  }
  if($line =~ "y_" && !($line =~ "y_f"))
  {
    $line =~ s/\(\(//g;
    $line =~ s/\)\)//g;
    print FH "$line";
  }
}

close(FH); 
