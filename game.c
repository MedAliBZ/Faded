#include "game.h"

void Game_Select_Scene(int *sc)
{
	(*sc)++;
}

void Game_Load_Scene(Game *G)
{
	fprintf(stderr, "chargement de la scene \n");
}

void Game_DisplayGame(Game *G, SDL_Surface *ecran)
{
	Scrolling(&(G->cam), G->p.Position, 1000, 600);
	SDL_BlitSurface(G->background, &(G->cam.scroll), ecran, NULL);

	Display_Chrono(&(G->c), ecran);

	if (!G->kill)
	{
		Display_Ennemy(&(G->e), ecran, G->pos_real);
	}

	SDL_Rect position = {650, 0};
	Display_Vie(&(G->v), ecran, position);
	if (G->p.Attack == 0)
	{
		if (G->p.Etat_Mv || G->p.Etat_MvC)
		{
			Display_Player(&(G->p), ecran, G->cam.pos_real);
		}
		else
		{
			Animation_Player(&(G->p), ecran, G->cam.pos_real);
		}
	}
	else
	{
		Attack_Player(&(G->p), ecran, G->cam.pos_real);
	}

	//Display_Player(&(G->p),ecran);
	Display_MiniMap(&(G->m), ecran);

	SDL_Flip(ecran);
}

void Game_Init_Scene(Game *G)
{
	TTF_Init(); //initialisation de TTF
	G->GameOver = 0;
	G->sc = 0;
	G->collision = false;
	G->colParfait = false;
	G->kill = false;
	G->GameEnigme = 0;

	G->background = IMG_Load("img/back.jpg");
	G->backmask = IMG_Load("img/backmask.jpg");

	SDL_Rect position = {2000, 300, 100, 100};
	G->pos_real = position;
	Initialisation_Ennemy(&(G->e), position);

	Init_Vie(&(G->v));

	SDL_Rect pos = {500, 150, 50, 120};
	Initialisation_Player(&(G->p), pos);

	Initialisation_Scroll(&(G->cam), G->p.Position, 1000, 600);

	SDL_Rect positionC = {50, 0};
	Init_Chrono(&(G->c), positionC, TIME);
	Init_MiniMap(&(G->m), &(G->p));

	if (G->loadgame)
	{
		FILE *f = fopen("save.bin", "rb");
		if (f != NULL)
		{
			Game_Load_Game(G, f);
		}
	}
}

void Game_PlayGame(Game *G, SDL_Surface *ecran)
{
	Uint32 t_prev, dt = 1;

	int key[322] = {0};

	bool enigme = true;

	Game_DisplayGame(G, ecran);
	SDL_EnableKeyRepeat(5, 5);
	while (G->GameOver == 0)
	{
		t_prev = SDL_GetTicks();

		Game_UpdateGame(G, dt, ecran);

		Game_DisplayGame(G, ecran);

		if ((G->p.Position.x < 7800 && G->p.Position.x > 7000) && enigme)
		{
			Game_PlayEnigme(G, ecran);
			enigme = false;
			if (G->GameEnigme != 1)
			{
				G->GameOver = 1; //gameover
				printf("gameover\n");
			}
			if (G->GameOver == 0)
			{
				ecran = SDL_SetVideoMode(321, 321, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
				bool checkXO;

				checkXO = Play_Xo(ecran);
				if (!checkXO)
				{
					G->GameOver = 1;
				}
				ecran = SDL_SetVideoMode(1000, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
			}
		}

		dt = SDL_GetTicks() - t_prev;
		SDL_Delay(1000 / FPS);

		//FPS=10; kol 1/10 seconde todhhor taswira
	}
}

void Game_UpdateGame(Game *G, Uint32 dt, SDL_Surface *ecran)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONUP:
		{
			if (G->cntrl == 2)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					G->p.Etat_Mv = true;
					G->p.Etat_MvC = false;
					G->pos_souris.x = event.motion.x + G->cam.scroll.x;
					G->pos_souris.y = event.motion.y;
				}
			}

			break;
		}
		case SDL_KEYDOWN:
		{
			if (G->cntrl == 0)
			{
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					fprintf(stderr, " right \n");
					G->p.Etat_Mv = false;
					G->p.Etat_MvC = true;
					G->p.Direction = true;
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					fprintf(stderr, " left \n");
					G->p.Etat_Mv = false;
					G->p.Etat_MvC = true;
					G->p.Direction = false;
				}
			}
			if (G->cntrl == 1)
			{
				if (event.key.keysym.sym == SDLK_d)
				{
					fprintf(stderr, " right \n");
					G->p.Etat_Mv = false;
					G->p.Etat_MvC = true;
					G->p.Direction = true;
				}
				else if (event.key.keysym.sym == SDLK_q)
				{
					fprintf(stderr, " left \n");
					G->p.Etat_Mv = false;
					G->p.Etat_MvC = true;
					G->p.Direction = false;
				}
			}
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				fprintf(stderr, " jump \n");
				G->p.Jump = 1;
				if (G->p.Direction)
				{
					G->p.Position.y -= VELOCITY * 0.8 * dt;
					G->p.Position.x += VELOCITY * 0.2 * dt;
				}
				else
				{
					G->p.Position.y -= VELOCITY * 0.8 * dt;
					G->p.Position.x -= VELOCITY * 0.2 * dt;
				}
				G->p.Jump = 0;

				G->p.Ground = false;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				fprintf(stderr, " pause \n");
				//Pause_Chrono(&(G->c));
				bool menu = true;
				menu = Game_Menu_Save(&(G->s), G, ecran);
				//Sauvgarde
			}
			else if (event.key.keysym.sym == SDLK_RETURN)
			{

				G->p.Attack = 1;
				//Sauvgarde
			}

			break;
		}
		case SDL_QUIT:
		{
			Game_FreeGame(G);
			break;
		}
		}
	}

	G->colParfait = Collision_Parfait(&(G->p), G->backmask);

	if (G->colParfait == 1)
	{
		fprintf(stderr, " parfait \n");
		if (G->p.Direction)
		{
			G->p.Position.x -= G->p.vitesse;
		}
		else
		{
			G->p.Position.x += G->p.vitesse;
		}
		G->colParfait = 0;
	}

	if (G->p.Etat_Mv)
	{
		DeplacementPlayer(&(G->p), G->pos_souris);
	}
	if (G->p.Etat_MvC)
	{
		DeplacementPlayerC(&(G->p), dt);
	}

	if (!(G->p.Etat_MvC) && !(G->p.Etat_Mv))
	{
		G->p.vitesse = 0;
	}

	if (!G->kill)
	{
		G->collision = collision(G->cam.pos_real, G->pos_real);
		Animation_Ennemy(&(G->e), &(G->p));
		G->pos_real.x = G->e.Position.x - G->cam.scroll.x;
		G->pos_real.y = G->e.Position.y;
	}

	if (G->collision && G->p.Attack == 1)
	{
		fprintf(stderr, " kill \n");
		G->kill = true;
		G->collision = false;
	}

	if (G->collision && G->p.Attack == 0)
	{
		fprintf(stderr, " coll \n");
		G->collision = false;
		if (G->p.Direction)
		{
			G->p.Position.x -= 50;
		}
		else
		{
			G->p.Position.x += 50;
		}
		Calcul_Vie(&(G->v));
	}

	if (!(G->c.pause))
	{
		if (!Calcul_Chrono(&(G->c)))
		{
			G->GameOver = 1;
		}
	}

	if (G->p.Ground == 0)
	{
		fprintf(stderr, " fall \n");
		G->p.Position.y += GRAVITY * dt * dt;
	}

	if (!(G->v.survie))
	{
		G->GameOver = 1; //GameOver
	}

	Update_MiniMap(&(G->m), &(G->p));
}

void Game_NewGame(Game *G, SDL_Surface *ecran)
{

	printf("init secene");
	Game_Init_Scene(G);
	do
	{
		printf("Select secene");
		Game_Select_Scene(&(G->sc));

		printf("load scene");
		Game_Load_Scene(G);

		printf("play");
		Game_PlayGame(G, ecran);
	} while (G->GameOver == 0);
	Game_FreeGame(G);
}

void Game_PlayEnigme(Game *G, SDL_Surface *ecran)
{
	ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	//G->GameEnigme = enigme1(ecran);
	if (G->GameEnigme = enigme1(ecran) == 1)
	{
		if (G->GameEnigme = enigme2(ecran) == 1)
		{
			if (G->GameEnigme = enigme3(ecran) == 1)
			{
				if (G->GameEnigme = enigme4(ecran) == 1)
					printf("you passed\n");
			}
		}
	}
	ecran = SDL_SetVideoMode(1000, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

void Game_FreeGame(Game *G)
{
	fprintf(stderr, "free game \n");
	Free_Ennemy(&(G->e));
	Free_vie(&(G->v));
	Free_Player(&(G->p));
}

bool Game_Menu_Save(SaveG *s, Game *G, SDL_Surface *ecran)
{
	Init_Save(s);
	SDL_Event event1;
	bool continuer = true;
	SDL_EnableKeyRepeat(0, 0);
	while (continuer)
	{
		Display_Save(s, ecran);
		while (SDL_PollEvent(&event1))
		{
			switch (event1.type)
			{
			case SDL_KEYDOWN:
			{
				if (event1.key.keysym.sym == SDLK_RIGHT)
				{
					s->image_courrante++;
				}
				else if (event1.key.keysym.sym == SDLK_LEFT)
				{
					s->image_courrante--;
				}
				else if (event1.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_EnableKeyRepeat(5, 5);
					return false;
				}
				if (event1.key.keysym.sym == SDLK_RETURN)
				{
					G->GameOver = 1;
					if (s->image_courrante == 1)
					{
						return false;
					}
					else if (s->image_courrante == 2)
					{
						Save_Game(G);
						return false;
					}
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
				printf("Souris en position %d %d\n", event1.motion.x, event1.motion.y);
			}
			case SDL_MOUSEBUTTONUP:
			{

				if ((event1.motion.x > 391 && event1.motion.x < 487) && (event1.motion.y > 313 && event1.motion.y < 368))
				{
					s->image_courrante = 1;
					if (event1.button.button == SDL_BUTTON_LEFT)
					{
						G->GameOver = 1;
						return false;
					}
				}
				else if ((event1.motion.x > 487 && event1.motion.x < 614) && (event1.motion.y > 313 && event1.motion.y < 368))
				{
					s->image_courrante = 2;
					if (event1.button.button == SDL_BUTTON_LEFT)
					{
						G->GameOver = 1;
						Save_Game(G);
						return false;
					}
				}
				else if ((event1.motion.x > 474 && event1.motion.x < 527) && (event1.motion.y > 394 && event1.motion.y < 418))
				{
					if (event1.button.button == SDL_BUTTON_LEFT)
					{
						SDL_EnableKeyRepeat(5, 5);
						return false;
					}
				}
				break;
			}
			}
		}
		if (s->image_courrante < 1)
		{
			s->image_courrante = 2;
		}
		if (s->image_courrante > 2)
		{
			s->image_courrante = 1;
		}
	}
}

void Save_Game(Game *G)
{
	FILE *f = fopen("save.bin", "wb");
	fwrite(G, sizeof(Game), 1, f);
	fclose(f);
}

void Game_Load_Game(Game *G, FILE *f)
{
	Game tmp;
	fread(&tmp, sizeof(Game), 1, f);

	G->sc = tmp.sc;
	G->collision = false;
	G->colParfait = false;
	G->kill = tmp.kill;
	G->GameEnigme = tmp.GameEnigme;

	SDL_Rect position = {2000, 300, 100, 100};
	G->pos_real = position;
	Initialisation_Ennemy(&(G->e), position);

	Init_Vie(&(G->v));

	SDL_Rect pos = {500, 150, 50, 120};
	Initialisation_Player(&(G->p), pos);

	SDL_Rect positionC = {50, 0};
	Init_Chrono(&(G->c), positionC, TIME);

	G->e.Position = tmp.e.Position;
	G->p.Position = tmp.p.Position;
	G->p.Direction = tmp.p.Direction;
	G->v.vie = tmp.v.vie;
	G->c.counter = tmp.c.counter;
	Initialisation_Scroll(&(G->cam), G->p.Position, 1000, 600);
	fclose(f);
}
