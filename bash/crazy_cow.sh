#!/bin/bash

# Vérifier que l'argument a été donné
if [ $# -ne 1 ]
then
    echo "Il faut appeler le script $0 avec 1 argument"
    exit 1
else
    n=$1
fi

factorial=1

if [[ $n -lt 0 ]]
then
    echo "Erreur l'entree doit etre un entier non negatif"
    exit 1
elif [[ $n -eq 0 ]]
then
    echo 0 | cowsay
    sleep 1
    clear
fi

for (( i=1; i<=n; i++ ))
do
    factorial=$(( factorial * i ))
    cowsay $factorial
    sleep 1
    clear
done

clear

cowsay -T U "fin d'exercise"

