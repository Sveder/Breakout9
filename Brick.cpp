#include "Brick.h"

Brick::Brick(int iStartX, int iStartY, Uint32 iColor)
{
	this->surBrick = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 15, 10, 0, 0, 0, 0);
	int iRed = rand();
	int iGreen = rand();
	int iBlue = rand();
	this->iColor = SDL_MapRGB(this->surBrick->format, iRed, iGreen, iBlue);
	SDL_FillRect(this->surBrick, NULL, this->iColor);
	this->iX = iStartX;
	this->iY = iStartY;
	this->iStrength = 100;
}

Brick::~Brick()
{
	SDL_FreeSurface(this->surBrick);
}

SDL_Rect Brick::GetBrickRect()
{
	SDL_Rect rectReturnRect = this->surBrick->clip_rect;
	rectReturnRect.x = this->iX;
	rectReturnRect.y = this->iY;
	return rectReturnRect;
}


SDL_Rect Brick::Show(SDL_Surface *surScreen)
{
	ApplySurface(this->iX, this->iY, this->surBrick, surScreen);
	return GetBrickRect();
}

bool Brick::Hit(Uint8 iStrength)
{
	this->iStrength = this->iStrength - iStrength;
	if (0 == this->iStrength)
		return false;
	this->surBrick = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 15, 10, 0, 0, 0, 0);
	int iRed = rand();
	int iGreen = rand();
	int iBlue = rand();
	this->iColor = SDL_MapRGBA(this->surBrick->format, iRed, iGreen, iBlue, iStrength);
	return true;
}

SDL_Surface *Brick::GetSurface()
{
	return this->surBrick;
}