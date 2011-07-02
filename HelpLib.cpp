#include "HelpLib.h"

SDL_Surface *LoadOptimizedImage(char* sFilename)
{ 
	//One surface to load the image, and and optimized image:
	SDL_Surface* surOriginalImage = new SDL_Surface; 
	SDL_Surface* surOptimized = new SDL_Surface;

 	surOriginalImage = IMG_Load(sFilename);
	if (NULL != surOriginalImage)
	{
		surOptimized = SDL_DisplayFormat(surOriginalImage);
		if (NULL == surOptimized)
			surOptimized = surOriginalImage;
	}
	SDL_FreeSurface(surOriginalImage);

	return surOptimized;
}


void ApplySurface(int x, int y, SDL_Surface* surSource, SDL_Surface* surDest, SDL_Rect *rectClip)
{
	//Create a rectangle and fill it to allow blitting:
	SDL_Rect rectOffset;
	rectOffset.x = x;
	rectOffset.y = y;
	
	//Blit:
	SDL_BlitSurface(surSource, rectClip, surDest, &rectOffset);
}

bool isInRect(int x, int y, SDL_Rect rect)
{
	bool isIn = false;
	if ((rect.x <= x) && (rect.x + rect.w >= x))
		if ((rect.y <= y) && (rect.y + rect.h >= y))
			isIn = true;
	return isIn;
}

bool HitTest(SDL_Rect rectFirst, SDL_Rect rectSecond)
{
	bool isHit = false;
	
	if (isInRect(rectFirst.x, rectFirst.y, rectSecond))
		isHit = true;
	if (isInRect(rectFirst.x + rectFirst.w, rectFirst.y, rectSecond))
		isHit = true;
	if (isInRect(rectFirst.x, rectFirst.y + rectFirst.h, rectSecond))
		isHit = true;
	if (isInRect(rectFirst.x + rectFirst.w, rectFirst.y + rectFirst.h, rectSecond))
		isHit = true;

	if (isInRect(rectSecond.x, rectSecond.y, rectFirst))
		isHit = true;
	if (isInRect(rectSecond.x + rectSecond.w, rectSecond.y, rectFirst))
		isHit = true;
	if (isInRect(rectSecond.x, rectSecond.y + rectSecond.h, rectFirst))
		isHit = true;
	if (isInRect(rectSecond.x + rectSecond.w, rectSecond.y + rectSecond.h, rectFirst))
		isHit = true;

	return isHit;
}