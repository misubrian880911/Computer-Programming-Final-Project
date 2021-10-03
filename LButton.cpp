#include "LButton.h"

LButton::LButton()
{
    mPosition.x = 175;
    mPosition.y = 550;
}

LButton::LButton(int x0,int yo)
{
    mPosition.x = x0;
    mPosition.y = yo;
}
void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEventM( SDL_Event* e,mode& play)
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
	//Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }
        //Mouse is outside button
        if( !inside )
        {
      //      mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    play=ready;
                    Mix_HaltMusic();
                    break;

                case SDL_MOUSEBUTTONUP:

                    break;
            }
        }
    }
}

void LButton::render(our_texture &gButtonSpriteSheetTexture,SDL_Renderer* gRenderer,SDL_Rect* gSpriteClips)
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, gRenderer, gSpriteClips );
}
