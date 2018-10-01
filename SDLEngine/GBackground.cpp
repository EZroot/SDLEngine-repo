#include "GBackground.h"

GBackground::GBackground(char* spriteFile, int image_width, float acceleration, int maxXVel, SDL_Window* window, SDL_Renderer* renderer)
{
	sprite = ETexture::OnLoad(window, renderer, spriteFile);
	accel = acceleration;
	maxSpeed = maxXVel;
	imgWidth = image_width;
}

GBackground::~GBackground()
{
}

//ONLY LEFT SCROLLING
void GBackground::Update(float updateStep)
{
	accelValue += accel;

	//Acceleration our background
	xVel -= accelValue * updateStep;

	//Cap our horizontal speed
	if (xVel < -maxSpeed)
	{
		xVel = -maxSpeed;
	}

	//Update background position
	xPos += (float)(xVel * updateStep);

	//Reset position scrolling to the LEFT
	if (xPos < -imgWidth)
	{
		xPos = 0;
	}
}

void GBackground::Render(SDL_Renderer * renderer)
{
	ETexture::OnDraw(sprite, renderer, (int)xPos+imgWidth, (int)yPos);
	ETexture::OnDraw(sprite, renderer, (int)xPos, (int)yPos);
}
