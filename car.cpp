#include "car.h"
bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

car::car()
{
    posX = 300 - (CAR_WIDTH/2);
    velX = 0;
    maxV = 0;
    collider.w = 40;
    collider.h = 80;
}

car::car(int v)
:maxV(v)
{
    posX = 300 - (CAR_WIDTH/2);
    velX = 0;
    collider.w = 40;
    collider.h = 80;
}

void car::handleEvent( SDL_Event& e ,Mix_Chunk* drift)
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {

            case SDLK_LEFT:
                velX -= maxV;
                Mix_PlayChannel(-1,drift,0);
                break;
            case SDLK_RIGHT:
                velX += maxV;
                Mix_PlayChannel(-1,drift,0);
                break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: velX += maxV; break;
            case SDLK_RIGHT: velX -= maxV; break;
        }
    }
}

void car::moving(SDL_Rect& a,mode& play)
{
    //Move the car left or right
    posX += velX;
    collider.x = posX;
    collider.y = posY;

    //If the car went too far to the left or right
    if( ( posX < 200 ) || ( posX + CAR_WIDTH > 400 ) )
    {
        //Move back
        posX -= velX;
        collider.x = posX;
    }

    if( checkCollision(collider, a) )
    {
        play = over;
    }
}

void car::render(our_texture& gcarTexture,SDL_Renderer* gRenderer )
{
	gcarTexture.render(  posX, posY, gRenderer );
}
