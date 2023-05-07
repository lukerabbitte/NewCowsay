# INF203 Projet Luke Rabbitte

# Intro

The cowsay program displays a message or
quote on the screen, by having it said by an ASCII
ASCII cow or other ASCII animal.

The user can specify the text to make the animal say
by passing it as a command line argument or by entering it
line argument or by entering it via the
input.

The cowsay program can also support several options for
The cowsay program can also support several options for customising the
output, such as the use of speech bubbles, selection of an
quote bubbles, selection of a specific avatar
etc.

Finally, cowsay is used in a playful way
to add a touch of humour to programmes.

In the next three sections, I will discuss
my code choices for my bash scripts, my c programs
c programs and my automata-based game,
respectively.

# Bash

## cow_kindergarten.sh
Very simply here I implemented a for loop `for i in {1..10}`.

I also used the following commands for the
first time, they will show up quite a lot.

`cowsay $i;
 sleep 1;
 clear;
`

Full code:

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

Very similar to previous.

Full code:

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

Like before.

Full code:

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

I had to spend some time debugging this, only to
realise that cowsay doesn't like being told to output
'0'. As seen in my comments, I found that piping
an echo command to cowsay solved the issue.

Otherwise, just implementing basic fibonacci logic.

Full code:

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

Use modulo arithmetic with two inner loops to determine
whether number is prime. Track with boolean
is_prime.

Full code:

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

Instead of using bc or other easier solutions, I
took some of the concepts learned in class, as well
as doing some extra reading on regular expressions,
to split the given argument into `operand1`,
`operator` and `operand2`.

Once this was handled, I was able to perform
if-else checks and echo the result.

I had some problems with figuring out how to
handle multiplication, as `*` is a special character
in bash. In the end, I found a solution whereby
the variable holding `operator` is initialised
with an escape character '\'.

Note: the result will only be printed to the
cow's eyes if its absolute value is less than
100, i.e, it is two digits.

Full code:

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

Originally I was investigating generating some
interesting sequences from number theory.

One of which was the sequence of **perfect
numbers**,
positive integers that are equal to the sum of
their proper divisors, excluding the
number itself.

The code for this first attempt can be
found here:

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
This used a variable `perfect_numbers_found` to
keep track. Interested in analysing the time
complexity, I timed the execution of the
program, and got cowsay to print both the perfect
number found, and the time it took to find it,
during its output.

What I found is that it became incredibly slow
after the first three perfect numbers were
found.

Finding the 4th took ~11 minutes, and I didn't
feel like waiting around long enough for the
5th!

In any case, I realised that this was perhaps
not the most user friendly utility, owing to
its time complexity.

So, in the end, I decided to implement a
**factorial calculator**. The user inputted
`n` is multiplied by `n-1`,
`n-2`, etc... until it is multiplied by `1`.

Full code:

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

My C program lets the user call with the
following flags:

```
-e <custom eye string> 'My cowsay message' 
-T <custom tongue string> 'My cowsay message' 
-d 'My cowsay message'
-p <desired ASCII art width> <image_path> 'My cowsay message' 
```

`-e` and `-t` are straightforward, letting the user
customise the cowsay cow.

`-d` replaces a standard cowsay cow with a dragon.

`-p` is the most interesting flag. It 'pretty prints' a custom
ASCII artwork which prints a given image in ASCII art at a given
width, then below concatenates an ASCII banner.

I had the idea when looking back through my camera roll
and finding I had an actual picture of a cow that I
had taken on holidays in Dunmore East in Ireland. I thought
it would be very interesting to get a real cow
to say something!
 
I achieved this using the jp2a and figlet libraries, respectively.

Note that it works best when directed towards an
output file as in`> output.txt`. If a great enough
width is selected, the generated text will be
quite large, and will need to be viewed after
zooming out quite far.

The `newcow.c` is simply the main file for handling user input
and calling the relevant functions. Most of the functionality
is in `citation.c` with some constants stored in
`constants.c`. The .h file of both of these is imported into
`newcow.c`

My full `newcow.c` code is here:

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

Now here is the code for `citation.c`:

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

`affiche_bordure(int width)` prints a border given a certain width.
It can print whatever the constant `BORDER_CHAR` is assigned.

`affiche_citation(char* quote)` prints the speech bubble according to a given
width, keeping its place in the input string according
to the width multiplied by the line count.

`affiche_vache()` prints cowsay cow with two custom arguments.

`affiche_dragon()` does the same with a dragon avatar.

`affiche_pretty_image(char* filename, int width)`
uses system(command) via a buffer to call the library
jp2a, which converts an image to ASCII art.

`affiche_pretty_citation(char* quote, int width)`
uses system(command) via a buffer to call figlet,
and produce an ASCII banner according to given width.

`find_width(char* filename)` finds the width of the
first line of a file.

The constants are defined within `constants.c` as follows:

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

## Other C files

Elsewhere, I have `wildcow.c` which uses the `update`
and `goto` functions as specified. `animer_vache()`
is called with a user specified frame rate such
as 0.5 seconds or 1.2 seconds.

This is the speed at which the animation changes.

This then makes a call to `affiche_vache_animee(int frame_increment)`
which prints the cow at different x and y coordinates
along the terminal. The idea with the example values
given is that the cow walks from the top right to
the bottom left of the terminal screen.

This is the full `wildcow.c` code:

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

Lastly, I have the file `reading_cow.c` which for now is
still of a skeletal form:

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

I was using CLion Windows from a WSL virtual machine. Although
I learned a lot about makefiles and, in particular,
the CMake Application, I had some major difficulties
in trying to work on this file in particular.

# Automaton

This was the implementation of the cowsay game which
represents different stages of a cow's hunger, and
carries us between states based on functions which
call random number generators.

I had some problems working out the finer details of logic
based on the brief game description. For example, for 
a while I assumed that the game should end when the
food supply drops below 0. However, I soon realised
when testing that you still have a chance of surviving
even if this happens.

I decided to represent more accurate and detailed states
according to the cow's fitness level than given in the
project description. This included managing 5 states
instead of 3. In my implementation, there is a cow
for `lifesucks` 'hungry' state as well as the
`lifesucks` 'overfed' state.

I use a simplified `citation.c` file called
`bulle_citation.c` to generate the quotations:

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

The main flow of the game is controlled within
`tamagoshi_cow.c`:

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
`affiche_vache(int fitness)` prints the cow according to an integer fitness value.

`affiche_trophee(int position)` takes the user's final score
and prints an ASCII trophy with their position on the
podium (either 1, 2, or 3). The points required
to get a trophy at these levels changes based upon
whether the user selected normal or pro mode at the beginning!

`int fitness_update(int lunchfood_fitness)` and
`int stock_update(int lunchfood_stock)` are implemented
as required.

`int main()` performs a lot of user input error handling,
for example not letting the user enter a value of
`lunchfood` greater than what is
available in `stock`.

At the end of the game, statistics are shown along with
a trophy and podium position, if the user reached the required
point level.

# Summary

Overall, I learned a lot about tooling and project structure
in the c language, as well as getting a lot more familiar
with bash, and the very useful libraries available to those
developing with it.

I tried wherever possible to improve readability by
leaving comments and by avoiding clutter in main program
flow files, instead setting up separate files to store
constants and auxiliary functions.

This required constant thought about readability and
design.

Many of the ideas I worked with here have inspired further
thinking about ways to improve. For example, the random
numbers generated for the cowsay game are still
somewhat deterministic, being based on the time. If I
had more time, I would love to investigate using
true random number generators such as those offered
by random.org through their API.

I spent about a day coming up with and
implementing the ASCII art and
banner generator. This is what I am most proud of as
it is always nice to show some visual output to others.
I would love to study ASCII art generation and the 
mathematics of image processing more, in particular
the steps of preprocessing and luminance detection
that I imagine are involved in the libraries I used.

# Annex: Sample Interactions

# Bash Sample Outputs

## cow_kindergarten.sh

`./cow_kindergarten.sh`

This produces a series of cows terminating in the following:

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

## crazy_cow.sh (initial version with perfect numbers)

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

# C Sample Outputs

## newcow.c

Note `newcow.c` uses functions from `citation.c` and
constants from `constants.c` aswell.

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

# Automaton Sample Outputs

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