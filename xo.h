#ifndef XO_H_INCLUDED
#define XO_H_INCLUDED

#include <SDL/SDL.h>
#include <stdbool.h>
typedef struct
{
    SDL_Surface* xoS;
    SDL_Rect xoR[4][4];
    SDL_Rect posxo[3];
    int tab[4][4];

    int tour;
    int winner;

}Xo;

void Init_Xo(Xo *xo);

int Checkwin_Xo(Xo *xo);

void Put_Xo(Xo* xo,int x,int y);

void Random_Xo(Xo *xo);

void Diplay_Xo(Xo* xo,SDL_Surface* ecran);

void Free_Xo(Xo *xo);

bool Play_Xo(SDL_Surface *ecran);

#endif // XO_H_INCLUDED
