#!/bin/bash

# Vérifier que l'argument a été donné
if [ $# -ne 1 ]
then
    echo "Il faut appeler le script $0 avec 1 argument"
    exit 1
else
    n=$1
fi

# Vérifier si le nombre est inférieur à 0
if [ $n -lt 0 ]
then
    echo "Erreur: le nombre doit etre un nombre entier superieur ou egal a 0."
    exit 1
elif [ $n -le 2 ]
then
    echo "Erreur: le nombre doit etre un nombre entier superieur au premier nombre premier, 2."
    exit 1
fi

# Imprimer tous les nombres premiers inférieurs à n

for ((i=2; i<$n; i++))
do
    is_prime=true

    for ((j=2; j<$i; j++))
    do
        if [ $(($i%$j)) -eq 0 ]
        then
            is_prime=false
            break
        fi
    done

    if $is_prime
    then
      cowsay $i
    	sleep 1
    	clear
    fi
done

clear

cowsay -T U "fin d'exercise"
