#include "ennemy.h"

void Initialisation_Ennemy(Ennemy *e,SDL_Rect pos)
{

	e->Position.x=pos.x;
	e->Position.y=pos.y;

	e->Direction=true;
	e->Animation=1;
	e->state=WAITING;
	e->distance=400;
	e->distance_a=100;

	e->Animation_D[1]=IMG_Load("img/ennemy/ed1.png");
	e->Animation_D[2]=IMG_Load("img/ennemy/ed2.png");
	e->Animation_D[3]=IMG_Load("img/ennemy/ed3.png");

	e->Animation_G[1]=IMG_Load("img/ennemy/eg1.png");
	e->Animation_G[2]=IMG_Load("img/ennemy/eg2.png");
	e->Animation_G[3]=IMG_Load("img/ennemy/eg3.png");
}
void Display_Ennemy(Ennemy *e,SDL_Surface *ecran,SDL_Rect pos)
{
	if(e->Direction)
	{
		SDL_BlitSurface(e->Animation_D[e->Animation], NULL, ecran, &pos);	
		SDL_Flip(ecran);
	}
	else
	{
		SDL_BlitSurface(e->Animation_G[e->Animation], NULL, ecran, &pos);
		SDL_Flip(ecran);
	}
}

void Animation_Ennemy(Ennemy *e,Player*p)
{
	int dist =p->Position.x - e->Position.x;
	if( (dist>0) && (dist< e->distance))
	{
		e->state=FOLLOWING;
	}
	else if ((dist<0) && (dist > (- e->distance) ))
	{
		e->state=FOLLOWING;
	}
	else
	{
		e->state=WAITING;	
	}
	switch(e->state)
	{
		case WAITING:
		{
			e->Animation++;

			if(e->Animation==4)
			{
				e->Animation=1;
				if(e->Direction)
				{
					e->Direction=false;	
				}
				else
				{
					e->Direction=true;	
				}
			}
			if(e->Direction)
			{
				e->Position.x+=50;	
			}
			else
			{
				e->Position.x-=50;	
			}
			break;
		}
		case FOLLOWING:
		{		
			if(dist<0)
			{
				e->Position.x-=30;
			}
			else
			{
				e->Position.x+=30;
			}
			break;
		}
	}
			

	
}

void Free_Ennemy(Ennemy *e)
{
	for(int i=1;i<4;i++)
	{
		SDL_FreeSurface(e->Animation_D[i]);
		SDL_FreeSurface(e->Animation_G[i]);
	}
}

