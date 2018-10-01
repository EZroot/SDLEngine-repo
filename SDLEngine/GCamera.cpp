#include "GCamera.h"



GCamera::GCamera()
{
	rectData.x = 0;
	rectData.y = 0;
	rectData.w = SCREEN_WIDTH;
	rectData.h = SCREEN_HEIGHT;
	startX = rectData.x;
	startY = rectData.y;
}

GCamera::~GCamera()
{
}

void GCamera::Update(float updateStep)
{
	//BASED ON INTENSITY
	//x axis min = -intensity, max = intensity
	//1 full move between and back = 1 shake (full wave cycle if u wanna think of it like that)
	if (shakeCounter > 0)
	{
		float a = ((rand() % 100 + 1)*(shakeIntensity));
		float b = ((rand() % 100 + 1)*(shakeIntensity));

		rectData.x += (a - b)*updateStep;
		rectData.y += (a - b)*updateStep;

		shakeCounter--;
	}
	else
	{
		rectData.x = startX;
		rectData.y = startY;
	}
}

void GCamera::Shake(float intensity, int amountOfShakes, float speed)
{
	shakeSpeed = speed;
	shakeIntensity = intensity;
	shakeCounter = amountOfShakes;
}

void GCamera::SetRectData(int w, int h, int x, int y)
{
	rectData.w = w;
	rectData.h = h;
	rectData.x = x;
	rectData.y = y;
}

SDL_Rect GCamera::GetRectData()
{
	return rectData;
}
