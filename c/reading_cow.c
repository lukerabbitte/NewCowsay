/*

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

 */