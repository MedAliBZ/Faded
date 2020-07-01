#include "minimap.h"

void Init_MiniMap(Minimap*m,Player*p)
{
	m->back=IMG_Load("img/minimap.png");
	m->Dot=IMG_Load("img/Dot.png");
	m->posBlit.x=100;
	m->posBlit.y=600-60;
	m->posDot.x=p->Position.x/10+100;
	m->posDot.y=p->Position.y/10+600-60;
}

void Update_MiniMap(Minimap *m,Player*p)
{
	m->posDot.x=p->Position.x/10+100;
	m->posDot.y=p->Position.y/10+600-60;
}

void Display_MiniMap(Minimap*m,SDL_Surface*ecran)
{
	SDL_BlitSurface(m->back,NULL,ecran,&(m->posBlit));
	SDL_BlitSurface(m->Dot,NULL,ecran,&(m->posDot));
	SDL_Flip(ecran);
}