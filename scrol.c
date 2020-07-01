#include"scrol.h"

void Initialisation_Scroll(Scroll *cam,SDL_Rect pos_player,int width,int height)
{
	cam->scroll.x=pos_player.x-(width*.5);
    cam->scroll.y=0;
    cam->scroll.w=width;
    cam->scroll.h=height;
    cam->pos_real.x=0;
    cam->pos_real.y=0;
    cam->pos_real.w=pos_player.w;
    cam->pos_real.h=pos_player.h;
}

void Scrolling(Scroll *cam,SDL_Rect pos_player,int width,int height)
{
	cam->scroll.x=(pos_player.x + pos_player.w*.5)-(width*.5);
	
	if(cam->scroll.x >=8000-width)
    {
        cam->scroll.x=8000-width;
    }
    if(cam->scroll.x<=0)
    {
    	cam->scroll.x=0;
    }

    cam->pos_real.x=pos_player.x-cam->scroll.x;
    cam->pos_real.y=pos_player.y;

    if (cam->pos_real.x>=1000)
    {
        cam->pos_real.x=1000-161;
    }
    else if (cam->pos_real.x <=0)
    {
        cam->pos_real.x=0;
    }
}
