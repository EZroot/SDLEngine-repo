#include "EFont.h"

EFont::~EFont()
{
}

SDL_Texture * EFont::Load(const char * msg, SDL_Renderer* renderer, SDL_Color color)
{
	TTF_Font* font = TTF_OpenFont("Resources/font/alagard.ttf", 24);

	SDL_Surface* msgSurf = TTF_RenderText_Solid(font, msg, color);

	SDL_Texture* msgTex = SDL_CreateTextureFromSurface(renderer, msgSurf);

	TTF_CloseFont(font);
	SDL_FreeSurface(msgSurf);
	//msgSurf = nullptr;

	return msgTex;
}

void EFont::Draw(SDL_Renderer * renderer, SDL_Texture * message, int x, int y, int width, int height)
{
	SDL_Rect msgRect;
	msgRect.x = x;
	msgRect.y = y;
	msgRect.w = width;
	msgRect.h = height;

	SDL_RenderCopy(renderer, message, NULL, &msgRect);
}

void EFont::Free(SDL_Texture * message)
{
	SDL_DestroyTexture(message);
}
