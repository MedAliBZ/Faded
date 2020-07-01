/**
* @file fonctions.h
* @brief all the menu functions
* @author Mohamed Ali Bouzaiene
* @version 0.0.1
*/

#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

typedef struct 
{
    SDL_Surface *text;
    SDL_Rect positiontext;
}texte;

typedef struct 
{
    SDL_Surface *boutton;
    SDL_Rect positionboutton;
}options;




void menu(SDL_Surface *background1,SDL_Surface* screen,SDL_Rect positionbackground,texte* txt,SDL_Surface *play,SDL_Surface *setting,SDL_Surface *quit,SDL_Rect positionplay,SDL_Rect positionsetting,SDL_Rect positionquit,SDL_Surface *credits,SDL_Rect positioncredits);
void menu1(SDL_Surface *background,SDL_Surface* screen,SDL_Rect positionbackground);
/**
* @brief to show the menu
*/
void fleche(int etat,SDL_Surface* screen,SDL_Surface *play,SDL_Surface *quit,SDL_Surface *setting,SDL_Surface *credits,SDL_Surface *quit1,SDL_Surface *setting1,SDL_Surface *play1,SDL_Surface *credits1,SDL_Rect positionplay,SDL_Rect positionquit,SDL_Rect positionsetting,SDL_Rect positioncredits);
/**
* @brief to move with the arrows on the menu
*/
void animation1(SDL_Surface *background3,SDL_Surface* screen,SDL_Rect *position,SDL_Surface *background1,SDL_Rect positionbackground);
/**
* @brief to animate the background
*/
int personnage(SDL_Surface* screen);
/**
* @brief to change the player
*/
int change(SDL_Surface* screen);
/**
* @brief to change the input
*/
//void music(SDL_Surface *screen,SDL_Surface *bout[2],Mix_Music *musique[2]);


#endif
