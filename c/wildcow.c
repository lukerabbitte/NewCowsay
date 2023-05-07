/*

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

 */