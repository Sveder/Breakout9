#ifndef __Ball_h__
#define __Ball_h__

#include "HelpLib.h"

//Classes:
class Ball
{
public:
	Ball(char* sImageName, int iStartX, int iStartY);
	Ball(char* sImageName, int iStartX, int iStartY, Uint32 iColorKey);
	~Ball();
	SDL_Rect Show(SDL_Surface *surScreen);
	SDL_Rect GetBallRect();
	bool Move();
	SetDeltas(float iNewXDelta, float iNewYDelta);
	ChangeDirection(int nX);
protected:
private:
	Uint32 iColorKey;
	float iX, iY, iYDelta, iXDelta;
	char *sImageName;
	SDL_Surface *surBall;
	bool isMoving, isUp, isRight;
	
};


#endif //__Ball_h__