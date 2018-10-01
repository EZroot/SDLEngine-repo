#include "EAnimation.h"
#include "ETexture.h"
#include <iostream>
#include "ELog.h"

EAnimation::EAnimation()
{
}


EAnimation::~EAnimation()
{
}

SDL_Texture* EAnimation::OnLoad(SDL_Window* window, SDL_Renderer* renderer, char* file,
	SDL_Rect*& clips, int amountOfFrames, int frameWidth, int frameHeight)
{
	//Load our animation sheet
	SDL_Texture* tex = IMG_LoadTexture(renderer, file);
	if (tex == nullptr)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return nullptr;
	}

	//Create and cache our animation frames
	clips = new SDL_Rect[amountOfFrames];
	for (int i = 0; i < amountOfFrames; i++)
	{
		clips[i].x = (i / 1 * frameWidth);
		clips[i].y = (i % 1 * frameHeight);
		clips[i].w = frameWidth;
		clips[i].h = frameHeight;
	}
	return tex;
}

bool EAnimation::OnDraw(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y,
	SDL_Rect*& clips, int amountOfFrames, int frameCounter, int frameSpeed)
{
	int index = frameCounter;

	//Render animation frame
	ETexture::OnDraw(texture, renderer, x, y, &clips[index]);
	return true;
}

bool EAnimation::OnFree(SDL_Texture* texture, SDL_Rect*& clips)
{
	//Free our animation from memory
	delete[] clips;
	clips = nullptr;
	SDL_DestroyTexture(texture);
	texture = nullptr;
	return true;
}
