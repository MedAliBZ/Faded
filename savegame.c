#include "savegame.h"

void Init_Save(SaveG *s)
{
	s->back=IMG_Load("img/SaveImg/save.png");
	s->boutons[1]=IMG_Load("img/SaveImg/yes.png");
	s->boutons[0]=IMG_Load("img/SaveImg/no.png");
	s->boutonsp[1]=IMG_Load("img/SaveImg/yesp.png");
	s->boutonsp[0]=IMG_Load("img/SaveImg/nop.png");
	s->yes.x=364+150;
	s->yes.y=313;
	s->no.x=240+150;
	s->no.y=313;
	s->posBlit.x=200+150;
	s->posBlit.y=150;
	s->image_courrante=1;
}

void Display_Save(SaveG *s,SDL_Surface*ecran)
{
	SDL_BlitSurface(s->back,NULL,ecran,&(s->posBlit));
	if(s->image_courrante==1)
	{
		SDL_BlitSurface(s->boutonsp[0],NULL,ecran,&(s->no));
		SDL_BlitSurface(s->boutons[1],NULL,ecran,&(s->yes));
	}
	else if(s->image_courrante==2)
	{
		SDL_BlitSurface(s->boutons[0],NULL,ecran,&(s->no));
		SDL_BlitSurface(s->boutonsp[1],NULL,ecran,&(s->yes));
	}
	else
	{
		SDL_BlitSurface(s->boutons[0],NULL,ecran,&(s->no));
		SDL_BlitSurface(s->boutons[1],NULL,ecran,&(s->yes));
	}
	SDL_Flip(ecran);
	
}


