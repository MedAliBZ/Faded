#include "player.h"
#include <SDL/SDL_rotozoom.h>

void Initialisation_Player(Player *p,SDL_Rect pos)
{
	p->Position.x=pos.x;
	p->Position.y=pos.y;
	p->Position.w=pos.w;
	p->Position.h=pos.h;

	p->Etat_Mv=false;
	p->Etat_MvC=false;
	p->Ground=0;
	p->Jump=0;

	p->Direction=true;
	p->Deplacement=0;
	p->Animation=0;
	p->Attack=0;
	p->attack=0;
	p->vitesse=0;
	char str[512];

	for(int i=0;i<6;i++)
	{
		sprintf(str, "img/player/player_G%d.png", i+1);
		p->DeplacementG[i]=IMG_Load(str);
	}
	for(int j=0;j<6;j++)
	{
		sprintf(str, "img/player/player_D%d.png", j+1);
		p->DeplacementD[j]=IMG_Load(str);
	}
	for(int k=0;k<7;k++)
	{
		sprintf(str, "img/player/AttackD%d.png", k+1);
		p->AttackD[k]=IMG_Load(str);
	}

	p->AnimationG[0]=IMG_Load("img/player/player_G1.png");
	p->AnimationG[1]=IMG_Load("img/player/player_G2.png");

	p->AnimationD[0]=IMG_Load("img/player/Animation1.png");
	p->AnimationD[1]=IMG_Load("img/player/Animation2.png");
}




void Display_Player(Player *p,SDL_Surface *ecran,SDL_Rect position)
{
	fprintf(stderr," %d \n",p->Attack);
	if(p->Attack==0)
	{
		if(p->Direction)
		{
			SDL_BlitSurface(p->DeplacementD[p->Deplacement], NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(5);
		}
		else
		{
			SDL_BlitSurface(p->DeplacementG[p->Deplacement], NULL, ecran, &position);
			SDL_Flip(ecran);
			SDL_Delay(5);
		}
	}
	else
	{

		
	}
	
	p->Etat_MvC=false;
	p->Animation++;
	if(p->Animation==2)
	{
		p->Animation=0;
	}
}

void Attack_Player(Player *p,SDL_Surface *ecran,SDL_Rect position)
{
	fprintf(stderr," attack \n");
	SDL_BlitSurface(p->AttackD[p->attack], NULL, ecran, &position);
	SDL_Flip(ecran);
	SDL_Delay(5);
	p->attack++;
	if(p->attack==7)
	{
		p->attack=0;
		p->Attack=0;
	}
	p->Position.x++;
}

void Animation_Player(Player *p,SDL_Surface *ecran,SDL_Rect position)
{
	if(p->Direction)
	{
		SDL_BlitSurface(p->AnimationD[p->Animation], NULL, ecran, &position);
		SDL_Flip(ecran);

	}
	else
	{
		SDL_BlitSurface(p->AnimationG[p->Animation], NULL, ecran, &position);
		SDL_Flip(ecran);
	}
	p->Animation++;
	if(p->Animation==2)
	{
		p->Animation=0;
	}
}


void DeplacementPlayer(Player *p,SDL_Rect position)
{
	if(position.x > p->Position.x)
	{
		p->Position.x+=10;
		p->Direction=true;
		if(position.x < p->Position.x)
		{
			p->Position.x=position.x;
			p->Etat_Mv=false;
		}		
	}
	else
	{
		p->Position.x-=10;
		p->Direction=false;
		if(position.x > p->Position.x)
		{
			p->Position.x=position.x;
			p->Etat_Mv=false;
		}		
	}
	p->Deplacement++;
	if(p->Deplacement==6)
	{
		p->Deplacement=0;
	}
}

void DeplacementPlayerC(Player *p,Uint32 dt)
{
	p->vitesse+=dt*ACCELERATION;
	if(p->vitesse >50)
	{
		p->vitesse=50;
	}

	if(p->Direction)
	{
		p->Position.x+=p->vitesse;
	}
	else
	{
		p->Position.x-=p->vitesse;
	}		

	p->Deplacement++;
	if(p->Deplacement==6)
	{
		p->Deplacement=0;
	}
}

void Free_Player(Player *p)
{
	for(int i=0;i<2;i++)
	{
		SDL_FreeSurface(p->DeplacementG[i]);
		SDL_FreeSurface(p->DeplacementD[i]);
	}
}
void zoom_affichage(SDL_Surface *p,SDL_Surface *ecran)
{
int i;
float ratio,x,y;
SDL_Surface *image;image=p;
SDL_Rect pos;
image=rotozoomSurface(image,0,0.1,SMOOTHING_ON);
for(i=1;i<101;i++)
{
ratio=i*0.01;
x=1920;
y=1200;
x=x/2-(x/2/100)*i;y=y/2-(y/2/100)*i;
pos.x=x;pos.y=y;
image=rotozoomSurface(image,0,ratio,SMOOTHING_ON);
SDL_BlitSurface(image,NULL,ecran,&pos);
SDL_Flip(ecran);
SDL_Delay(5);
SDL_FreeSurface(image);
image=NULL;
image=p;
}
SDL_Delay(500);
}
