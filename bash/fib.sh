#!/bin/bash

# Verify input argument
if [ $# -ne 1 ]
then
  echo "Error: script must be called with 1 argument"
  exit 1
else
  n=$1
fi

# Handle edge cases
if [ $n -le 0 ]
then
  echo "Error: n must be greater than 0"
  exit 2
elif [ $n -eq 1 ]
then
  echo 0
  exit 0
fi

# Generate Fibonacci sequence up to n and print each number
t0=0
t1=1
while [ $t1 -lt $n ]
do
  cowsay $t0
  sleep 1
  clear
  cowsay $t1
  sleep 1
  clear
  t2=$((t0 + t1))
  t0=$t1
  t1=$t2
done

# Print final Fibonacci number if it is less than or equal to n
if [ $t1 -eq $n ]
then
  cowsay $t0
  sleep 1
  clear
  cowsay $t1
  sleep 1
  clear
fi
