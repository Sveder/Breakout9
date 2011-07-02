#include "Ball.h"

Ball::Ball(char* sImageName, int iStartX, int iStartY)
{
	this->iX = iStartX;
	this->iY = iStartY;
	this->sImageName = sImageName;
	this->surBall = LoadOptimizedImage(sImageName);
	this->isMoving = false;
}

Ball::Ball(char* sImageName, int iStartX, int iStartY, Uint32 iColorKey)
{
	this->iX = iStartX;
	this->iY = iStartY;
	this->iXDelta = 0.2;
	this->iYDelta = 0.6	;
	this->isRight = true;
	this->sImageName = sImageName;
	this->surBall = LoadOptimizedImage(sImageName);
	SDL_SetColorKey(this->surBall, SDL_SRCCOLORKEY, iColorKey);
	this->isUp = false;
}

Ball::~Ball()
{
	SDL_FreeSurface(this->surBall);
}

SDL_Rect Ball::GetBallRect()
{
	SDL_Rect rectReturnRect = this->surBall->clip_rect;
	rectReturnRect.x = this->iX;
	rectReturnRect.y = this->iY;
	return rectReturnRect;
}

bool Ball::Move()
{
	this->iX += this->iXDelta * (this->isRight ? 1 : -1);
	this->iY += this->iYDelta * (this->isUp ? -1 : 1);

	if ((0 > this->iX) || (550 - this->surBall->clip_rect.w < this->iX))
	{
		this->isRight = !(this->isRight);
		this->Move();
	}
	if (0 > this->iY)
	{
		this->ChangeDirection();
		this->Move();
	}

	return (this->iY > 550) ? true : false;
}


SDL_Rect Ball::Show(SDL_Surface *surScreen)
{
	ApplySurface(this->iX, this->iY, this->surBall, surScreen);
	return GetBallRect();
}

Ball::SetDeltas(float iNewXDelta, float iNewYDelta)
{
	this->iXDelta = iNewXDelta;
	this->iYDelta = iNewYDelta;
}

Ball::ChangeDirection()
{
	this->isUp = !(this->isUp);
}