#ifndef VIE_H_INCLUDED
#define VIE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct 
{
	SDL_Surface *Barre[4];
	int vie;
	bool survie;
}Vie;

void Init_Vie(Vie *v);
void Calcul_Vie(Vie *v);
void Display_Vie(Vie *v,SDL_Surface*ecran,SDL_Rect position);
void Free_vie(Vie *v);



#endif
