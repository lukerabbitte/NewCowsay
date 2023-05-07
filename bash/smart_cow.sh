#!/bin/bash

# Vérifier que l'argument a été donné
if [ $# -ne 1 ]
then
    echo "Il faut appeler le script $0 avec 1 argument"
    exit 1
else
    operation=$1
fi

# Initialsier avec un \ pour eviter l'expansion automatique de *
operator='\'

# Extraire les opérandes et l'opérateur de l'expression
operator+=${operation//[^+*-\/]/}
operand1=${operation%%$operator*}
operand2=${operation#*$operator}

# Les échos suivants ont été utiles pour déboguer les problèmes avec des caractères spéciaux *
#echo operator is $operator
#echo operand1 is $operand1
#echo operand2 is $operand2

# Vérifier si les opérandes sont numériques
if ! [[ $operand1 =~ ^[0-9]+$ ]] || ! [[ $operand2 =~ ^[0-9]+$ ]]
then
    echo "Operandes invalides : $operand1 et $operand2"
    exit 1
fi

if [[ $operator == "\+" ]]
then
    result=$((operand1 + operand2))
elif [[ $operator == "\-" ]]
then
    result=$((operand1 - operand2))
elif [[ $operator == "\/" ]]
then
    result=$((operand1 / operand2))
elif [[ $operator == "\*" ]]
then
    result=$((operand1 * operand2))
else
    echo erreur
    exit 1
fi

# Passer le résultat comme argument à cowsay
if [ $result -gt 99 -o $result -lt -99 ]
then
  cowsay -e '??' "Ma reponse : $result" # si la valeur absolue du résultat est supérieure à deux chiffres
else
  cowsay -e $result "Ma reponse : $result"
fi