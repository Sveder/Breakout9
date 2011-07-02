#ifndef __Brick_h__
#define __Brick_h__

#include <time.h>
#include <stdlib.h>
#include "HelpLib.h"

//Classes:
class Brick
{
public:
	Brick(int iStartX, int iStartY, Uint32 iColor = 0);
	~Brick();
	SDL_Rect Show(SDL_Surface *surScreen);
	SDL_Rect GetBrickRect();
	bool Hit(Uint8 iStrength);
	SDL_Surface *GetSurface();
protected:
private:
	int iX, iY;
	Uint32 iColor;
	SDL_Surface *surBrick;
	int iStrength;
};


#endif //__Brick_h__