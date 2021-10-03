#include "wall.hpp"
wall::wall() : posX(300),posY(0){}
void wall::moving(SDL_Rect &a){
    posY += velY;
    if(posY > 720){
        posY = a.y;
    }
}
void wall::changeposX(SDL_Rect &a){
    posX = a.x;
}
void wall::render(our_texture& gWallTexture,SDL_Renderer* gRenderer )
{
    gWallTexture.render( posX, posY, gRenderer );
}
