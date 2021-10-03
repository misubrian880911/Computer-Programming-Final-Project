#include "car.h"
#include "our_texture.h"
#include "LButton.h"
#include <ctime>
#include <sstream>
#include <SDL_mixer.h>
#include "wall.hpp"

using namespace std;

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 600
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 720
#endif

bool init();

bool loadMedia();

void close();

mode play = start;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

our_texture gcarTexture;
our_texture gcarSpeedingTexture;
our_texture gBGTexture;
our_texture gSpeedingButtonTexture;

our_texture gTimeTextTexture;

our_texture gDistTextTexture;

our_texture gcurrentTexture;
our_texture greadyTexture;

our_texture gButtonstartTexture;
our_texture gButtonoverTexture;
our_texture gButtoncomplTex;

our_texture gWallTexture;

TTF_Font *gFont = NULL;

SDL_Rect gSpriteClips;
LButton START;
LButton COMPL;
LButton OVER;

Mix_Music *opening = NULL;
Mix_Chunk *drift = NULL;
Mix_Chunk *ignition = NULL;
Mix_Music *dejavu = NULL;
Mix_Chunk *boosting = NULL;


bool init()
{

	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
		gWindow = SDL_CreateWindow( "Final", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if( !greadyTexture.loadfile( "ready.png",gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gWallTexture.loadfile( "wall.png",gRenderer ) )
    {
        printf( "Failed to load wall texture!\n" );
        success = false;
    }

	if( !gcarTexture.loadfile( "86.png",gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gcarSpeedingTexture.loadfile( "86_speeding.png",gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadfile( "road1.png",gRenderer  ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gSpeedingButtonTexture.loadfile( "speedup_button.png",gRenderer  ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

    if( !gButtonstartTexture.loadfile( "initial.png",gRenderer  ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
    if( !gButtonoverTexture.loadfile( "over.png",gRenderer  ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gButtoncomplTex.loadfile( "complete.png",gRenderer  ) ){
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	gFont = TTF_OpenFont( "airstrike.ttf", 30 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	opening = Mix_LoadMUS( "opening.mp3" );
	if( opening == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	drift = Mix_LoadWAV( "drift.wav" );
	if( drift == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	ignition = Mix_LoadWAV( "ignition.wav" );
	if( ignition == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	dejavu = Mix_LoadMUS( "deja vu and engine.mp3" );
	if( dejavu == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	boosting = Mix_LoadWAV( "boost.wav" );
	if( boosting == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}


void close()
{
	gcarTexture.free();
	gBGTexture.free();
	gSpeedingButtonTexture.free();
	gTimeTextTexture.free();
	gDistTextTexture.free();
	gButtonstartTexture.free();
	Mix_FreeMusic( opening );
	Mix_FreeChunk( ignition );
    Mix_FreeChunk( drift );
    Mix_FreeChunk( boosting );
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	opening = NULL;
    drift = NULL;
    ignition = NULL;
    boosting = NULL;

	IMG_Quit();
	SDL_Quit();
}

void timeing(time_t startTime,SDL_Color textColor)
{
    std::stringstream timeText;
    timeText.str( "" );
    timeText << "TIME " << (time(0) - startTime) ;

    if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor,gFont,gRenderer ) ){
					printf( "Unable to render time texture!\n" );
    }
}

int distanceing(int control_vel,SDL_Color textColor)
{
    std::stringstream distText;
    static int dist = 0;
    dist += control_vel;
    distText.str( "" );
    distText << "Distance " << dist/100;
    if(play==complete || play==over)
        dist = 0;

    if( !gDistTextTexture.loadFromRenderedText( distText.str().c_str(), textColor,gFont,gRenderer ) )
					printf( "Unable to render distance texture!\n" );
    return dist/100;
}


int main(int argc, char* args[])
{
    int distance0;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;
			bool speeding = false;
			bool canSpeeding = false;
			bool first_time_play = true;

			SDL_Event e;

			car car(5);

			wall walls;
            SDL_Rect rect;
            rect.x = 300;
            rect.y = 0;
            rect.w = 60;
            rect.h = 30;

            int bgrolling = 0;
            int control_vel = 0;

            time_t startTime = time(0);
            time_t speedingstartTime;
            time_t colletestartTime;
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( canSpeeding && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_LCTRL){
                        speeding = true;
                        canSpeeding = false;
                        speedingstartTime = time(0);
                        Mix_PlayChannel(-1,boosting,0);
                    }
                    START.handleEventM(&e,play);
                    car.handleEvent( e ,drift);
                }
                switch(play)
                {
                    case start:
                        if (!Mix_PlayingMusic())
                            Mix_PlayMusic(opening,1);
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );

                        START.render(gButtonstartTexture,gRenderer,&gSpriteClips);
                        gButtonstartTexture.render(0,0,gRenderer);

                        SDL_RenderPresent(gRenderer);
                        break;

                    case ready:{
                        Mix_PlayChannel(-1,ignition,0);
                        first_time_play = false;
                        clock_t get_into_gaming = clock();
                        while (clock()-get_into_gaming < 10000){
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            greadyTexture.render( 0,0,gRenderer );
                            SDL_RenderPresent( gRenderer );
                        }
                        play = gaming;
                        startTime = time(0);
                        colletestartTime = time(0);
                        rect.y = 0;
                        break;
                    }

                    case gaming:
                        if(!Mix_PlayingMusic()){
                            Mix_PlayMusic( dejavu, 1 );
                        }

                        timeing(startTime,{ 0, 0, 0, 255 });

                        car.moving(rect,play);

                        if (speeding){
                            control_vel = 15;
                            gcurrentTexture = gcarSpeedingTexture;
                            walls.velY = 15;
                        }
                        else if (!speeding){
                            control_vel = 10;
                            gcurrentTexture = gcarTexture;
                            walls.velY = 10;
                        }
                        if ((!speeding) && (time(0)-colletestartTime) > 5)
                            canSpeeding = true;
                        if (speeding && (time(0)-speedingstartTime) > 3){
                            speeding = false;
                            colletestartTime = time(0);
                        }

                        bgrolling+=control_vel;
                        if (bgrolling>SCREEN_HEIGHT)
                            bgrolling = 0;

                        distance0=distanceing(control_vel,{ 0, 0, 0, 255 });

                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );

                        gBGTexture.render( 0,bgrolling,gRenderer );
                        gBGTexture.render( 0,bgrolling-SCREEN_HEIGHT,gRenderer );
                        gTimeTextTexture.render( 420, 30,gRenderer);
                        gDistTextTexture.render( 400, 80,gRenderer);
                        if (canSpeeding)
                            gSpeedingButtonTexture.render( 20, 20,gRenderer);

                        car.render(gcurrentTexture,gRenderer );

                        rect.y+=control_vel;
                        if(rect.y > 720){
                            rect.y = rand()%720-720;
                            rect.x = rand()%140+200;
                            walls.changeposX(rect);
                        }
                        walls.moving(rect);
                        walls.render(gWallTexture, gRenderer);

                        SDL_RenderPresent( gRenderer );

                        if(distance0>=500)play=complete;
                        break;

                    case complete:
                        Mix_HaltMusic();
                        first_time_play = true;
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );

                        distance0=distanceing(control_vel,{ 0, 0, 0, 255 });

                        startTime=time(0);
                        colletestartTime=time(0);
                        car.posX = 300 - (car.CAR_WIDTH/2);
                        speeding = false;
                        canSpeeding = false;

                        COMPL.handleEventM(&e,play);

                        COMPL.render(gButtoncomplTex,gRenderer,&gSpriteClips);
                        gButtoncomplTex.render(0,0,gRenderer);

                        SDL_RenderPresent(gRenderer);

                        break;

                    case over:
                        Mix_HaltMusic();
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );

                        distance0=distanceing(control_vel,{ 0, 0, 0, 255 });

                        startTime=time(0);
                        colletestartTime=time(0);
                        car.posX = 300 - (car.CAR_WIDTH/2);
                        speeding = false;
                        canSpeeding = false;

                        OVER.handleEventM(&e,play);

                        OVER.render(gButtonoverTexture,gRenderer,&gSpriteClips);
                        gButtonoverTexture.render(0,0,gRenderer);

                        SDL_RenderPresent(gRenderer);
                        break;

			}
		}
	}

	//Free resources and close SDL
	close();

    return 0;
	}
}
