# INF203 Projet Luke Rabbitte

# Intro

Le programme cowsay affiche un message ou une
citation à l'écran, en le faisant dire par une
vache ASCII ou un autre animal ASCII quelconque.

L'utilisateur peut spécifier le texte à faire dire
à l'animal en le passant en argument de la ligne
de commande ou en le saisissant via l'entrée
standard.

Le programme cowsay peut également prendre en
charge plusieurs options pour personnaliser la
sortie, telles que l'utilisation de bulles de
citation, la sélection d'un avatar spécifique,
etc.

Enfin, cowsay est utilisé de manière ludique
pour ajouter une touche d'humour aux programmes.

Dans les trois sections suivantes, je discuterai
de mes choix de code pour mes scripts bash, mes
programmes c et mon jeu basé sur des automates,
respectivement.

# Bash

## cow_kindergarten.sh
Très simplement, j'ai implémenté une boucle for
`for i in {1..10}`.

J'ai également utilisé les commandes
suivantes pour la première fois.
pour la première fois, elles apparaîtront
assez souvent.

`cowsay $i;
 sleep 1;
 clear;
`

Code complet :

```
#!/bin/bash

for i in {1..10}
do
	cowsay $i
	sleep 1
	clear
done

clear

cowsay -T U "fin d'exercise"
```


## cow_primaryschool.sh

Très similaire au précédent.

Code complet :

```
#!/bin/bash

if [ $# -eq 0 ]
then
    echo Il faut appeller le script $0 avec 1 argument
    exit 1
else
    n=$1
fi

for ((i=1; i<=n; i++))
do
	cowsay $i
	sleep 1
	clear
done

clear

cowsay -T U "fin d'exercise"
```

## cow_highschool.sh

Comme auparavant.

Code complet :

```
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

```

## cow_college.sh

J'ai dû passer un peu de temps à déboguer ce
problème, et je me suis rendu compte que cowsay
n'aime pas qu'on lui dise de sortir un message.
que cowsay n'aime pas qu'on lui dise de sortir '0'.
'0'. Comme indiqué dans mes commentaires, j'ai
trouvé que le fait d'envoyer une commande
une commande echo à cowsay a résolu le problème.

Sinon, il s'agit juste d'implémenter la logique
de base de Fibonacci.

Code complet :

```
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

```

## cow_university.sh

Utiliser l'arithmétique modulo avec deux boucles
internes pour déterminer si un nombre est premier.
si un nombre est premier. Suivi avec le booléen
is_prime.

Code complet :

```
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

```

## smart_cow.sh

Au lieu d'utiliser bc ou d'autres solutions plus
faciles, j'ai repris certains des concepts appris
en classe, ainsi que des lectures supplémentaires
sur les expressions régulières, pour diviser
l'argument donné en `operand1`,
`operator` et `operand2`.

Une fois que cela a été fait, j'ai pu effectuer
des vérifications de type if-else et afficher
le résultat.

J'ai eu quelques problèmes pour trouver comment
gérer la multiplication, car `*` est un caractère
spécial dans bash. Finalement, j'ai trouvé la
solution suivante la variable contenant `operator`
est initialisée avec le caractère d'échappement '\'.

Note : le résultat ne sera imprimé aux yeux de la
vache que si sa valeur absolue est inférieure à
100, c'est-à-dire s'il s'agit de deux chiffres.

Code complet :

```
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
```


## crazy_cow.sh

À l'origine, j'enquêtais sur la génération de
certains séquences intéressantes de la théorie
des nombres.

L'un d'eux était la séquence de **perfect numbers**,
entiers positifs qui sont égaux à la somme de
leurs propres diviseurs, à l'exclusion des
nombre lui-même.

Le code de cette première tentative peut être
trouvé ici :
```
#!/bin/bash

# Vérifier que l'argument a été donné
if [ $# -ne 1 ]
then
    echo "Il faut appeler le script $0 avec 1 argument"
    exit 1
else
    n=$1
fi

perfect_numbers_found=0
number=1

while [ $perfect_numbers_found -lt $n ]
do
    sum=0
    i=1
    start=$(date +%s.%N)
    while [ $i -lt $number ]
    do
        if [ $((number % i)) -eq 0 ]
        then
            sum=$((sum + i))
        fi
        i=$((i + 1))
    done

    if [ $sum -eq $number ]
    then
        end=$(date +%s.%N)
        runtime=$(echo "$end - $start" | bc) # la calcalatrice bc calcule l'intervalle
        seconds=${runtime%.*}
        fraction=${runtime#*.}
        cowsay "Nombre parfait $number trouve en $seconds.$fraction secondes"
        perfect_numbers_found=$((perfect_numbers_found + 1))
    fi

    number=$((number + 1))
done

cowsay -T U "fin d'exercise"

```
Cela a utilisé une variable `perfect_numbers_found`
pour garder une trace. Intéressé par l'analyse
du temps complexité, j'ai chronométré l'exécution
des programme, et a obtenu cowsay pour imprimer
à la fois le parfait numéro trouvé, et le temps
qu'il a fallu pour le trouver,
lors de sa sortie.

Ce que j'ai trouvé, c'est qu'il est devenu
incroyablement lent après que les trois premiers
nombres parfaits aient été trouvé.

Trouver le 4e a pris environ 11 minutes, et je ne
l'ai pas fait envie d'attendre assez longtemps
pour le 5ème !

En tout cas, je me suis rendu compte que c'était
peut-être pas l'utilitaire le plus convivial,
en raison de sa complexité temporelle.

J'ai donc finalement décidé de mettre en place
un **calculatrice factorielle**. L'utilisateur
a saisi `n` est multiplié par `n-1`,
`n-2`, etc... jusqu'à ce qu'il soit multiplié
par `1`.

Code complet :

```
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


```

# C

Mon programme C permet à l'utilisateur d'appeler
avec le drapeaux suivants :

```
-e <custom eye string> 'My cowsay message' 
-T <custom tongue string> 'My cowsay message' 
-d 'My cowsay message'
-p <desired ASCII art width> <image_path> 'My cowsay message' 
```

`-e` et `-t` sont simples, permettant à l'utilisateur
customisez la vache cowsay.

`-d` remplace une vache cowsay standard par un
dragon.

`-p` est le drapeau le plus intéressant. Il
"imprime assez" une coutume Illustration ASCII
qui imprime une image donnée dans l'art ASCII
à un moment donné largeur, puis ci-dessous
concatène une bannière ASCII.

J'ai eu l'idée en regardant dans ma pellicule
et découvrir que j'avais une vraie photo d'une
vache que j'ai avait pris des vacances à Dunmore
East en Irlande. Je pensais que ce serait très
intéressant d'avoir une vraie vache qui disait
quelque chose!

J'ai réalisé cela en utilisant les
bibliothèques jp2a et figlet, respectivement.

Notez que cela fonctionne mieux lorsqu'il est
dirigé vers un fichier de sortie comme
`> output.txt`. Si un assez grand `width`
est sélectionné, le texte généré sera
assez grand, et devra être vu après
dézoomer assez loin.

Le `newcow.c` est simplement le fichier principal
pour gérer les entrées de l'utilisateur et appeler
les fonctions pertinentes. La plupart des
fonctionnalités est dans `citation.c` avec
quelques constantes stockées dans
`constantes.c`. Le fichier .h des deux est
importé dans `newcow.c`.

Mon code `newcow.c` complet est ici :

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "citation.h"
#include "constants.h"
#include "wildcow.h"

int main(int argc, char* argv[]) {

    // On déclare les paramètres et leur buffer défaut
    char eyes[8] = "00";
    char tongue[8] = "U";
    char avatar[32] = "cow";

    int pretty_width = DEFAULT_PRETTY_WIDTH;
    char pretty_image_filename[PATH_CHARACTER_LIMIT];
    char quote[QUOTE_CHARACTER_LIMIT];

    // On traite des arguments. Rappel que le nom du script est stocke dans argv[0]
    for (int i = 1; i < argc; i++) {

        // Les yeux
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            strcpy(eyes, argv[i + 1]);
            i++;
        }

        // La langue
        else if (strcmp(argv[i], "-T") == 0 && i + 1 < argc) {
            strcpy(tongue, argv[i + 1]);
            i++;
        }

        // Afficher un dragon
        else if (strcmp(argv[i], "-d") == 0 && i < argc) {
            strcpy(avatar, "dragon");
        }

        // Afficher en mode pretty, qui genere une affiche ASCII a partir d'une image avec jp2a et figlet
        else if (strcmp(argv[i], "-p") == 0 && i < (argc - 1)) {
            strcpy(avatar, "pretty");
            pretty_width = atoi(argv[i+1]);
            strcpy(pretty_image_filename, argv[i + 2]);
            i++;
        }

        // On stocke la citation qui est dans le dernier argument dans une variable quote
        else {
            strcpy(quote, argv[i]);
        }
    }

    // Imprimer selon les arguments donnes
    if (strcmp(avatar, "dragon") == 0) {
        affiche_citation(quote);
        affiche_dragon();
    }
    else if (strcmp(avatar, "pretty") == 0) {
        affiche_pretty_image(pretty_image_filename, pretty_width);
        affiche_pretty_citation(quote, pretty_width);
    }
    else if (strcmp(avatar, "cow") == 0) {
        affiche_citation(quote);
        affiche_vache(eyes, tongue);
    }
    else
        printf("Erreur. Mauvaise selection d'avatar.");

    return 0;
}
```

Voici maintenant le code pour `citation.c` :

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "citation.h"
#include "constants.h"


void affiche_bordure(int width) {

    for (int i = 0; i < width + 4; i++) {
        putchar(BORDER_CHAR);
    }
    putchar('\n');
}

void affiche_citation(char* quote) {

    // Déterminer la longueur de la bulle de texte et le nombre de lignes
    int len = strlen(quote);
    int width = len < MAX_WIDTH_DEFAULT ? len : MAX_WIDTH_DEFAULT;
    int lineCount = (len / width) + 1;
    int indexInQuote = 0;

    // Imprimer le haut de la bulle de texte
    affiche_bordure(width);

    // Imprimer le corps de la citation
    for (int i = 0; i < lineCount; i++) {

        putchar(VERTICAL_CHAR);
        putchar(SPACE_CHAR);

        for (int j = 0; j < width; j++) {
            indexInQuote = i * width + j;
            if (indexInQuote < len) {
                putchar(quote[indexInQuote]);
            } else {
                putchar(SPACE_CHAR);
            }
        }

        putchar(SPACE_CHAR);
        putchar(VERTICAL_CHAR);
        putchar('\n');
    }

    // Imprimer le bas de la bulle de texte
    affiche_bordure(width);
}

void affiche_vache(char* eyes, char* tongue) {

    printf("        \\   ^__^\n");
    printf("         \\  (%s)\\_______\n", eyes);
    printf("            (__)\\       )\\/\\\n");
    printf("             %s ||----w |\n", tongue);
    printf("                ||     ||\n");
}

// Crédit d'art ASCII inconnu - du manuel de cowsay
void affiche_dragon() {

    printf("      \\                    / \\  //\\\n");
    printf("       \\    |\\___/|      /   \\//  \\\\\n");
    printf("            /0  0  \\__  /    //  | \\ \\\n");
    printf("           /     /  \\/_/    //   |  \\  \\\n");
    printf("           @_^_@'/   \\/_   //    |   \\   \\\n");
    printf("           //_^_/     \\/_ //     |    \\    \\\n");
    printf("        ( //) |        \\///      |     \\     \\\n");
    printf("      ( / /) _|_ /   )  //       |      \\     _\\\n");
    printf("    ( // /) '/,_ _ _/  ( ; -.    |    _ _\\.-~        .-~~~^-.\n");
    printf("  (( / / )) ,-{        _      `-.|.-~-.           .~         `.\n");
    printf(" (( // / ))  '/\\      /                 ~-. _ .-~      .-~^-.  \\\n");
    printf(" (( /// ))      `.   {            }                   /      \\  \\\n");
    printf("  (( / ))     .----~-.\\        \\-'                 .~         \\  `. \\^-.\n");
    printf("             ///.----..>        \\             _ -~             `.  ^-`  ^-_\n");
    printf("               ///-._ _ _ _ _ _ _}^ - - - - ~                     ~-- ,.-~\n");
    printf("                                                                  /.-~\n");
}

void affiche_pretty_image(char* filename, int width) {

    // Construire une chaîne de commande pour appeler la bibliothèque jp2a dans wsl
    char command[COMMAND_CHARACTER_LIMIT];
    char path[PATH_CHARACTER_LIMIT];

    // Construct the jp2a command
    sprintf(command, "jp2a --width=%d %s", width, filename);

    // Execute the command
    system(command);
}

void affiche_pretty_citation(char* quote, int width) {

    // Construire une chaîne de commande pour appeler la bibliothèque figlet dans wsl
    char command[COMMAND_CHARACTER_LIMIT];
    sprintf(command, "figlet -w %d -c \"%s\"", width, quote);

    // Exécuter la commande et imprimer la sortie
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
    }

    char output[OUTPUT_CHARACTER_LIMIT];
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }
    pclose(fp);
}

int find_width(char* filename) {

    FILE* fp;
    char ch;
    int line_width = 0;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    while ( ((ch = fgetc(fp)) != EOF) && (ch != '\n') ) {
        line_width++;
    }

    fclose(fp);
    return line_width;
}
```

`affiche_bordure(int width)` imprime une bordure d'une certaine largeur.
Il peut imprimer quelle que soit la constante `BORDER_CHAR` assignée.

`affiche_citation(char* quote)` imprime la bulle de dialogue en fonction d'un
largeur, gardant sa place dans la chaîne d'entrée selon
à la largeur multipliée par le nombre de lignes.

`affiche_vache()` imprime cowsay cow avec deux arguments personnalisés.

`affiche_dragon()` fait de même avec un avatar de dragon.

`affiche_pretty_image(char* filename, int width)`
utilise system(command) via un tampon pour appeler la bibliothèque
jp2a, qui convertit une image en art ASCII.

`affiche_pretty_citation(char* quote, int width)`
utilise system(command) via un tampon pour appeler figlet,
et produire une bannière ASCII selon la largeur donnée.

`find_width(char* filename)` trouve la largeur du
première ligne d'un fichier.

Les constantes sont définies dans `constants.c` comme suit :

```
const int DEFAULT_PRETTY_WIDTH = 300;
const int COMMAND_CHARACTER_LIMIT = 512;
const int PATH_CHARACTER_LIMIT = 512;
const int OUTPUT_CHARACTER_LIMIT = 15000; // Estimation prudente de la taille de la mémoire tampon pour la sortie du figlet, basée sur le produit de la longueur de 50 lignes et de la largeur par défaut de 300. 50 * 300 = 15000
const int QUOTE_CHARACTER_LIMIT = 2048;

const int MAX_WIDTH_DEFAULT = 40;
const char BORDER_CHAR = '-';
const char VERTICAL_CHAR = '|';
const char SPACE_CHAR = ' ';
```

## Autres fichiers C

Ailleurs, j'ai `wildcow.c` qui utilise le `update`
et les fonctions `goto` comme spécifié. `animer_vache()`
est appelé avec une fréquence d'images spécifiée par l'utilisateur, telle que
0,5 seconde ou 1,2 seconde.

C'est la vitesse à laquelle l'animation change.

Cela fait alors un appel à `affiche_vache_animee(int frame_increment)`
qui imprime la vache à différentes coordonnées x et y
le long de l'aérogare. L'idée avec les exemples de valeurs
étant donné que la vache marche du haut à droite vers
en bas à gauche de l'écran du terminal.

Voici le code `wildcow.c` complet :

```
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "wildcow.h"

void update() {
    printf("\033[H\033[J"); // clear screen
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y); // move cursor to (x, y)
}

void affiche_vache_animee(int frame_increment) {

    update();
    gotoxy(frame_increment, frame_increment);
    printf("             ^__^\n");
    update();
    gotoxy(frame_increment, frame_increment);
    printf("             (00)\\_______\n");
    update();
    gotoxy(frame_increment, frame_increment);
    printf("            (__)\\        )\\/\\\n");
    update();
    gotoxy(frame_increment, frame_increment);
    printf("             U   ||----w |\n");
    update();
    gotoxy(frame_increment, frame_increment);
    printf("                 ||     ||\n");
}

int animer_vache(double frame_rate) {

    for(int i = 100; i >= 0; i= i - 20) {
        affiche_vache_animee(i);
        usleep(frame_rate*100000); // conversion de secondes a millisecondes
        update();
    }
    return 0;
}
```

Enfin, j'ai le fichier `reading_cow.c` qui pour
l'instant est encore d'une forme squelettique :

```
#include <stdio.h>

int main() {
FILE *fp;
char c;

    fp = fopen("filename.txt", "r");
    if (fp == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier.\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }

    fclose(fp);

    return 0;
}
```

J'utilisais CLion Windows à partir d'une machine virtuelle WSL. Bien que
J'ai beaucoup appris sur les makefiles et, en particulier,
l'application CMake, j'ai eu quelques difficultés majeures
en essayant de travailler sur ce dossier en particulier.

# Automate

C'était la mise en œuvre du jeu du cowsay qui
représente les différentes étapes de la faim d'une vache, et
nous transporte entre des états basés sur des fonctions qui
appeler des générateurs de nombres aléatoires.

J'ai eu quelques problèmes pour comprendre les détails les plus fins de la logique
basé sur la brève description du jeu. Par exemple, pour
un certain temps, j'ai supposé que le jeu devrait se terminer lorsque le
l'approvisionnement alimentaire tombe en dessous de 0. Cependant, j'ai vite réalisé
lors du test que vous avez encore une chance de survivre
même si cela arrive.

J'ai décidé de représenter des états plus précis et détaillés
selon le niveau de forme physique de la vache que celui indiqué dans le
Description du projet. Cela comprenait la gestion de 5 états
au lieu de 3. Dans mon implémentation, il y a une vache
pour `lifesucks` 'faim' ainsi que le
`lifesucks` état 'suralimenté'.

J'utilise un fichier `citation.c` simplifié appelé
`bulle_citation.c` pour générer les citations :

```
#include <stdio.h>
#include <string.h>
#include "citation.h"

#define MAX_WIDTH_DEFAULT 40
#define BORDER_CHAR '-'
#define VERTICAL_CHAR '|'
#define SPACE_CHAR ' '

void affiche_bordure(int width) {

    for (int i = 0; i < width + 4; i++) {
        putchar(BORDER_CHAR);
    }
    putchar('\n');
}

void affiche_citation(char* quote) {

    // Déterminer la longueur de la bulle de texte et le nombre de lignes
    int len = strlen(quote);
    int width = len < MAX_WIDTH_DEFAULT ? len : MAX_WIDTH_DEFAULT;
    int lineCount = (len / width) + 1;
    int indexInQuote = 0;

    // Imprimer le haut de la bulle de texte
    affiche_bordure(width);

    // Imprimer le corps de la citation
    for (int i = 0; i < lineCount; i++) {

        putchar(VERTICAL_CHAR);
        putchar(SPACE_CHAR);

        for (int j = 0; j < width; j++) {
            indexInQuote = i * width + j;
            if (indexInQuote < len) {
                putchar(quote[indexInQuote]);
            } else {
                putchar(SPACE_CHAR);
            }
        }

        putchar(SPACE_CHAR);
        putchar(VERTICAL_CHAR);
        putchar('\n');
    }

    // Imprimer le bas de la bulle de texte
    affiche_bordure(width);
}
```

Le flux principal du jeu est contrôlé dans
`tamagoshi_cow.c` :

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "citation.h"

const int min_stock = 0;
const int max_stock = 10;

int fitness = 5;
int stock = 5;
int game_mode = 0; // 0 = normal, 1 = pro, changer le points requis pour les trophees

void affiche_vache(int fitness) {

        // byebyelife_faim
        if (fitness<=0) {
            affiche_citation("Not Enough Food...Bye Bye Life!");
            printf("        \\   ^__^         /\n");
            printf("         \\  (XX)\\_______/\n");
            printf("            <__>\\-----w-)     \n");
            printf("              U |      |\n");
            printf("                 |     |\n");
        }

        // lifesucks_faim
        else if (fitness>=1 && fitness<=3) {
            affiche_citation("Not Enough Food...Life Sucks!");
            printf("        \\   ^__^          \n");
            printf("         \\  (o0)\\_______/\n");
            printf("            <__>\\-----w-)     \n");
            printf("              U |      |\n");
            printf("                 |     |\n");
        }

        // liferocks
        else if (fitness >=4 && fitness <=6) {
            affiche_citation("Life Rocks!");
            printf("        \\   ^__^\n");
            printf("         \\  (oo)\\_______\n");
            printf("            (__)\\       )\\/\\\n");
            printf("             U ||----w |\n");
            printf("                ||     ||\n");
        }

        // lifesucks_suralimentation
        else if (fitness>=7 && fitness<=9) {
            affiche_citation("Too Much Food...Life Sucks!");
            printf("        \\   ^__^\n");
            printf("         \\  (.o)\\_______\n");
            printf("            (__)\\       )\\/\\\n");
            printf("             U ||----w |\n");
            printf("                ||     ||\n");
        }

        // byebyelife_suralimentation
        else if (fitness >=10) {
            affiche_citation("Too Much Food...Bye Bye Life!");
            printf("        \\   ^__^\n");
            printf("         \\  (XX)\\_______\n");
            printf("            (__)\\       )\\/\\\n");
            printf("             U ||----w |\n");
            printf("                ||     ||\n");
        }

        else {
            printf("Erreur : entree inattendue. La condition physique des vaches doit etre comprise entre 0 et 10 inclus.\n");
        }
}

void affiche_trophee(int position) {

    printf("  _______\n");
    printf(" |       |\n");
    printf("(|   %d   |)\n", position);
    printf(" |       |\n");
    printf("  \\     /\n");
    printf("   `---'\n");
    printf("   _|_|_\n");
}

int fitness_update(int lunchfood_fitness) {
    int digestion = (rand() % 4) - 3;
    printf("Digestion is %d\n", digestion);
    return (fitness + lunchfood_fitness) + digestion;
}

int stock_update(int lunchfood_stock) {

    int crop = rand() % 7 - 3;
    printf("Crop is %d\n", crop);
    int updated_stock = (stock - lunchfood_stock) + crop;

    if (updated_stock > 10) {
        stock = 10; // Plafonner le stock à 10
        return stock;
    } else {
        stock = updated_stock;
        return stock;
    }
}

int main() {

    srand(time(NULL)); // initialiser le germe aléatoire

    // On déclare les variables qui influencent le jeu.
    int digestion; // sera généré aléatoirement sur chaque boucle entre 0 et 3 inclus
    int crop; // sera généré aléatoirement sur chaque boucle entre -3 et 3 inclus.
    int lunchfood; // sera demandé à chaque fois à l'utilisateur. N'acceptez les entrées de l'utilisateur que si <=stock
    int lifespan = 0; // iterateur dans la boucle principale
    int validInput = 0; // la gestion des erreurs

    int duree_de_vie = 0;

    printf("\n\n\n+++++++++++++++++++++++++++++++++++++++++++++++++\nBienvenue dans le jeu cowsay base sur "
           "l'automate\n+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
    printf("Selectionnez un mode de jeu. Le mode Pro necessite des points plus eleves pour gagner un trophee\n");
    printf("Pro - Taper 1, Normal - Taper 0: ");
    scanf("%d", &game_mode);

    while (1) {

        // Afficher la vache et le stock
        validInput = 0;
        printf("\n\n\n++++++++++++++++++++++++++++++\nDuree de vie: %d\n"
               "++++++++++++++++++++++++++++++\n\n", duree_de_vie);
        affiche_vache(fitness);
        //printf("\nFitness actuel: %d", fitness); // utile pour tester
        printf("\nStock actuel: %d\n\n", stock);

        // Demander à l'utilisateur la valeur de lunchfood
        while (!validInput) {

            printf("Donner la valeur de lunchfood pour la vache:");

            if (scanf("%d", &lunchfood) != 1) {
                printf("Erreur: entrez un nombre entier inferieur ou egal au niveau de stock actuel.\n");
            }
            else if (lunchfood<0) {
                printf("Lunchfood doit etre >= 0!\n");
            }
            else if (stock<0 && lunchfood!=0) {
                printf("Vous n'avez plus de nourriture dans votre stock! Lunchfood doit etre 0\n");
            }
            else if (stock<0 && lunchfood==0) {
                validInput=1;
            }
            else if ( (stock>=0) && (lunchfood > stock) ) {
                printf("La valeur de Lunchfood depasse le stock actuel. Essayer a nouveau.\n");
            }
            else if (lunchfood <= stock) {
                validInput=1;
            }
            else
                printf("Erreur: entrez un nombre entier inferieur ou egal au niveau de stock actuel.");

        }

        // Mettre à jour la condition physique et le stock
        fitness = fitness_update(lunchfood);
        stock = stock_update(lunchfood);

        if ( (fitness >= 1 && fitness <= 9) )
            duree_de_vie++;
        else {
            printf("\n\n\n++++++++++++++++++++++++++++++\nGAMEOVER\n++++++++++++++++++++++++++++++\n\n");
            affiche_vache(fitness);
            //printf("\nFitness actuel: %d", fitness); // Utile pour tester
            printf("\nStock actuel: %d\n", stock);
            printf("\n++++++++++++++++++++++++++++++\nSTATISTIQUES\n++++++++++++++++++++++++++++++\n");
            if (stock==-1) {
                printf("\nVous n'avez plus de nourriture dans votre stock!\n");
            }
            break;
        }
    }

    // Afficher le score final et le trophée
    printf("Score final: %d \n", duree_de_vie);

    if ( (duree_de_vie) >= ( (game_mode==0) ? 15 : 30) ) {
        affiche_trophee(1);
    } else if ( (duree_de_vie) >= ( (game_mode==0) ? 10 : 20) ){
        affiche_trophee(2);
    } else if ( (duree_de_vie) >= ( (game_mode==0) ? 5 : 10) ){
        affiche_trophee(3);
    } else {
        if (game_mode==0)
            printf("Vous n'avez pas gagne de medaille en mode normal!\n");
        if (game_mode==1)
            printf("Vous n'avez pas gagne de medaille en mode pro!\n");
    }

    return 0;
}
```
`affiche_vache(int fitness)` imprime la vache selon une valeur fitness entière.

`affiche_trophee(int position)` prend le score final de l'utilisateur
et imprime un trophée ASCII avec leur position sur le
podium (soit 1, 2 ou 3). Les points requis
pour obtenir un trophée à ces niveaux change en fonction de
si l'utilisateur a sélectionné le mode normal ou pro au début !

`int fitness_update(int lunchfood_fitness)` et
`int stock_update(int lunchfood_stock)` sont implémentés
comme demandé.

`int main()` effectue beaucoup de gestion des erreurs de saisie utilisateur,
par exemple ne pas laisser l'utilisateur entrer une valeur de
`lunchfood` supérieur à ce qui est
disponible en "stock".

À la fin du jeu, les statistiques sont affichées avec
un trophée et une place sur le podium, si l'utilisateur a atteint le niveau requis des points.

# Résumé

Dans l'ensemble, j'ai beaucoup appris sur l'outillage et la structure de projet
dans le langage c, ainsi que de se familiariser beaucoup plus
avec bash, et les bibliothèques très utiles à la disposition de ceux
développer avec elle.

J'ai essayé dans la mesure du possible d'améliorer la lisibilité en
en laissant des commentaires et en évitant l'encombrement du programme principal
fichiers de flux, au lieu de configurer des fichiers séparés pour stocker
constantes et fonctions auxiliaires.

Cela a nécessité une réflexion constante sur la lisibilité et
conception.

Bon nombre des idées avec lesquelles j'ai travaillé ici m'ont inspiré davantage
réfléchir aux moyens de s'améliorer. Par exemple, le hasard
les numéros générés pour le jeu cowsay sont toujours
quelque peu déterministe, étant basé sur le temps. Si je
avait plus de temps, j'aimerais enquêter en utilisant
de vrais générateurs de nombres aléatoires tels que ceux proposés
par random.org via leur API.

J'ai passé environ une journée à trouver et
la mise en œuvre de l'art ASCII et
générateur de bannières. C'est ce dont je suis le plus fier en tant que
il est toujours agréable de montrer une sortie visuelle aux autres.
J'aimerais étudier la génération d'art ASCII et la
mathématiques du traitement d'image plus, en particulier
les étapes de prétraitement et de détection de luminance
que j'imagine sont impliqués dans les bibliothèques que j'ai utilisées.

# Annexe : Exemples d'interactions

# Bash Exemples de sorties

## cow_kindergarten.sh

`./cow_kindergarten.sh`

Cela produit une série de vaches se terminant par :

```
 ____
< 10 >
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
                
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||


```

## cow_primaryschool.sh

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_primaryschool.sh 4

 ___
< 1 >
---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 2 >
---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 3 >
---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 4 >
---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||
```

## cow_highschool.sh

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_highschool.sh 5
 ___
< 1 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 4 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 9 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 16 >
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 25 >
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_highschool.sh 0
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_highschool.sh -5
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_highschool.sh 1
 ___
< 1 >
---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||
```

## cow_college.sh

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_college.sh 
Il faut appeller le script ./cow_college.sh avec 1 argument
```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_college.sh 20
 ___
< 0 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 1 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 1 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 2 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 3 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 5 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 8 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 13 >
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_college.sh -5
Erreur: n ne peut pas etre inferieur ou egal a 0.
```

## cow_university.sh

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_university.sh 30
 ___
< 2 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 3 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 5 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 7 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 13 >
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 17 >
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 19 >
 ----
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 29 >
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_university.sh -5
Erreur: le nombre doit etre un nombre entier superieur ou egal a 0.

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./cow_university.sh 2
Erreur: le nombre doit etre un nombre entier superieur au premier nombre premier, 2.
```

## smart_cow.sh

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./smart_cow.sh 3+11
 _________________
< Ma reponse : 14 >
 -----------------
        \   ^__^
         \  (14)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./smart_cow.sh 3-9
 _________________
< Ma reponse : -6 >
 -----------------
        \   ^__^
         \  (-6)\_______
            (__)\       )\/\
                ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./smart_cow.sh 5000/12
 __________________
< Ma reponse : 416 >
 ------------------
        \   ^__^
         \  (??)\_______
            (__)\       )\/\
                ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./smart_cow.sh 15*21
 __________________
< Ma reponse : 315 >
 ------------------
        \   ^__^
         \  (??)\_______
            (__)\       )\/\
                ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./smart_cow.sh 1524*2491248
 _________________________
< Ma reponse : 3796661952 >
 -------------------------
        \   ^__^
         \  (??)\_______
            (__)\       )\/\
                ||----w |
                ||     ||

```

## crazy_cow.sh

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./crazy_cow.sh 8
 ___
< 1 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 2 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 6 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ____
< 24 >
 ----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 _____
< 120 >
 -----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 _____
< 720 >
 -----
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ______
< 5040 >
 ------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 _______
< 40320 >
 -------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./crazy_cow.sh 2
 ___
< 1 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ___
< 2 >
 ---
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./crazy_cow.sh -5
Erreur l'entree doit etre un entier non negatif
```

## crazy_cow.sh (version initiale avec des perfect numbers)

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/bash$ ./crazy_cow.sh 4

 _______________________________________
/ Nombre parfait 6 trouve en .000727352 \
\ secondes                              /
 ---------------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________________________________
/ Nombre parfait 28 trouve en .000955625 \
\ secondes                               /
 ----------------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 _________________________________________
/ Nombre parfait 496 trouve en .003855925 \
\ secondes                                /
 -----------------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 _______________________________
/ Nombre parfait 8128 trouve en \
\ 672.159289116 secondes           /
 -------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
 ________________
< fin d'exercise >
 ----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

# C Exemples de sorties

## newcow.c

Remarque `newcow.c` utilise les fonctions de `citation.c` et
constantes de `constants.c` également.

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay hello
---------
| hello |
|       |
---------
        \   ^__^
         \  (00)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay sdoif3r8u2r2qw#fqwf#
------------------------
| sdoif3r8u2r2qw#fqwf# |
|                      |
------------------------
        \   ^__^
         \  (00)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay -e 99 "Hello"
---------
| Hello |
|       |
---------
        \   ^__^
         \  (99)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay -e \#\# 'Hello'
---------
| Hello |
|       |
---------
        \   ^__^
         \  (##)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay -d 'Hello from dragon mode'
--------------------------
| Hello from dragon mode |
|                        |
--------------------------
      \                    / \  //\
       \    |\___/|      /   \//  \\
            /0  0  \__  /    //  | \ \
           /     /  \/_/    //   |  \  \
           @_^_@'/   \/_   //    |   \   \
           //_^_/     \/_ //     |    \    \
        ( //) |        \///      |     \     \
      ( / /) _|_ /   )  //       |      \     _\
    ( // /) '/,_ _ _/  ( ; -.    |    _ _\.-~        .-~~~^-.
  (( / / )) ,-{        _      `-.|.-~-.           .~         `.
 (( // / ))  '/\      /                 ~-. _ .-~      .-~^-.  \
 (( /// ))      `.   {            }                   /      \  \
  (( / ))     .----~-.\        \-'                 .~         \  `. \^-.
             ///.----..>        \             _ -~             `.  ^-`  ^-_
               ///-._ _ _ _ _ _ _}^ - - - - ~                     ~-- ,.-~
                                                                  /.-~

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay -T $ 'Hello'
---------
| Hello |
|       |
---------
        \   ^__^
         \  (00)\_______
            (__)\       )\/\
             $ ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay -T $ -e '..' 'Hello'
---------
| Hello |
|       |
---------
        \   ^__^
         \  (..)\_______
            (__)\       )\/\
             $ ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
--------------------------------------------
| Lorem ipsum dolor sit amet, consectetur  |
| adipiscing elit, sed do eiusmod tempor i |
| ncididunt ut labore et dolore magna aliq |
| ua. Ut enim ad minim veniam, quis nostru |
| d exercitation ullamco laboris nisi ut a |
| liquip ex ea commodo consequat. Duis aut |
| e irure dolor in reprehenderit in volupt |
| ate velit esse cillum dolore eu fugiat n |
| ulla pariatur. Excepteur sint occaecat c |
| upidatat non proident, sunt in culpa qui |
|  officia deserunt mollit anim id est lab |
| orum.                                    |
--------------------------------------------
        \   ^__^
         \  (00)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay -p 50 /mnt/c/Users/luker/CLionProjects/NewCowsay/dunmore_east_cow.jpg "Hello, this is a photo of a cow I took in Ireland." > test_output_1.txt

cccccccccllccloolcllccllllcccc::cc;....           
ccclcccllcllolloololloooloollllooc....            
cllllllllolooolllolllooooooooolll....             
llloooolllllololcllccloododdxlcl......  ..        
llllolllllllolloolllcllldOKXKKkl'.,'           ...
cclcc::clllllloooolllodk0XXKKKKK0c.dc      .......
ccollcccllllllcol,'.,:ldkkkkO00000dd:........   ..
c:lcc::cclllollll..',:okxxodxOKKXKO...............
lccclcc:cllllllll..,',xxxkxOkOoc:;c'..'..'.'''....
lcclodolollllllooc',lxdOkOO00k;....cdl.'..''''....
llllclloolollllolldkddk00XXXXO,......cOl..........
cccccc:cclllcocclkkdoxOKNNNNKd......:'..'.........
::ccclllccccclllxxkxxk0KKKXKOc.. .:c...,;..  .....
c;:::ccclclcccccodxxxkOkkkxlc:,.;:;,;cxNx.        
::,,,::cl::c::::dKdodoocc,;:cloooloooxXNN:.       
c:cc;;::c:cc;;;d0xlllc::;,:codddddddkKXXNXc.      
ccc:c;,:;;;:,;oOklclcc;;lloodddddkOKKKKKKX0'.     
:cclccc:::;::lO0xllccloloooooddx0XXXXKKKK00:....  
ccclcc::c:lldKXKkdodlododdddddkKXXXXXXXKKK0Ox....l
lclcclc;colkXXNNKKKkoloodddddkO00KKKKKKK0OOO0c..dx
llloloolookXNNNNXKkoooooodddkOkkO000OOOOkxddxxOO0x
lllllooloONNNNNNNKxoooddddxO00Oxxxxdddddollc::cloc
oooclllxKNNNNXNNXkxxxxdddxOOOkkkdollcccccccc::::::
llloooldxOXNNNNXOxxddoooodoollllllc:::lloooolcllcc
llloll:;,'lXXXXOxxxxOolcc:::cllllccclll;''c::;,,;;
cc:c::c'',;ok00xxxOXk:ccccclcccloooolcl.. ;:;;,'''
:::clc:c:,,:cdooddxl:::,;:;ccc:lcolllll' ..c:;;,''
ccll::clcccl::;;;;;:::,;;;;:;:c:::collcc.:.:c:;,''
c:ccccc:c::::::,,,;,,;,;;:;,;,,;;:;:cccccc';c:;,''
c::c:c:,;,'''',''',''',''''''.''''';:;:c;c:,c:;;''
:c;::;...................'.........',',,,:::c::;,'
,,:;,....................................::cc::;,,
,,,;.....................................;::::;;,'
 _   _      _ _          _   _     _       _     
| | | | ___| | | ___    | |_| |__ (_)___  (_)___ 
| |_| |/ _ \ | |/ _ \   | __| '_ \| / __| | / __|
|  _  |  __/ | | (_) |  | |_| | | | \__ \ | \__ \
|_| |_|\___|_|_|\___( )  \__|_| |_|_|___/ |_|___/
                    |/                           
                _           _                 __ 
   __ _   _ __ | |__   ___ | |_ ___     ___  / _|
  / _` | | '_ \| '_ \ / _ \| __/ _ \   / _ \| |_ 
 | (_| | | |_) | | | | (_) | || (_) | | (_) |  _|
  \__,_| | .__/|_| |_|\___/ \__\___/   \___/|_|  
         |_|                                     
                                     ___ 
          __ _    ___ _____      __ |_ _|
         / _` |  / __/ _ \ \ /\ / /  | | 
        | (_| | | (_| (_) \ V  V /   | | 
         \__,_|  \___\___/ \_/\_/   |___|
                                         
          _              _      _       
         | |_ ___   ___ | | __ (_)_ __  
         | __/ _ \ / _ \| |/ / | | '_ \ 
         | || (_) | (_) |   <  | | | | |
          \__\___/ \___/|_|\_\ |_|_| |_|
                                        
        ___          _                 _   
       |_ _|_ __ ___| | __ _ _ __   __| |  
        | || '__/ _ \ |/ _` | '_ \ / _` |  
        | || | |  __/ | (_| | | | | (_| |_ 
       |___|_|  \___|_|\__,_|_| |_|\__,_(_)
                                           

```

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./NewCowsay -p 200 /mnt/c/Users/luker/CLionProjects/NewCowsay/monks.JPG "This
 is a small excerpt of a painting I saw at the Musee d'Orsay in Paris" > test_output_2.txt

.';;:cccccclllllllllllllllllloooooooooddodddddddddxdxxxxxxxxkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxkkkkkxkkkkxxxxxxxxxxxxdxddddddddddddddddddddddddddddddddddddoooooooodoooodddddddddddddddddddddoooolllllll
,;:ccccllllllllllolloooooooooooddddddddddxdxxdxxxxkxxxxxxxxxkkkxxxkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxkxxxkkkxxxxxxxxxxxxxxxxxxxxxxxxxdxxdxdddxdddxxxddddddddddddooooooodddodddoddooddodddddddddodooooooolll
ccllllllllloooooooooooooooooddddddddddxddxxxxxxxxxxxkkxxkkkkkkkkkkkkkkkkkkkkkkOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxdxxxxxxxxxxxxxxxdddddddddddddddddddddddddddddddddddddddddddoooooool
clllllllllooooooooooooooddddddddddxxxxxxxxxxxxxxxxxxxxxkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkOOOOkkOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxxxdddddddddddxxddddddddddddddddddddddddoooooo
lc;;;;;;clooooooooodddddddxddxxxxxxxxxxxxxxxxxkkkkkkkkkkkkkkkkkkkkkkkkOOOOkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxddxddxxxxddddxxxxxxxddddddddoo
:;,,,'',;:c;;:lddddddxxxxxxxxxxxxxxkkkkkkkkkkkkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkOkkkkkkOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxddddddddoo
''''',;:cllllodddxxxxxxxxxxxxxkkkkxxkkkkkkkkkOOOOOOOOOOOOOOOOOOOOOOOO00O0000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxdddddddd
',;clloooooodddxxxxxxxxxxkkkkkkkkxxxxdoooolodxkOOOO0OOOOOOOOOOOO00000000000000000000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkOkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxdddddddddd
cllooddddxxxxxxxxxxxkkkkkkkkkkkxxl:;,,,,,',,,,;cdOOOO00000000000000000000000000000000000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxxxxxxxdd
oodddxxxxxxxxkkkkkkkkkkkkkkkkkkxc,',,',,,'''...',:x0000K00000000000K0000000000000000000000000000000000000000000000000OO00OOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxxxxd
llloddxxxxkkkkkkkkkkkkkkkkkkkkko,''''''..........'':x000000000000000000000000000000000000000000000000000000000000000O00000OOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxx
lllloddxxxkxxkkkkkkkkkkkkkkkkkkd,''................''x0000000000000000000000000000000000000000000000000000000000OOO0000000OOOOOOOOOOOOOOOOkOkOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxx
dddooodxxxxxxxxxkkkkkkkkkkkkkkkk;'..........'.''''.'.c00000Oxollccclodx000K00K000000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxkkkkkkkkkkko....''...............,O0Odc,,,,,,,;:::::d0KKKK0000000000000000000000000000000000O000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxkkkkkkkkkkkkkkkkkkl....'................'xkl,',,,,,,,,,,,,',:O000000000000000000000000000000000O0000OOOOOO00OOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxkxxkkkxxxxxxxxxxxxx
xxxkkxxxxxxxxxxkkkkkkkkkkkkkkkkx,....................'xx'..............''.,d00000000000000000000000000000000000000000OO00O0OO000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxkkkkkkkkkkxx
xxxxxxxkxxxxxxxxxxkkkkkkkkkkkkxxc....................,kk:',,,;,,,;,',,......l00000000000000000000000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
xxxxkxkkxkkxkxxxxxxxkkkkkkkxxxxc.....................ckkl;ccccccc:;::',,,,cok0000K0000KK000000000000000000000000000000000000000000000000000000O0OOOOOOOOOOOOOkkkkkkkkOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
xxxxxxxxxxxxxxxxxkkxkkkxxxxxxdl'....................,dOOkcllllccc:;;;,,,;:x000000K00KKKK000000000K0000000000000000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOkOkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
xxxxxxxxxxxxxxxxxkkkkkxxxdl;,.......................:kOOdlllllccc:;:;;;;:k000000KKKKK0KKKKKKKKKKKKKK00K000000K000000000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkk
xxxxxxxxxxxxxxxxkkkkxxoc,...........................';lollooolc::;,;,,;:d000KKKKKKKKKKKKKKKKKKKKKKKKKK000KKK0000KKKK000000K00000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOkOOkkkOOkOkkkOkkkkkk
xxxxxxxxxkkkkkkkkkxd:'..............................'';llooool:;;,',,;:x00KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0KKKKKK000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkk
xkkkkkkkkkkkkkkkkxc'............................''''',;;;;;;;;;,,''',:k0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0000000000000000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOk
kkkkkkkkkkkkkkkkk:..........................''',,'''''''',,,,'''''..:O000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOk
kkkkkkkkkkkkkkkko..........................'..'''..'''',,,''''''''..'coxk0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0000000000000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOO
kkkkkkkkkkkkkkkx;....................................''''''''''''''''...':k0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK00K0000000000000000000000000000000OOOOOOOOOOOOOOOOOOOO
OOOOOOOOOOOOOkkl.....................................'''''''''....'''',,,,;:lx0KKKKKKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKXKKKKKKKKKKKKK0000KKKKKKKKKKKKKKKKKKKKKKK00000000000000000000000000000000000
OOOOOOOOOOOOkkl......................................''',,'...'',,,,,,,''',,,,;o0KKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKKKKKKKKK0000KKKKKKKKKKKKKKKKKKKKKKKK00000000000000000000000000000000
OOOOOOOOOOOOkd......................................'''''....''','',,''''....''',:oOKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKKKKKK00KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK00KKKKKKKKKKKKKK00
OOOOOOOOOOOOx'......................................''.....,''''''''''''...........'cO0KKXXXXXXXXXXXXXXXXXXXXKKXKKKKKKKKKKKXXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK00000000000000000KKK00000000
OOOOOOOOOOOOc..............................'.....'........''''''''.'''.''............,,o0KKKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKXXXKKKKKKKKKKKKKKKKKKKKKKKKKKKK0KKK0KKKK0KKKKKKKKKKKKKKKKKKKKKKKK
000000O0OOOO,..............................................'''''...''..''..............';cOKKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKXXKKXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK00000000000
000000000OOO,..............................................''......'....'..............''',kKXXXXXXXXXXXXXXXXXXXXXXXXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0K0K00000000
000OO0000OOOc...............................................'......'....''................',x0XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKKKKKKXXXXXKKKKKKKXKKKKKKKKKKKKKKKKK0K0KKKKKKKKKKKKKKK0000000000000000
O00OOO00OOOOx'......... ...........................................'.....'..................';dKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKxddddx0KKKXKKKKKXKKk0KKKKKKKKKKKKKOkOKKKKKKKKKKKKK0000000000000000O00O
00000000OOOOOl..... ........................................'................................',ckXXXXXXXXXKKKKKKKKKXXXXXXXXKKKKK0ddoooooooxOKKOOOkxdooodxO0KKKKKKKKOdloodkOKKKKKKKKKK0KK000000000000000O
000000000000Oo....   ....  ............... .................'..................................';kXXXXXXXXXKXXXXXKXXXXXXXXXXKXKOdodoooollclo0kllolllooololoddddddddoolcllllxOOOOOOOOOOOOO000000000000000
OOOO00O00OOOOl.....    ...  .............  ................................'....................'lKXXXXXXXXXXXXXXXXXXXXXXXKXKKKOdoollllllcclllllllllllllllllclccccllllclccccccccccccccclldddddddddddoolo
000O0OOOOOOOOo'.....   .      ..........    .................... ..........'....................'cKKKKKKXXXXXXXXXXXXKKKKKKKKKOkdololllllccccccccccccccclcccccccccccccccccc:::cccc::::::::::::::::::ccccc
OOOOOOOOOOOOkc........   . ..   ........    .............................. .....................,dKKKKKKKKKKKKKKKKKKKKKKK0Oxdoloolllcccc;,,;:ccccccccccccccccccc::::::::::::::::::::::::::cccccccccccccc
OOOOkkOkkkkkx;.....         ............    ..................... .......  ....................'o000KK000KKKKK0KKKKK000Okolc::;;;;;;,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;::::::::::;;;:;;;:;::;:::::::::
OOOkkkkkkkkkd,....           ..  .......     ...........................    ..................'oOO00000000000000Okxxolc::::;;;;;:;;;;;;;,;;;;;,;;;;;;;;;;;;,,,,,,,,,,,,,,,,,,,,,,,,,,,,'''''''''',,,,,,,
kkkkkkkkkkkko....         ....  ... ...       ..........................    .................'oxkkkkkxxkxxxxolcccc:::ccccc:::;;;;;;;;;;;;;;;,;;;;;,,,,;;;;;;;;,,,,,,,,,,,,,,,,,,'',,,,,,,,,,,,,''',,''''
kkkkkkkkkkkkd,..         ....  ... ....        ................... ....       ..............;oxxxxxxxxdolcccccccc:cccccccc:::::::::::::::::::;;;;;;;::;;:::::::::::;;;,,''',,''''''''','....'','''''''''
kxxkxxxxxxxxxxdc:,..... ..... .... .....          .. .............  .....          ......:lodxxxxxxddoccc::::c::cc:::::c::::::::;:::;::::::::::::::c:::::::::::::::,'',,,,,,,,;,,,,'..........''''''',,,
dddxxxxxxxxxxddddddddoc.....                        ......................   .      . ..'ooodooolcc:cc:::::::::;::::::::::::::::::::::::;;:::::::::::;;:::::::;:::,.....';::::::;;'..................',;
lllooooooooooooooooooo;..                          ................. .......  ..    ....,;;;;,,;,;;;;;;;;,,,;;,,,,;,;;;;;;;;;:;:;;:::::;;;;;;:::::::;;:::;;;,;;;;;'.......,;::::::;'...................'
;;;;;:::::::::::::::::..                          .....................................''',,,,,,;;;;;;;,,,,,,,,,,,,,,,,,,,,,,;,,,;;:;;,,,,,;;;;;;;;;;;;:;,'....'','........';:::::;'....................
,,,,,;;;;;;;;;;,,,,,,,...                         ................... ....... .... ...''',,,,,,,,,,,,,,,,,,,,,,,,,,,;;;;;;;;;;;;,,,'''',,,,'',,,,;;;;;;;,'..................;::::::,,...................
,;;,,,,,,,;;,,,,,,,,,'..                         .................... .......  ...  .',,;;;;;;;;;;;,;,,,,,;;,;;;;;;;;;;;;,,;,,,,,,''''''',,,;;;;;;;;;;;:;,..................,,','''',''''''.............
;;;;;;,,,,;;,,,;;;,;,'..                         ....................  .......   .. ..;;;;;;;;;;;;;;::;;;;;;;;;;;;;;;;,,,,;;;;;;;,,,;;;;;;;;;;;;;;;;;;;;,,'.............'...........'''''''',,,,,'''''''
,,''',,,,;;;;;;;;;;;,..                          ..................... .......    .  .';;;;;;:;:::::;;;;;;;;;;;;,;;;;;;,;::;;,,,;;,,,,,;;;;,,,,,;,,,,,,,...............................''''''''',,,,,,''
........'''''''''''''..             .           ......................  .....     .  .'::ccc::::::::::::::::::::::::;;;;;;;;;;;;,,,;;;;;;;;;;,,,,',,,,,,'.............'......'''',,,,'''',,,'',,,,,',,''
......................                          ......................  ......        .,,,,,;;;;;;,,,,,,;;;;;;:;;;;;::;:::::;;;;;;;;;;;;,;;;,;,;;,;;;,,,,'.........'''''',,,,,,,,;,;;;,'',,,'.'',,,'''''
.....................                           ......................  ......     .  ....''''.....''''..........'''',,,;;:::::cc:::::::::::::::::::::::;;;;;;;;;;;;,,,;;,;;;;;,,,,,,,,,,,,,,,,,,,,,,,,,
 ....................                           ......................   .....        ....................................'',;;::::::::;'',;::::::::::;:;;;;;;;;;;;;;;;;;,,,;,,;;;;;;;;;;;;;;;;;;;;;;,;;
   .................                           ....  .................   .....         ..........................................'',,;;',',,,;,,;;::::::;;;;;;;;;;:;;;;;;;;;;;;;;;;;;;;;;;;,;;,,,,,,,,,,
     ...............                           ....  .................   ......        .....................................................''..'','',,,,,,,,,,,,',,'''''''''''',,,,,,,,,,,,,;;;;;,,,,,,
       ............                            .... ..................   ......        .................................................................''''''''''''',,,,,,,,,,,,,,,,,,,,,,,;;;,,,,,,,,,
         ..........                           ..... ..................    .....        ................................................................................''''''''''''''''''''''''''''''''.
            .......                           ..... ..................    .....         ................................................................................................................
              ....                            ..... ..................    .....         ................................................................................................................
                                              ..... ..................    .....         ................................................................................................................
                                             ...... ..................    ......        ................................................................................................................
                                             ..... ...................     .....        ............................................................................................................    
                                             ..... ..................      .....        ..''.........................................................................................................   
                                             ..... ..................      .....        ..,,,'........................................................................................................  
   _____ _     _       _                                   _ _                                _            __                       _       _   _               ___                              _   
  |_   _| |__ (_)___  (_)___    __ _   ___ _ __ ___   __ _| | |   _____  _____ ___ _ __ _ __ | |_    ___  / _|   __ _   _ __   __ _(_)_ __ | |_(_)_ __   __ _  |_ _|  ___  __ ___      __   __ _| |_ 
    | | | '_ \| / __| | / __|  / _` | / __| '_ ` _ \ / _` | | |  / _ \ \/ / __/ _ \ '__| '_ \| __|  / _ \| |_   / _` | | '_ \ / _` | | '_ \| __| | '_ \ / _` |  | |  / __|/ _` \ \ /\ / /  / _` | __|
    | | | | | | \__ \ | \__ \ | (_| | \__ \ | | | | | (_| | | | |  __/>  < (_|  __/ |  | |_) | |_  | (_) |  _| | (_| | | |_) | (_| | | | | | |_| | | | | (_| |  | |  \__ \ (_| |\ V  V /  | (_| | |_ 
    |_| |_| |_|_|___/ |_|___/  \__,_| |___/_| |_| |_|\__,_|_|_|  \___/_/\_\___\___|_|  | .__/ \__|  \___/|_|    \__,_| | .__/ \__,_|_|_| |_|\__|_|_| |_|\__, | |___| |___/\__,_| \_/\_/    \__,_|\__|
                                                                                       |_|                             |_|                              |___/                                        
                                           _   _            __  __                           _ _  ___                         _         ____            _     
                                          | |_| |__   ___  |  \/  |_   _ ___  ___  ___    __| ( )/ _ \ _ __ ___  __ _ _   _  (_)_ __   |  _ \ __ _ _ __(_)___ 
                                          | __| '_ \ / _ \ | |\/| | | | / __|/ _ \/ _ \  / _` |/| | | | '__/ __|/ _` | | | | | | '_ \  | |_) / _` | '__| / __|
                                          | |_| | | |  __/ | |  | | |_| \__ \  __/  __/ | (_| | | |_| | |  \__ \ (_| | |_| | | | | | | |  __/ (_| | |  | \__ \
                                           \__|_| |_|\___| |_|  |_|\__,_|___/\___|\___|  \__,_|  \___/|_|  |___/\__,_|\__, | |_|_| |_| |_|   \__,_|_|  |_|___/
                                                                                                                      |___/                                   

```

## wildcow.c

```
lukerabbitte@Death-Star:/mnt/c/Users/luker/CLionProjects/NewCowsay/c/build$ ./WildCowsay

                                                              ^__^
                                                              (00)\_______
                                                             (__)\        )\/\
                                                              U   ||----w |
                                                                  ||     ||
                                                    ^__^
                                                    (00)\_______
                                                   (__)\        )\/\
                                                    U   ||----w |
                                                        ||     ||
                                          ^__^
                                          (00)\_______
                                         (__)\        )\/\
                                          U   ||----w |
                                              ||     ||
                                ^__^
                                (00)\_______
                               (__)\        )\/\
                                U   ||----w |
                                    ||     ||
                      ^__^
                      (00)\_______
                     (__)\        )\/\
                      U   ||----w |
                          ||     ||
             ^__^
             (00)\_______
            (__)\        )\/\
             U   ||----w |
                 ||     ||

```

# Exemples de sorties d'automates

```
C:\Windows\system32\wsl.exe --distribution Ubuntu --exec /bin/bash -c "cd /mnt/c/Users/luker/CLionProjects/CowsayAutomaton/cmake-build-debug && /mnt/c/Users/luker/CLionProjects/CowsayAutomaton/cmake-build-debug/CowsayAutomaton"



+++++++++++++++++++++++++++++++++++++++++++++++++
Bienvenue dans le jeu cowsay base sur l'automate
+++++++++++++++++++++++++++++++++++++++++++++++++

Selectionnez un mode de jeu. Le mode Pro necessite des points plus eleves pour gagner un trophee
Pro - Taper 1, Normal - Taper 0:0
 0



++++++++++++++++++++++++++++++
Duree de vie: 0
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 5

Donner la valeur de lunchfood pour la vache:3
3
Digestion is -3
Crop is 1



++++++++++++++++++++++++++++++
Duree de vie: 1
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 3

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -1
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 2
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 5

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -1
Crop is 3



++++++++++++++++++++++++++++++
Duree de vie: 3
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: 8

Donner la valeur de lunchfood pour la vache:5
5
Digestion is -2
Crop is 1



++++++++++++++++++++++++++++++
Duree de vie: 4
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 4

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -1
Crop is -1



++++++++++++++++++++++++++++++
Duree de vie: 5
++++++++++++++++++++++++++++++

-------------------------------
| Too Much Food...Life Sucks! |
|                             |
-------------------------------
        \   ^__^
         \  (.o)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 1

Donner la valeur de lunchfood pour la vache:0
0
Digestion is 0
Crop is -2



++++++++++++++++++++++++++++++
Duree de vie: 6
++++++++++++++++++++++++++++++

-------------------------------
| Too Much Food...Life Sucks! |
|                             |
-------------------------------
        \   ^__^
         \  (.o)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: -1

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -3
Crop is -3



++++++++++++++++++++++++++++++
Duree de vie: 7
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: -4

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -2
Crop is 3



++++++++++++++++++++++++++++++
Duree de vie: 8
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: -1

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -3
Crop is -1



++++++++++++++++++++++++++++++
GAMEOVER
++++++++++++++++++++++++++++++

-----------------------------------
| Not Enough Food...Bye Bye Life! |
|                                 |
-----------------------------------
        \   ^__^         /
         \  (XX)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: -2

++++++++++++++++++++++++++++++
STATISTIQUES
++++++++++++++++++++++++++++++
Score final: 8
  _______
 |       |
(|   3   |)
 |       |
  \     /
   `---'
   _|_|_

Process finished with exit code 0
```

```
C:\Windows\system32\wsl.exe --distribution Ubuntu --exec /bin/bash -c "cd /mnt/c/Users/luker/CLionProjects/CowsayAutomaton/cmake-build-debug && /mnt/c/Users/luker/CLionProjects/CowsayAutomaton/cmake-build-debug/CowsayAutomaton"



+++++++++++++++++++++++++++++++++++++++++++++++++
Bienvenue dans le jeu cowsay base sur l'automate
+++++++++++++++++++++++++++++++++++++++++++++++++

Selectionnez un mode de jeu. Le mode Pro necessite des points plus eleves pour gagner un trophee
Pro - Taper 1, Normal - Taper 0:0
 0



++++++++++++++++++++++++++++++
Duree de vie: 0
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 5

Donner la valeur de lunchfood pour la vache:-331
-331
Lunchfood doit etre >= 0!
Donner la valeur de lunchfood pour la vache:-1
-1
Lunchfood doit etre >= 0!
Donner la valeur de lunchfood pour la vache:6
6
La valeur de Lunchfood depasse le stock actuel. Essayer a nouveau.
Donner la valeur de lunchfood pour la vache:15
15
La valeur de Lunchfood depasse le stock actuel. Essayer a nouveau.
Donner la valeur de lunchfood pour la vache:3
3
Digestion is 0
Crop is -1



++++++++++++++++++++++++++++++
Duree de vie: 1
++++++++++++++++++++++++++++++

-------------------------------
| Too Much Food...Life Sucks! |
|                             |
-------------------------------
        \   ^__^
         \  (.o)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 1

Donner la valeur de lunchfood pour la vache:-1
-1
Lunchfood doit etre >= 0!
Donner la valeur de lunchfood pour la vache:1
1
Digestion is -1
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 2
++++++++++++++++++++++++++++++

-------------------------------
| Too Much Food...Life Sucks! |
|                             |
-------------------------------
        \   ^__^
         \  (.o)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 2

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -3
Crop is -3



++++++++++++++++++++++++++++++
Duree de vie: 3
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: -1

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -1
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 4
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 1

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -1
Crop is -3



++++++++++++++++++++++++++++++
Duree de vie: 5
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: -2

Donner la valeur de lunchfood pour la vache:0
0
Digestion is 0
Crop is -2



++++++++++++++++++++++++++++++
Duree de vie: 6
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: -4

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -1
Crop is 1



++++++++++++++++++++++++++++++
Duree de vie: 7
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: -3

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -2
Crop is 3



++++++++++++++++++++++++++++++
GAMEOVER
++++++++++++++++++++++++++++++

-----------------------------------
| Not Enough Food...Bye Bye Life! |
|                                 |
-----------------------------------
        \   ^__^         /
         \  (XX)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: 0

++++++++++++++++++++++++++++++
STATISTIQUES
++++++++++++++++++++++++++++++
Score final: 7
  _______
 |       |
(|   3   |)
 |       |
  \     /
   `---'
   _|_|_

Process finished with exit code 0
```

```
C:\Windows\system32\wsl.exe --distribution Ubuntu --exec /bin/bash -c "cd /mnt/c/Users/luker/CLionProjects/CowsayAutomaton/cmake-build-debug && /mnt/c/Users/luker/CLionProjects/CowsayAutomaton/cmake-build-debug/CowsayAutomaton"



+++++++++++++++++++++++++++++++++++++++++++++++++
Bienvenue dans le jeu cowsay base sur l'automate
+++++++++++++++++++++++++++++++++++++++++++++++++

Selectionnez un mode de jeu. Le mode Pro necessite des points plus eleves pour gagner un trophee
Pro - Taper 1, Normal - Taper 0:0
 0



++++++++++++++++++++++++++++++
Duree de vie: 0
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 5

Donner la valeur de lunchfood pour la vache:3
3
Digestion is -2
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 1
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 4

Donner la valeur de lunchfood pour la vache:2
2
Digestion is 0
Crop is 1



++++++++++++++++++++++++++++++
Duree de vie: 2
++++++++++++++++++++++++++++++

-------------------------------
| Too Much Food...Life Sucks! |
|                             |
-------------------------------
        \   ^__^
         \  (.o)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 3

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -2
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 3
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 5

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -2
Crop is 3



++++++++++++++++++++++++++++++
Duree de vie: 4
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 6

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -3
Crop is 0



++++++++++++++++++++++++++++++
Duree de vie: 5
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 4

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -2
Crop is 3



++++++++++++++++++++++++++++++
Duree de vie: 6
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 5

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -2
Crop is -2



++++++++++++++++++++++++++++++
Duree de vie: 7
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 1

Donner la valeur de lunchfood pour la vache:1
1
Digestion is -2
Crop is 3



++++++++++++++++++++++++++++++
Duree de vie: 8
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 3

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -1
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 9
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: 3

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -2
Crop is -2



++++++++++++++++++++++++++++++
Duree de vie: 10
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: -1

Donner la valeur de lunchfood pour la vache:0
0
Digestion is 0
Crop is -2



++++++++++++++++++++++++++++++
Duree de vie: 11
++++++++++++++++++++++++++++++

---------------
| Life Rocks! |
|             |
---------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             U ||----w |
                ||     ||

Stock actuel: -3

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -2
Crop is 3



++++++++++++++++++++++++++++++
Duree de vie: 12
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: 0

Donner la valeur de lunchfood pour la vache:0
0
Digestion is 0
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 13
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: 2

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -3
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 14
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: 2

Donner la valeur de lunchfood pour la vache:2
2
Digestion is -1
Crop is -2



++++++++++++++++++++++++++++++
Duree de vie: 15
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: -2

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -1
Crop is 2



++++++++++++++++++++++++++++++
Duree de vie: 16
++++++++++++++++++++++++++++++

---------------------------------
| Not Enough Food...Life Sucks! |
|                               |
---------------------------------
        \   ^__^
         \  (o0)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: 0

Donner la valeur de lunchfood pour la vache:0
0
Digestion is -2
Crop is 2



++++++++++++++++++++++++++++++
GAMEOVER
++++++++++++++++++++++++++++++

-----------------------------------
| Not Enough Food...Bye Bye Life! |
|                                 |
-----------------------------------
        \   ^__^         /
         \  (XX)\_______/
            <__>\-----w-)
              U |      |
                 |     |

Stock actuel: 2

++++++++++++++++++++++++++++++
STATISTIQUES
++++++++++++++++++++++++++++++
Score final: 16
  _______
 |       |
(|   1   |)
 |       |
  \     /
   `---'
   _|_|_

Process finished with exit code 0

```