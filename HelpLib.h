#ifndef __HelpLib_h__
#define __HelpLib_h__

#include <sdl/SDL.h>
#include <sdl/SDL_image.h>

#include "Main.h"

//Functions:
SDL_Surface *LoadOptimizedImage(char* sFilename);
void ApplySurface(int x, int y, SDL_Surface* surSource, SDL_Surface* surDest, SDL_Rect *rectClip = NULL);
bool isInRect(int x, int y, SDL_Rect rect);
RECT_SIDES_HIT HitTest(SDL_Rect rectFirst, SDL_Rect rectSecond);

#endif //__HelpLib_h__