#ifndef __Main_h__
#define __Main_h__

//Lib imports:
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLMain.lib")
#pragma comment(lib, "SDL_ttf.lib")
#pragma comment(lib, "SDL_image.lib")


//Includes:

#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <sdl/SDL.h>
#include <sdl/SDL_ttf.h>
#include <sdl/SDL_image.h>

#include "HelpLib.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"


//Defines:
#define FSDL_SCREEN_WIDTH		550
#define FSDL_SCREEN_HEIGHT		550
#define FSDL_SCREEN_BPP			0

#define FSDL_BG_IMAGE			TEXT("bliss.bmp")
#define FSDL_PADDLE_IMAGE		TEXT("paddle.jpg")
#define FSDL_BALL_IMAGE			TEXT("ball.jpg")


//#define OPENGL

#ifdef OPENGL
#define FSDL_SCREEN_FLAGS		SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL | SDL_OPENGLBLIT
#define UpdateWholeScreen(x)	SDL_GL_SwapBuffers()
#else //Not OPENGL
#define FSDL_SCREEN_FLAGS		SDL_HWSURFACE | SDL_DOUBLEBUF
#define UpdateWholeScreen(x)	SDL_Flip(x)
#endif //OPENGL

//Macros:
#define print(x)				MessageBox(NULL, x, "Debug string!", 0);

//Globals:
SDL_Surface *surScreen = NULL;
SDL_Rect *rectDirtyRects = new SDL_Rect[100];
int iDirtyRectsCount = 0;
enum RECT_SIDES_HIT {SIDE_LEFT, SIDE_RIGHT, SIDE_UP, SIDE_DOWN};


#endif //__Main_h__