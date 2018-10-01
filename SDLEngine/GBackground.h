#ifndef GBACKGROUND_H
#define GBACKGROUND_G
#include <SDL.h>
#include "ETexture.h"

class GBackground
{
public:
	GBackground(char* spriteFile, int image_width, float acceleration, int maxXVel, SDL_Window* window, SDL_Renderer* renderer);
	~GBackground();

	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

	//Sprite
	SDL_Texture* sprite;

	//Position
	float xPos = 0;
	float yPos = 0;
	
	//Physics
	float xVel = -100.f; //initial speed
	float yVel = 0;

	//Img data
	int imgWidth = 2000;

	//Acelleartion
	float accel = 0.f; //modifier
	float accelValue = 0.f; //value
	int maxSpeed = 0; //max
};

#endif