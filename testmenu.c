#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "fonctions.h"
#include "enigmes.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;
    
    int k;
    
    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Ma super fenêtre SDL !", NULL);
    
    // Coloration de la surface ecran en bleu-vert
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17, 206, 112));

    SDL_Flip(screen); /* Mise à jour de l'écran avec sa nouvelle couleur */

    /*k=change(screen);
    k=personnage(screen);*/
    k=enigme4(screen);
    //k=enigme3(screen);
    /*k=enigme2(screen);
    k=enigme1(screen);*/

    SDL_Quit();

    return EXIT_SUCCESS;
}
