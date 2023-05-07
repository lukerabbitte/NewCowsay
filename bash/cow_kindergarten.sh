#!/bin/bash

for i in {1..10}
do
	cowsay $i
	sleep 1
	clear
done

clear

cowsay -T U "fin d'exercise"
