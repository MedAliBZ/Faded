#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include"ennemy.h"
#include"vie.h"
#include "player.h"
#include "bounding.h"
#include "chrono.h"
#include "scrol.h"
#include "savegame.h"


#include "enigmes.h"
#include "minimap.h"
#include "xo.h"

#define FPS 10
#define TIME 70
#define GRAVITY 0.3
#define VELOCITY 8

#define TIMEENIGME 10

typedef struct game
{
	Ennemy e;
	Vie v;
	Player p;
	Chrono c;
	Scroll cam;
	//Enigme En;
	int GameEnigme;
	SaveG s;
	Minimap m;
	
	int sc;
	int time;
	bool loadgame;
	int cntrl;

	SDL_Rect pos_real;
	SDL_Surface *background;
	SDL_Surface *backmask;
	SDL_Rect pos_souris;

	bool GameOver;

	bool collision;
	int colParfait;
	bool kill;
}Game;

void Game_Init_Scene(Game* G);
void Game_NewGame(Game* G,SDL_Surface *ecran);
void Game_Load_Scene(Game* G);
void Game_FreeGame(Game* G);
void Game_DisplayGame(Game* G,SDL_Surface *ecran);
void Game_PlayGame(Game* G,SDL_Surface *ecran);
void Game_Select_Scene(int * sc);
void Game_UpdateGame(Game* G,Uint32 dt,SDL_Surface *ecran);
void Game_PlayEnigme(Game* G,SDL_Surface*ecran);

bool Game_Menu_Save(SaveG *s,Game*G,SDL_Surface*ecran);
void Save_Game(Game *G);
void Game_Load_Game(Game *G,FILE *f);

#endif
