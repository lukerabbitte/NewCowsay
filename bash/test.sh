#!/bin/bash

# Get the input argument 'n'
n=$1

# Check if n is 0
if [ $n -eq 0 ]
then
  echo "Error: n cannot be 0."
  exit 1
fi

# Initialize variables for the first two Fibonacci numbers
a=0
b=1

# Print first Fibonacci number as n is greater than 0
cowsay $a
sleep 1
clear

# Print the second Fibonacci number if n is greater than 1
if [ $n -gt 1 ]
then
  cowsay $b
  sleep 1
  clear
fi

# Loop through the remaining Fibonacci numbers less than 'n'
while [ $b -lt $n ]
do
  # Calculate the next Fibonacci number
  c=$((a + b))
  
  # If the next Fibonacci number is greater than or equal to 'n', then the loop is done
  if [ $c -ge $n ]
  then
    exit 0
  fi
  
  # Print the next Fibonacci number
  cowsay $c
  sleep 1
  clear
  
  # Update the variables for the next iteration of the loop
  a=$b
  b=$c
done

