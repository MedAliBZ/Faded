#include"vie.h"


void Init_Vie(Vie *v)
{
	v->Barre[1]=IMG_Load("img/vie/vie1.png");
	v->Barre[2]=IMG_Load("img/vie/vie2.png");
	v->Barre[3]=IMG_Load("img/vie/vie3.png");
	v->vie=3;
	v->survie=true;
}

void Calcul_Vie(Vie *v)
{
	v->vie--;
	if(v->vie==0)
	{
		v->survie=false;
	}
}

void Display_Vie(Vie *v,SDL_Surface*ecran,SDL_Rect position)
{
	SDL_BlitSurface(v->Barre[v->vie],NULL,ecran,&position);
	SDL_Flip(ecran);
}

void Free_vie(Vie *v)
{
	for(int i=1;i<4;i++)
	{
		SDL_FreeSurface(v->Barre[i]);
	}
}
