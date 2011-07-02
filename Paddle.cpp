#include "Paddle.h"

Paddle::Paddle(char* sImageName, int iStartX, int iStartY)
{
	this->surPaddle = LoadOptimizedImage(sImageName);
	this->sImageName = sImageName;
	this->iY = iStartY;
	this->iX = iStartX;
	this->iDelta = 0;
	this->bIsMoving = false;
}

Paddle::~Paddle()
{
	SDL_FreeSurface(this->surPaddle);
}

Paddle::StartMove(int iDelta)
{
	this->iDelta = iDelta;
	this->bIsMoving = true;
}

Paddle::StopMove()
{
	this->bIsMoving = false;
}

SDL_Rect Paddle::Show(SDL_Surface *surScreen)
{
	if (this->bIsMoving)
		this->iX += this->iDelta;
	if (((1 + surScreen->w - this->surPaddle->w) < this->iX) || (0 > this->iX))
		this->iX -= this->iDelta;
	
	ApplySurface(this->iX, this->iY, this->surPaddle, surScreen);
	return GetPaddleRect();
}

SDL_Rect Paddle::GetPaddleRect()
{
	SDL_Rect rectPaddle = this->surPaddle->clip_rect;
	rectPaddle.x = this->iX;
	rectPaddle.y = this->iY;
	return rectPaddle;
}
