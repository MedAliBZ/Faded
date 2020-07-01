#include"bounding.h"


/*bool collision (SDL_Rect position1,SDL_Rect position2)
{
	if( (position1.x > (position2.x+position2.w)) || (position2.x > (position1.x + position1.w)) || 
	(position1.y > (position2.y + position2.h)) || (position2.y > (position1.y + position1.h)) )
	{
		return false;
	}
	else
	{
		return true;
	}
}*/
bool collision (SDL_Rect position1,SDL_Rect position2)
{
	if( (position1.x > (position2.x+position2.w)) || (position2.x > (position1.x + position1.w)) || 
	(position1.y > (position2.y + position2.h)) || (position2.y > (position1.y + position1.h)) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

