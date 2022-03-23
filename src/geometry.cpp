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
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const double PI = 3.141592653589793238;
//x and y are starting positions of the map building blocks. 
// rowSize is the row breaker that determines the number of blocks in a row.
// px and py are the position of the player.
// boxSize determines the size of one block.
// pxi and pyi are the amount of increments added and subtracted from px and py during movement.
int x, y, rowSize = 50, boxSize = 20;
double px, py, pxi, pyi, plx, ply; 
double pa;
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
//the size of the array.
int mapSize = sizeof(map)/sizeof(*map);


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();
// calculates the map array index corresponding to the pixel position of the player on the screen.
//cpx is the x postion of the player.
//cpy is the y posion of the player.
//box is the size of each blocks of the map
//max is the number of blocks in a single row of the map.
int calculateIndex(double cpx, double cpy, int box, int max);

//renders the view of the player
//px0 x position of the player.
//pyo y position of the player.
// the angle of view.
void drawSight(double px0, double py0, double angle);

// draws a map on the screen.
void drawMap();

// draws a player on the screen.
//pan: the angle of the player.
void drawPlayer(double pan);
// calculates the map array index corresponding to the block the player currently stands on.
void calculateIndex();

void findWallSide(double siX, double siY, int box);

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
void drawSight(double px0, double py0, double angle)
{
	int len = 0;
	int sightTest = 0;
	double plxI = px0;
	double plyI = px0;
	while(sightTest == 0)
	{
		len = len + 1;
		plxI = px0+1+len*cos(angle);
		plyI = py0+1+len*sin(angle);
		
		if(map[calculateIndex(plxI, plyI, boxSize, rowSize)] != 0)
		{
			while(map[calculateIndex(plxI, plyI, boxSize, rowSize)] != 0)
			{
				len = len-1;
				plxI = px0+1+len*cos(angle);
				plyI = py0+1+len*sin(angle);
			}
			sightTest = 1;
		}
	
	}		
	findWallSide(plxI,plyI,boxSize);
	SDL_RenderDrawLine( gRenderer, px+1, py+1, plxI, plyI );
}
void findWallSide(double siX, double siY, int box)
{
 	int dpx = floor(siX/box) * box;
	int dpy = floor(siY/box) * box;

	if(abs(dpx+box-siX) < abs(dpx-siX))
	{
		dpx = dpx+box;
	}
	if(abs(dpy+box-siY) < abs(dpy-siY) )
	{
		dpy = dpy+box;
	}

	if(abs(dpx-siX) < abs(dpy-siY))
	{
		SDL_SetRenderDrawColor( gRenderer, 0xff, 0x22, 0x33, 0xFF );
	}
	else
	{
		SDL_SetRenderDrawColor( gRenderer, 0x11, 0x22, 0x42, 0xFF );
	}
	
}
void drawPlayer(double pan, double playerX, double playerY)
{
	double plx1 = px, ply1 = py, plx2 = px, ply2 = py, plx3 = px, ply3 = py;
	int pxx = round(playerX);
	int pyy = round(playerY);
	SDL_Rect fillRect = { pxx, pyy, 3, 3 };
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xaa, 0x35, 0xFF );		
	SDL_RenderFillRect( gRenderer, &fillRect );
	
	//Draw blue horizontal line
	int counter = 0;
	double increment = -0.6;
	while(counter < 192){
		drawSight(pxx, pyy, (pan+increment));
		increment = increment + 0.00625;
		counter = counter + 1;
	}
	
	
	

}
void drawMap()
{
	x = 0; y = 0;
	int t = rowSize - 1;
	for(int i = 0; i < mapSize; i++)
	{
		//Render red filled quad
		SDL_Rect fillRect = { x, y, boxSize, boxSize };
		if(map[i] == 1)
		{
			SDL_SetRenderDrawColor( gRenderer, 0x11, 0x11, 0x11, 0xFF );
		}
		else if(map[i] == 2)
		{
			SDL_SetRenderDrawColor( gRenderer, 0x12, 0x96, 0x35, 0xFF );
		}
		else
		{
			SDL_SetRenderDrawColor( gRenderer, 0xf7, 0xe2, 0xbc, 0xFF );
		} 
		
		SDL_RenderFillRect( gRenderer, &fillRect );
		
		if( i < t)
		{
			x = x + boxSize;						
		}
		else
		{
			t = t + rowSize;
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
							if(map[calculateIndex(px, py, boxSize, rowSize)] != 0)
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
							if(map[calculateIndex(px, py, boxSize, rowSize)] != 0)
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
				
				drawPlayer(pa, px, py);
				
				//Update screen
				SDL_RenderPresent( gRenderer );

				
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}