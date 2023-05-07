#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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