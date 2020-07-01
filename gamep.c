#include "gamep.h"


void Game_Select_Scenep(int* sc)
{
	(*sc)++;
}

void Game_Load_Scenep(Gamep* G)
{ 
	fprintf(stderr,"chargement de la scene \n");
}

void Game_DisplayGamep(Gamep* G,SDL_Surface *ecran)
{
	Scrolling(&(G->cam),G->p.Position,500,600);
	SDL_BlitSurface(G->background,&(G->cam.scroll),ecran,NULL);
	Display_Chrono(&(G->c),ecran);
	if(!G->kill)
	{
		Display_Ennemy(&(G->e),ecran,G->pos_real);
	}
    SDL_Rect position={200,0};
    Display_Vie(&(G->v),ecran,position);
    if(G->p.Attack==0)
    {
    if(G->p.Etat_Mv ||G->p.Etat_MvC)
	{
		Display_Player(&(G->p),ecran,G->cam.pos_real);
	}
	else
	{
		Animation_Player(&(G->p),ecran,G->cam.pos_real);

	}
	}
	else
	{
		Attack_Player(&(G->p),ecran,G->cam.pos_real);
	}

	/**********************/

	Scrolling(&(G->cam1),G->p1.Position,500,600);
	SDL_Rect posblit={500,0};
	
	SDL_BlitSurface(G->background,&(G->cam1.scroll),ecran,&posblit);
	Display_Chrono(&(G->c1),ecran);
	if(!G->kill1)
	{
		Display_Ennemy(&(G->e1),ecran,G->pos_real1);
	}
    SDL_Rect position1={650,0};
    Display_Vie(&(G->v1),ecran,position1);
    G->cam1.pos_real.x+=500;
    if(G->p1.Attack==0)
    {
    if(G->p1.Etat_Mv ||G->p1.Etat_MvC)
	{
		Display_Player(&(G->p1),ecran,G->cam1.pos_real);
	}
	else
	{
		Animation_Player(&(G->p1),ecran,G->cam1.pos_real);

	}
	}
	else
	{
		Attack_Player(&(G->p1),ecran,G->cam1.pos_real);
	}





    SDL_Flip(ecran);
}

void Game_Init_Scenep(Gamep* G)
{ 
	TTF_Init();//initialisation de TTF
	G->GameOver=0;
	G->sc=0;
	G->collision=false;
	G->colParfait=false;
	G->kill=false;
	G->GameEnigme=0;
	G->background=IMG_Load("img/back.jpg");
	G->backmask=IMG_Load("img/backmask.jpg");
	SDL_Rect position={2000,300,100,100};
	G->pos_real=position;
	Initialisation_Ennemy(&(G->e),position);
	Init_Vie(&(G->v));
	SDL_Rect pos={500,150,50,120};
	Initialisation_Player(&(G->p),pos);
	Initialisation_Scroll(&(G->cam),G->p.Position,500,600);
	SDL_Rect positionC={50,0};
	Init_Chrono(&(G->c),positionC,TIME);

	/****************/

	G->collision1=false;
	G->colParfait1=false;
	G->kill1=false;
	G->GameEnigme1=0;
	SDL_Rect position1={3500,300,100,100};
	G->pos_real1=position1;
	Initialisation_Ennemy(&(G->e1),position1);
	Init_Vie(&(G->v1));
	SDL_Rect pos1={500,150,50,120};
	Initialisation_Player(&(G->p1),pos1);
	Initialisation_Scroll(&(G->cam1),G->p1.Position,500,600);
	SDL_Rect positionC1={500,0};
	Init_Chrono(&(G->c1),positionC1,TIME);

}


void Game_PlayGamep(Gamep* G,SDL_Surface *ecran)
{
	Uint32 t_prev,dt=1;

	int key[322]={0};

	bool enigme=true;

	Game_DisplayGamep(G,ecran);
	SDL_EnableKeyRepeat(5,5);
	while(G->GameOver==0)
    {  
    	t_prev=SDL_GetTicks();
    	

        Game_UpdateGamep(G,key,dt,ecran);
        
      	Game_DisplayGamep(G,ecran);

      	if( ((G->p.Position.x<7800 && G->p.Position.x>7000) || (G->p1.Position.x<7800 && G->p1.Position.x>7000)) && enigme)
      	{
      		Game_PlayEnigmep(G,ecran);
      		enigme=false;		
			if(G->GameEnigme!=1){
				G->GameOver=1;//gameover
				printf("gameover\n");
			}
      	}
      	

      	dt=SDL_GetTicks()-t_prev;
		SDL_Delay(1000/FPS);	

		//FPS=10; kol 1/10 seconde todhhor taswira 
		
    }
}

void Game_Input(int key[])
{
	SDL_Event event;
    SDL_EnableKeyRepeat(5,5);

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		key[event.key.keysym.sym]=1;
		break;
	case SDL_KEYUP:
		key[event.key.keysym.sym]=0;
		break;
	default:
		break;
	}
}

void Game_UpdateGamep(Gamep* G,int key[],Uint32 dt,SDL_Surface *ecran)
{   
	Game_Input(key);
	if(key[SDLK_RIGHT]==1)
	{
		fprintf(stderr," right \n");
		G->p.Etat_Mv=false;
		G->p.Etat_MvC=true;
		G->p.Direction=true;
	}
	Game_Input(key);
	if(key[SDLK_LEFT]==1)
	{
		fprintf(stderr," left \n");
		G->p.Etat_Mv=false;
		G->p.Etat_MvC=true;
		G->p.Direction=false;
	}
	Game_Input(key);
	if(key[SDLK_SPACE]==1)
	{
		fprintf(stderr," jump \n");
		G->p.Jump=1;
		if(G->p.Direction)
		{
			G->p.Position.y-=VELOCITY*0.8*dt;
			G->p.Position.x+=VELOCITY*0.2*dt;
		}
		else
		{
			G->p.Position.y-=VELOCITY*0.8*dt;
			G->p.Position.x-=VELOCITY*0.2*dt;
		}
		G->p.Jump=0;
		
		G->p.Ground=false;
	}
	Game_Input(key);
	if(key[SDLK_RETURN]==1)
	{
		
		G->p.Attack=1;
		//Sauvgarde
	}
	Game_Input(key);
	if(key[SDLK_d]==1)
	{
		fprintf(stderr," right \n");
		G->p1.Etat_Mv=false;
		G->p1.Etat_MvC=true;
		G->p1.Direction=true;
	}
	Game_Input(key);
	if(key[SDLK_q]==1)
	{
		fprintf(stderr," left \n");
		G->p1.Etat_Mv=false;
		G->p1.Etat_MvC=true;
		G->p1.Direction=false;
	}
	Game_Input(key);
	if(key[SDLK_z]==1)
	{
		fprintf(stderr," jump \n");
		G->p1.Jump=1;
		if(G->p1.Direction)
		{
			G->p1.Position.y-=VELOCITY*0.8*dt;
			G->p1.Position.x+=VELOCITY*0.2*dt;
		}
		else
		{
			G->p1.Position.y-=VELOCITY*0.8*dt;
			G->p1.Position.x-=VELOCITY*0.2*dt;
		}
		G->p1.Jump=0;
		
		G->p1.Ground=false;
	}
	Game_Input(key);
	if(key[SDLK_s]==1)
	{
		
		G->p1.Attack=1;
		
	}
	Game_Input(key);
	if(key[SDLK_ESCAPE]==1)
	{
		fprintf(stderr," quit \n");
		G->GameOver=1;
		//Sauvgarde
	}



	/******************************************************************/
	if(G->p.Position.y>400){
    	G->p.Position.y=400;
    }
    if(G->p.Position.y<10){
    	G->p.Position.y=10;
    }

	G->colParfait=Collision_Parfait(&(G->p),G->backmask);
	if(G->colParfait==1)
	{
		fprintf(stderr," parfait \n");
		if(G->p.Direction)
		{
			G->p.Position.x-=G->p.vitesse;
		}
		else
		{
			G->p.Position.x+=G->p.vitesse;
		}
		G->colParfait=0;
	}
	if(G->p.Etat_Mv)
	{
		DeplacementPlayer(&(G->p),G->pos_souris);
	}
	if(G->p.Etat_MvC)
	{
		DeplacementPlayerC(&(G->p),dt);
	}
	if(!(G->p.Etat_MvC) && !(G->p.Etat_Mv))
	{
		G->p.vitesse=0;
	}
	if(!G->kill)
	{
		G->collision=collision (G->cam.pos_real,G->pos_real);
		Animation_Ennemy(&(G->e),&(G->p));
		G->pos_real.x=G->e.Position.x-G->cam.scroll.x;
		G->pos_real.y=G->e.Position.y;
	}
	if(G->collision && G->p.Attack==1)
	{
		fprintf(stderr," kill \n");
		G->kill=true;
	}
	if(G->collision)
	{
		fprintf(stderr," coll \n");
		G->collision=false;
		if(G->p.Direction)
		{
			G->p.Position.x-=50;
		}
		else
		{
			G->p.Position.x+=50;
		}
		Calcul_Vie(&(G->v));
	}
	if(G->p.Ground==0)
	{
		fprintf(stderr," fall \n");
		G->p.Position.y+=GRAVITY*dt*dt;
	}
    if(!(G->c.pause) && !(G->c1.pause))
	{
		if((!Calcul_Chrono(&(G->c))) || (!Calcul_Chrono(&(G->c1))))
		{
			G->GameOver=1;
		}
	}
    if((!(G->v.survie))|| (!(G->v1.survie)))
    {
    	G->GameOver=1;//GameOver
    }
    

    /******************************************************************/


    if(G->p1.Position.y>400){
    	G->p1.Position.y=400;
    }
    if(G->p1.Position.y<10){
    	G->p1.Position.y=10;
    }
    G->colParfait1=Collision_Parfait(&(G->p1),G->backmask);
	if(G->colParfait1==1)
	{
		fprintf(stderr," parfait \n");
		if(G->p1.Direction)
		{
			G->p1.Position.x-=G->p1.vitesse;
		}
		else
		{
			G->p1.Position.x+=G->p1.vitesse;
		}
		G->colParfait1=0;
	}
	/*if(G->p1.Etat_Mv)
	{
		DeplacementPlayer(&(G->p1),G->pos_souris);
	}*/
	if(G->p1.Etat_MvC)
	{
		DeplacementPlayerC(&(G->p1),dt);
	}
	if(!(G->p1.Etat_MvC) && !(G->p1.Etat_Mv))
	{
		G->p1.vitesse=0;
	}
	if(!G->kill1)
	{
		G->collision1=collision (G->cam1.pos_real,G->pos_real1);
		Animation_Ennemy(&(G->e1),&(G->p));
		G->pos_real1.x=G->e1.Position.x-G->cam1.scroll.x;
		G->pos_real1.y=G->e1.Position.y;
	}
	if(G->collision1 && G->p1.Attack==1)
	{
		fprintf(stderr," kill \n");
		G->kill1=true;
	}
	if(G->collision1)
	{
		fprintf(stderr," coll \n");
		G->collision1=false;
		if(G->p1.Direction)
		{
			G->p1.Position.x-=50;
		}
		else
		{
			G->p1.Position.x+=50;
		}
		Calcul_Vie(&(G->v1));
	}
	if(G->p1.Ground==0)
	{
		fprintf(stderr," fall \n");
		G->p1.Position.y+=GRAVITY*dt*dt;
	}
	

}


void Game_NewGamep(Gamep* G,SDL_Surface *ecran)
{

	printf ("init secene");
	Game_Init_Scenep(G);
	do
	{
		printf ("Select secene");
		Game_Select_Scenep(&(G->sc));

		printf ("load scene");
		Game_Load_Scenep(G);

		printf ("play");
		Game_PlayGamep(G,ecran);
	}
	while (G->GameOver==0);
	Game_FreeGamep(G);
}

void Game_PlayEnigmep(Gamep* G,SDL_Surface*ecran)
{	
	ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    G->GameEnigme=enigme1(ecran);
	ecran = SDL_SetVideoMode(1000, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
}



void Game_FreeGamep(Gamep* G)
{ 
	fprintf(stderr,"free game \n"); 
	Free_Ennemy(&(G->e));
	Free_vie(&(G->v)); 
	Free_Player(&(G->p));
}

