#ifndef ENNEMY_H_INCLUDED
#define ENNEMY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.h"

typedef enum STATE STATE;
enum STATE{WAITING,FOLLOWING,ATTACKING};


typedef struct 
{
	SDL_Surface *Animation_G[4];
	SDL_Surface *Animation_D[4];
	int Animation;
    SDL_Rect Position;
	bool Direction;
	STATE state;
	int distance;
	int distance_a;
}Ennemy;

void Initialisation_Ennemy(Ennemy *e,SDL_Rect pos);
void Display_Ennemy(Ennemy *e,SDL_Surface *ecran,SDL_Rect pos);
void Animation_Ennemy(Ennemy *e,Player*p);
void Free_Ennemy(Ennemy *e);



#endif
