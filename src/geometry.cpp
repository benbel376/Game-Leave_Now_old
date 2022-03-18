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
const int SCREEN_WIDTH = 864;
const int SCREEN_HEIGHT = 486;
const double PI = 3.141592653589793238;
//x and y are starting positions of the map building blocks. 
// t is the row breaker that determines the number of blocks in a row.
// px and py are the position of the player.
// boxSize determines the size of one block.
// pxi and pyi are the amount of increments added and subtracted from px and py during movement.
int x, y, t, boxSize = 54;
double px, py, pxi, pyi, plx, ply; 
double pa;
int map[] = 
{
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,
1,0,0,1,0,0,0,0,0,0,0,1,1,1,0,1,
1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};
//the size of the array.
int mapSize = sizeof(map)/sizeof(*map);


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();
// calculates the index corresponding to the 
int calculateIndex(double cpx, double cpy, int box, int max);
// draws a map on the screen.

void drawMap();
// draws a player on the screen.
void drawPlayer(double pan);
// calculates the map array index corresponding to the block the player currently stands on.
void calculateIndex();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

int calculateIndex(double cpx, double cpy, int box, int max)
{
	int dpx = floor(cpx/box);
	int dpy = floor(cpy/box);
	int index = (max*dpy) + dpx;
	return index;
}
void drawSight(double px0, double py0, double angle){
	int len = 0;
	int sightTest = 0;
	double plxI = px0;
	double plyI = px0;
	while(sightTest == 0)
	{
		len = len + 10;
		plxI = px0+1+len*cos(angle);
		plyI = py0+1+len*sin(angle);
		
		if(map[calculateIndex(plxI, plyI, boxSize, 16)] == 1)
		{
			while(map[calculateIndex(plxI, plyI, boxSize, 16)] == 1)
			{
				len = len-2;
				plxI = px0+1+len*cos(angle);
				plyI = py0+1+len*sin(angle);
			}
			sightTest = 1;
		}
	
	}
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xaa, 0x35, 0xFF );		
	SDL_RenderDrawLine( gRenderer, px+1, py+1, plxI, plyI );
}
void drawPlayer(double pan)
{
	double plx1 = px, ply1 = py, plx2 = px, ply2 = py, plx3 = px, ply3 = py;
	SDL_Rect fillRect = { px, py, 3, 3 };
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xaa, 0x35, 0xFF );		
	SDL_RenderFillRect( gRenderer, &fillRect );
	
	//Draw blue horizontal line
	int counter = 0;
	double increment = -0.6;
	while(counter < 192){
		drawSight(px, py, (pan+increment));
		increment = increment + 0.00625;
		counter = counter + 1;
	}
	
	
	

}
void drawMap()
{
	x = 0; y = 0; t = 15; boxSize = 54;
	for(int i = 0; i < mapSize; i++)
	{
		//Render red filled quad
		SDL_Rect fillRect = { x, y, boxSize, boxSize };
		if(map[i] == 1)
		{
			SDL_SetRenderDrawColor( gRenderer, 0x11, 0x11, 0x11, 0xFF );
		}
		else
		{
			SDL_SetRenderDrawColor( gRenderer, 0x35, 0x75, 0xa3, 0xFF );
		} 
		
		SDL_RenderFillRect( gRenderer, &fillRect );
		
		if( i < t)
		{
			x = x + boxSize;						
		}
		else
		{
			t = t + 16;
			x = 0;
			y = y + boxSize;
		}

	} 

				
}

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
			SDL_Event e;
			px = 357;
			py = 297;
			pa = 0.0;
			
			
			
			//While application is running
			while( !quit )
			{
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
							pa = pa - (0.05*PI);
							if(pa <= 0){
								pa = pa + (2*PI);
							}
							break;

							case SDLK_RIGHT:
							pa = pa + (0.05*PI);
							if(pa >= 2*PI){
								pa = pa-(2*PI);
							}
							
							break;
							case SDLK_UP:
							py = py + (6*pyi); 
							px = px + (6*pxi);
							if(map[calculateIndex(px, py, boxSize, 16)] == 1)
							{
								py = py - (5*pyi); 
								px = px - (5*pxi);
							}
							py = py - (6*pyi); 
							px = px - (6*pxi);

							py = py + (5*pyi); 
							px = px + (5*pxi);
							break;

							case SDLK_DOWN:

							py = py - (6*pyi); 
							px = px - (6*pxi);
							if(map[calculateIndex(px, py, boxSize, 16)] == 1)
							{
								py = py + (5*pyi); 
								px = px + (5*pxi);
							}
							py = py + (6*pyi); 
							px = px + (6*pxi);

							py = py - (5*pyi); 
							px = px - (5*pxi);
							
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
				drawMap();
				
				drawPlayer(pa);
				
				//Update screen
				SDL_RenderPresent( gRenderer );

				
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}