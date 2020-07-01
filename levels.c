#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "mvt_souris.h"


int main(int argc, char *argv[])
{
    int a;
    SDL_Surface* screen;

    SDL_Init(SDL_INIT_VIDEO);                                                 // Initialisation de la SDL
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture de la fenêtre
    if (!screen)
    {
        printf("unable to set 1920x1080 video: %s\n", SDL_GetError());
        return (-1);
    }
    SDL_WM_SetCaption("TEST ENIGMES", NULL);
    a=level1(screen);
    if (a==0)
    printf("success\n");
    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS;
}