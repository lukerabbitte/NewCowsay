#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citation.h"
#include "constants.h"

void update () {
    printf (" \033[ H \033[ J");
}

void gotoxy (int x , int y) {
    printf (" \033[% d;% dH",x , y );
}

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

        else if (strcmp(argv[i], "-D") == 0 && i < argc) {
            strcpy(avatar, "dragon");
        }

        else if (strcmp(argv[i], "-P") == 0 && i < (argc - 1)) {
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

    return 0;
}