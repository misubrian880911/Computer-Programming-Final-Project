#ifndef LBUTTON_H
#define LBUTTON_H

#include <SDL.h>
#include "our_texture.h"
#include <SDL_mixer.h>
#include <ctime>
const int BUTTON_WIDTH = 250;
const int BUTTON_HEIGHT = 100;
enum mode
{
    start,ready,gaming,over,complete
};


class LButton
{
    public:
        //Initializes internal variables
        LButton();

        LButton(int,int);

        //Sets top left position
        void setPosition( int x, int y );

        //Handles mouse event
        void handleEventM( SDL_Event* e ,mode&);

        //Shows button sprite
        void render(our_texture&,SDL_Renderer*,SDL_Rect*);

    private:
        //Top left position
        SDL_Point mPosition;

        //Currently used global sprite
   //     LButtonSprite mCurrentSprite;
};

#endif // LBUTTON_H
