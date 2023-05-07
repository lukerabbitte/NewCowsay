#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Il faut appeler le script $0 avec 1 argument"
    exit 1
else
    n=$1
fi

for ((i=1; i<=n; i++))
do
    cowsay $((i * i))
    sleep 1
    clear
done

clear

cowsay -T U "fin d'exercise"
