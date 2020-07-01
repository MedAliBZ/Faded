#ifndef COLLISIONPARFAIT_H_INCLUDED
#define COLLISIONPARFAIT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include"player.h"

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int Collision_Parfait(Player *p,SDL_Surface *backgroundMask);

#endif
