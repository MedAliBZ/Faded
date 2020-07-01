#ifndef GAMEP_H_INCLUDED
#define GAMEP_H_INCLUDED


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include"ennemy.h"
#include"vie.h"
#include "player.h"
#include "bounding.h"
#include "chrono.h"
#include "scrol.h"


#include "enigmes.h"

#define FPS 10
#define TIME 70
#define GRAVITY 0.3
#define VELOCITY 8

#define TIMEENIGME 10

typedef struct gamep
{
	bool GameOver;
	int sc;
	int time;
	SDL_Surface *background;
	SDL_Surface *backmask;
	int GameEnigme;

	/*PERSONNAGE 1*/

	Ennemy e;
	Vie v;
	Player p;
	Chrono c;
	Scroll cam;
	SDL_Rect pos_real;
	SDL_Rect pos_souris;
	bool collision;
	int colParfait;
	bool kill;

	/*PERSONNAGE 2*/

	Ennemy e1;
	Vie v1;
	Player p1;
	Chrono c1;
	Scroll cam1;
	int GameEnigme1;
	SDL_Rect pos_real1;
	bool collision1;
	int colParfait1;
	bool kill1;

}Gamep;

void Game_Init_Scenep(Gamep* G);
void Game_NewGamep(Gamep* G,SDL_Surface *ecran);
void Game_Load_Scenep(Gamep* G);
void Game_FreeGamep(Gamep* G);
void Game_DisplayGamep(Gamep* G,SDL_Surface *ecran);
void Game_PlayGamep(Gamep* G,SDL_Surface *ecran);
void Game_Input(int key[]);
void Game_Select_Scenep(int * sc);
void Game_UpdateGamep(Gamep* G,int key[],Uint32 dt,SDL_Surface *ecran);
void Game_PlayEnigmep(Gamep* G,SDL_Surface*ecran);

#endif
