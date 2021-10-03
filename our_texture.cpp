#include "our_texture.h"
our_texture::our_texture()
{

	myTexture = NULL;
	myWidth = 0;
	myHeight = 0;
}

our_texture::~our_texture()
{

	free();
}

void our_texture::free()
{

	if( myTexture != NULL )
	{
		SDL_DestroyTexture( myTexture );
		myTexture = NULL;
		myWidth = 0;
		myHeight = 0;
	}
}

void our_texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{

	SDL_SetTextureColorMod( myTexture, red, green, blue );
}

void our_texture::setBlendMode( SDL_BlendMode blending )
{

	SDL_SetTextureBlendMode( myTexture, blending );
}

void our_texture::setAlpha( Uint8 alpha )
{

	SDL_SetTextureAlphaMod( myTexture, alpha );
}



int our_texture::getWidth()
{
	return myWidth;
}

int our_texture::getHeight()
{
	return myHeight;
}

#ifdef _SDL_TTF_H
bool our_texture::loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font *gFont,SDL_Renderer* gRenderer )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        myTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( myTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			myWidth = textSurface->w;
			myHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return myTexture != NULL;
}
#endif

bool our_texture::loadfile( std::string path,SDL_Renderer* gRenderer )
{

	free();


	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{

		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			myWidth = loadedSurface->w;
			myHeight = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}


	myTexture = newTexture;
	return myTexture != NULL;
}

void our_texture::render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	SDL_Rect renderQuad = { x, y, myWidth, myHeight };


	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx( gRenderer, myTexture, clip, &renderQuad, angle, center, flip );
}
