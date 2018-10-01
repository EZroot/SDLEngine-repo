#ifndef GCAMERA_H
#define GCAMERA_H
#include <SDL.h>
#include <random>

class GCamera
{
public:
	GCamera();
	~GCamera();

	void Update(float updateStep);

	//How much shake for how long
	void Shake(float intensity, int amountOfShakes, float speed);

	//Setters
	void SetRectData(int w, int h, int x, int y);
	//Getters
	SDL_Rect GetRectData();

	//Const
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//Position
	int startX = 0;
	int startY = 0;

	//Variables
	SDL_Rect rectData;

	float shakeSpeed = 0.0f;
	float shakeIntensity = 0.0f;
	int shakeCounter = 0;
	bool isShaking = false;
};

#endif