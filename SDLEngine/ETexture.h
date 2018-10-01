#ifndef ETexture_H_
	#define ETexture_H_

#include <SDL.h>
#include <SDL_image.h>

class ETexture
{
public:
	ETexture();
	~ETexture();

	static SDL_Texture* OnLoad(SDL_Window* window, SDL_Renderer* renderer, char* file);
	static bool OnDraw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect dst,
		SDL_Rect *clip = nullptr);	
	static bool OnDraw(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y,
		SDL_Rect *clip = nullptr);
	static bool OnDraw(SDL_Texture * texture, SDL_Renderer * renderer, int x, int y, double angle,
		SDL_Point* center, SDL_RendererFlip flipType, SDL_Rect * clip = nullptr);
	static bool OnDraw(SDL_Texture * texture, SDL_Renderer * renderer, float x, float y, double angle,
		SDL_Point* center, SDL_RendererFlip flipType, SDL_Rect * clip = nullptr);
	static bool OnFree(SDL_Texture* tex);
};

#endif