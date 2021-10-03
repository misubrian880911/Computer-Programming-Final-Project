#ifndef CAR_H
#define CAR_H


#include <SDL.h>
#include <SDL_mixer.h>
#include "our_texture.h"
#include "LButton.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 720;
class car
{
    public:

        car();
        car(int v);

		static const int CAR_WIDTH = 40;
		static const int CAR_HEIGHT = 80;

		void handleEvent( SDL_Event& ,Mix_Chunk *);

		void moving(SDL_Rect&,mode&);

		void render( our_texture&, SDL_Renderer* );

		int getPosX();
		int getPosY();
		int posX;

    private:
		const int posY = 600,velY = 0;
		int maxV;
		int velX;
		SDL_Rect collider;


};

#endif // CAR_H
