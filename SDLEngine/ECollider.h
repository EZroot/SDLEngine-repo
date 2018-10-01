#ifndef ECOLLIDER_H
#define ECOLLIDER_H
#include <SDL.h>

class ECollider
{
public:
	ECollider(int width, int height);
	~ECollider();

	//axis aligned bounding boxes.
	static bool CheckCollision(SDL_Rect a, SDL_Rect b);
	static bool CheckCollision(SDL_Rect* a, SDL_Rect* b);

	void SetPosition(int xPos, int yPos);
	
	SDL_Rect GetColliderRect();
	int GetColliderXPos();
	int GetColliderYPos();

private:
	SDL_Rect collider_rect;
};

#endif
