#ifndef EFONT_H
#define EFONT_H
#include <SDL.h>
#include <SDL_ttf.h>
class EFont
{
public:
	~EFont();

	static SDL_Texture* Load(const char* msg, SDL_Renderer* renderer, SDL_Color color = { 255,255,255 });
	static void Draw(SDL_Renderer* renderer, SDL_Texture* message, int x, int y, int width, int height);
	static void Free(SDL_Texture* message);
};
#endif
