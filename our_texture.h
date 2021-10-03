#ifndef OUR_TEXTURE_H
#define OUR_TEXTURE_H


#include <string>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



class our_texture
{
    public:

		our_texture();


		~our_texture();

		bool loadfile( std::string path ,SDL_Renderer*);

		#ifdef _SDL_TTF_H
		bool loadFromRenderedText( std::string textureText, SDL_Color,TTF_Font*,SDL_Renderer*);
		#endif

		void free();

		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );

		void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* myTexture;

		int myWidth;
		int myHeight;
};

#endif // OUR_TEXTURE_H
