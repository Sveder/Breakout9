#ifndef __Paddle_h__
#define __Paddle_h__

#include "HelpLib.h"

//Classes:
class Paddle
{
public:
	Paddle(char* sImageName, int iStartX, int iStartY);
	~Paddle();
	StartMove(int iDelta);
	StopMove();
	SDL_Rect Show(SDL_Surface *surScreen);
	SDL_Rect GetPaddleRect();
protected:
private:
	int iX, iY, iDelta;
	char* sImageName;
	bool bIsMoving;
	SDL_Surface *surPaddle;
};

#endif //__Paddle_h__