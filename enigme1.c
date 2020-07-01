#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonctions.h"
#include "enigmes.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;
    SDL_Rect position;
    int k;

    position.x=0;
    position.y=0;

    SDL_Init(SDL_INIT_VIDEO);                                                 // Initialisation de la SDL
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture de la fenêtre
    if (!screen)
    {
        printf("unable to set 1920x1080 video: %s\n", SDL_GetError());
        return (-1);
    }
    SDL_WM_SetCaption("TEST ENIGMES", NULL);
    k=enigme4(screen);
    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS;
}
