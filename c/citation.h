#ifndef COWSAY_CITATION_H
#define COWSAY_CITATION_H

void affiche_bordure(int width);
void affiche_citation(char* quote);
void affiche_vache(char* eyes, char* tongue);
void affiche_dragon();
void affiche_pretty_image(char* filename, int width);
void affiche_pretty_citation(char* quote, int width);
int find_width(char* filename);

#endif //COWSAY_CITATION_H
