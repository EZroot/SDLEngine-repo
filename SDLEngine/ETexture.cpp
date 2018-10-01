#include "ETexture.h"
#include <iostream>
#include <SDL_image.h>

ETexture::ETexture()
{
}


ETexture::~ETexture()
{
}

SDL_Texture* ETexture::OnLoad(SDL_Window* window, SDL_Renderer* renderer, char* file)
{
	//Load texture
	SDL_Texture* tex = IMG_LoadTexture(renderer, file);
	if (tex == nullptr)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return nullptr;
	}
	return tex;
}

bool ETexture::OnDraw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect dst,
	SDL_Rect *clip)
{
	SDL_RenderCopy(renderer, texture, clip, &dst);
	return true;
}

bool ETexture::OnDraw(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y,
	SDL_Rect *clip)
{
	//Render a section of a texture
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	}
	OnDraw(texture, renderer, dst, clip);
	return true;
}

bool ETexture::OnDraw(SDL_Texture * texture, SDL_Renderer * renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flipType, SDL_Rect * clip)
{
	//Render a section of a texture
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	}
	SDL_RenderCopyEx(renderer, texture, clip, &dst, angle, center, flipType);
	return true;
}

bool ETexture::OnDraw(SDL_Texture * texture, SDL_Renderer * renderer, float x, float y, double angle, SDL_Point * center, SDL_RendererFlip flipType, SDL_Rect * clip)
{

	//Render a section of a texture
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	}
	SDL_RenderCopyEx(renderer, texture, clip, &dst, angle, center, flipType);
	return true;
}

bool ETexture::OnFree(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	return true;
}