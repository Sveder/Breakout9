#include "Main.h"


SDL_Surface *LoadBackground()
{
	SDL_Surface *surBG = LoadOptimizedImage(FSDL_BG_IMAGE);
	ApplySurface(0, 0, surBG, surScreen); 
	return surBG;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	srand(unsigned(time(NULL)));
	//A buffer to use for sprintf-ing and printing:
	char *sPrintBuf = new char;
	//A flag to know when to quit the game:
	bool isQuit = false; 
	SDL_Event *evCurEvent = new SDL_Event;
	
	//Initialize all SDL subsystems:
	SDL_Init(SDL_INIT_EVERYTHING);	
	//Initialize the screen:
	surScreen = SDL_SetVideoMode(FSDL_SCREEN_WIDTH, FSDL_SCREEN_HEIGHT, FSDL_SCREEN_BPP, FSDL_SCREEN_FLAGS);
	if (NULL == surScreen)
	{
		sprintf(sPrintBuf, "There was an error opening the SDL screen: %d", SDL_GetError());
		print(sPrintBuf);
		return 1;
	}
	SDL_WM_SetCaption("Breakout", NULL);
 	Paddle padMainPaddle = Paddle(FSDL_PADDLE_IMAGE, 100, 500);
	SDL_Surface *surBackground = LoadBackground();
	int lastKeyPressed, iSpeed = 2;
	const iBricksInRow = 12;
	const iRows = 5;
	int iWidth = 30;
	int iHeight = 15;
	int iKilled = 0;
	Brick *brickBricks[iRows][iBricksInRow];
	for (int i = 0; i < iRows; i++)
	{
		for (int j = 0; j < iBricksInRow; j++)
		{
			brickBricks[i][j] = new Brick(iWidth * j + 100, iHeight * i + 100);
			brickBricks[i][j]->Show(surScreen);
		}
	}
	padMainPaddle.Show(surScreen);

	Uint32 iColorKey = SDL_MapRGB(surScreen->format, 255, 255, 255);
	Ball ballMain = Ball(FSDL_BALL_IMAGE, 300, 300, iColorKey);
	ballMain.Show(surScreen);
	UpdateWholeScreen(surScreen);
	bool isDirectionChanged = false;
	while (!isQuit)
	{
		while (SDL_PollEvent(evCurEvent))
		{
			//Check if the game needs to be terminated, and terminate it on escape and alt f4::
			if (SDL_QUIT == evCurEvent->type)	
				isQuit = true;
			if (SDLK_ESCAPE == evCurEvent->key.keysym.sym)
				isQuit = true;
			if ((SDLK_F4 == evCurEvent->key.keysym.sym) && (256 == (int)(KMOD_LALT & evCurEvent->key.keysym.mod)))
				isQuit = true;

			if ((SDL_PRESSED == evCurEvent->key.state) && (SDLK_LEFT == evCurEvent->key.keysym.sym))
			{
				rectDirtyRects[iDirtyRectsCount] = padMainPaddle.GetPaddleRect();
				iDirtyRectsCount += 1;
				lastKeyPressed = SDLK_LEFT;
				padMainPaddle.StartMove(-1 * iSpeed);
			}
			if ((SDL_PRESSED == evCurEvent->key.state) && (SDLK_RIGHT == evCurEvent->key.keysym.sym))
			{
				rectDirtyRects[iDirtyRectsCount] = padMainPaddle.GetPaddleRect();
				iDirtyRectsCount += 1;
				lastKeyPressed = SDLK_RIGHT;
				padMainPaddle.StartMove(iSpeed);
			}
			if ((SDL_RELEASED == evCurEvent->key.state) && (lastKeyPressed == evCurEvent->key.keysym.sym))
				padMainPaddle.StopMove();
			
		}
		rectDirtyRects[iDirtyRectsCount] = ballMain.GetBallRect();
		iDirtyRectsCount += 1;
		if (ballMain.Move())
		{
			print("Nope, no three lives - YOU LOST!");
			return 0;
		}
		ApplySurface(0,0,surBackground, surScreen);
		rectDirtyRects[iDirtyRectsCount] = padMainPaddle.GetPaddleRect();
		iDirtyRectsCount += 1;
		rectDirtyRects[iDirtyRectsCount] = padMainPaddle.Show(surScreen);
		iDirtyRectsCount += 1;
		rectDirtyRects[iDirtyRectsCount] = ballMain.Show(surScreen);
		iDirtyRectsCount += 1;
		if (HitTest(padMainPaddle.GetPaddleRect(), ballMain.GetBallRect()))
		{
			ballMain.ChangeDirection();
		}
		for (i = 0; i < iRows; i++)
		{
			for (int j = 0; j < iBricksInRow; j++)
			{
				if ((brickBricks[i][j] != NULL) && (HitTest(brickBricks[i][j]->GetBrickRect(), ballMain.GetBallRect())))
				{
					bool isDead = brickBricks[i][j]->Hit(50);
					if (!isDirectionChanged)
					{
						ballMain.ChangeDirection();
						isDirectionChanged = true;
					}
					if (isDead)
					{
						iKilled++;
						SDL_Rect rectBlitBg = brickBricks[i][j]->GetBrickRect();
						rectBlitBg.h = iHeight;
						rectBlitBg.w = iWidth;
						ApplySurface(rectBlitBg.x, rectBlitBg.y , brickBricks[i][j]->GetSurface(), surScreen, &rectBlitBg);
						rectDirtyRects[iDirtyRectsCount] = brickBricks[i][j]->GetBrickRect();
						iDirtyRectsCount += 1;
						delete brickBricks[i][j];
						brickBricks[i][j] = NULL;
						if (iRows * iBricksInRow == iKilled)
						{
							print("You won, you rule!");
							return 0;
						}

					}
					else
					{
						rectDirtyRects[iDirtyRectsCount] = brickBricks[i][j]->Show(surScreen);
						iDirtyRectsCount += 1;
					}
				}
				else if (NULL != brickBricks[i][j])
				{
					rectDirtyRects[iDirtyRectsCount] = brickBricks[i][j]->Show(surScreen);
					iDirtyRectsCount += 1;
				}
			}
		}
		SDL_UpdateRects(surScreen, iDirtyRectsCount, rectDirtyRects);
		iDirtyRectsCount = 0;
		isDirectionChanged = false;

	}
	return 0;
}