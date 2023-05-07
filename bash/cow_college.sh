#!/bin/bash

# Verification des entrees
if [ $# -ne 1 ]
then
    echo Il faut appeller le script $0 avec 1 argument
    exit 1
else
    n=$1
fi

if [ $n -le 0 ]
then
  echo "Erreur: n ne peut pas etre inferieur ou egal a 0."
  exit 2
fi

# Traitement des germes du processus
t0=0
t1=1

echo $t0 | cowsay # J'ai eu des problèmes avec 0 en cowsay, j'ai donc pipé
sleep 1
clear

if [ $n -gt 1 ]
then
  cowsay $t1
  sleep 1
  clear
fi

# Boucle tant que t2 est inférieur à n
while [ $t1 -lt $n ]
do
  t2=$((t0 + t1))
  
  # Si le prochain nombre de Fibonacci est supérieur ou égal à 'n', alors on sort de la boucle
  if [ $t2 -ge $n ]
  then
    break
  fi
  
  cowsay $t2
  sleep 1
  clear
  t0=$t1
  t1=$t2
done

clear

cowsay -T U "fin d'exercise"
