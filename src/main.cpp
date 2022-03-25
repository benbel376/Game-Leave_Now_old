/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 600;
const double PI = 3.141592653589793238;
int map[] = 
{
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,2,2,2,2,1,2,2,2,1,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,
1,2,0,0,0,0,0,0,0,1,1,2,0,0,2,1,2,0,0,0,2,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,2,1,
1,2,0,0,0,0,0,0,0,0,1,2,0,0,2,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,2,1,
1,2,0,0,0,0,0,0,0,0,1,2,0,0,2,1,0,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,1,2,0,2,1,
1,2,0,0,0,0,0,0,0,0,1,2,0,2,2,1,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
1,2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,2,0,2,1,
1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,2,0,2,1,
1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,1,2,0,0,0,1,2,0,2,1,
1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,1,2,0,0,0,1,2,2,2,1,
1,2,0,0,0,1,2,0,0,0,1,2,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,2,0,0,0,1,1,1,1,1,
1,2,0,0,0,0,0,0,0,0,1,2,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,2,0,0,0,0,0,1,2,0,0,0,0,0,0,2,1,
1,2,0,0,2,2,2,2,0,0,1,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,2,0,0,0,1,0,0,2,1,
1,2,0,0,2,1,1,2,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,1,1,1,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,2,0,0,0,1,0,0,2,1,
1,2,0,0,2,1,1,2,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,2,0,0,2,2,2,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,2,1,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,2,1,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,2,1,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,0,0,0,0,1,2,0,0,1,2,2,0,0,0,1,2,0,0,0,1,2,2,2,0,0,0,0,0,2,1,0,0,0,2,1,0,0,2,2,2,0,0,0,0,1,0,0,2,1,
1,0,0,0,0,1,2,0,0,1,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,1,0,0,2,1,2,0,0,0,0,1,0,0,2,1,
1,0,0,0,0,1,1,1,0,1,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,2,2,2,0,0,0,0,1,0,0,2,1,
1,0,0,0,0,1,2,0,0,2,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,0,0,0,0,1,2,0,0,2,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,1,0,0,2,1,
1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			//While application is running
			while( !quit )
			{
				startX = 1010;
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					pxi = cos(pa);
					pyi = sin(pa);
					
					
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_LEFT:
							
							break;

							case SDLK_RIGHT:
							
							break;
							case SDLK_UP:
							
							break;

							case SDLK_DOWN:

							break;

							default:
							// nothing.
							break;
						}
					}
				}
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				//Update screen
				SDL_RenderPresent( gRenderer );

				
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}