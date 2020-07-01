#include"collisionparfait.h"

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
	SDL_Color color;
	Uint32 col=0;
	//Determine position
	char* pPosition=(char* ) pSurface->pixels;
	pPosition+= (pSurface->pitch * y);
	pPosition+= (pSurface->format->BytesPerPixel *x);
	memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel);
	//convertir color
	SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
	return (color);
}

int Collision_Parfait(Player *p,SDL_Surface *backgroundMask)
{
	SDL_LockSurface(backgroundMask);
	SDL_Color pixel,pixel1;

	pixel1=GetPixel(backgroundMask,(p->Position.x+(p->Position.w/2)),(p->Position.y + p->Position.h));
	if(pixel1.r==255 && pixel1.b==255  && pixel1.g==255)
	{
		p->Ground=1;
	}
	else
	{
		p->Ground=0;
	}

	
	if(p->Direction)
	{
		if(p->Jump==1)
		{
			pixel=GetPixel(backgroundMask,(p->Position.x+p->Position.w),(p->Position.y+p->Position.h));
		}
		else
		{
			pixel=GetPixel(backgroundMask,(p->Position.x+p->Position.w),(p->Position.y+(p->Position.h /2)));
		}
	}
	else
	{
		if(p->Jump==1)
		{
			pixel=GetPixel(backgroundMask,(p->Position.x),(p->Position.y+p->Position.h));
		}
		else
		{
			pixel=GetPixel(backgroundMask,(p->Position.x),(p->Position.y+(p->Position.h /2)));
		}
	}
	
	if(pixel.r==255 && pixel.b==255  && pixel.g==255)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	SDL_UnlockSurface(backgroundMask);
}
