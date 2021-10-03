//
//  wall.hpp
//  HW
//
//  Created by XRic on 2019/1/5.
//  Copyright © 2019 XRic. All rights reserved.
//

#ifndef wall_hpp
#define wall_hpp

#include <stdio.h>
#include <SDL.h>
#include <cstdlib>
#include "our_texture.h"
class wall{
    int posX, posY;
public:
    wall();
    static const int WALL_WIDTH = 60;
    static const int WALL_HEIGHT = 30;
    int velY = 5;
    void moving(SDL_Rect &);
    void render(our_texture &,SDL_Renderer*);
    void changeposX(SDL_Rect &);
};
#endif /* wall_hpp */
