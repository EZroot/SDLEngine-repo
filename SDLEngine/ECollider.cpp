#include "ECollider.h"



ECollider::ECollider(int width, int height)
{
	//Bounding box
	collider_rect.w = width;
	collider_rect.h = height;
}

ECollider::~ECollider()
{

}

//axis aligned bounding boxes
bool ECollider::CheckCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}
	//If none of the sides from A are outside B
	return true;
}

bool ECollider::CheckCollision(SDL_Rect * a, SDL_Rect * b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;

	//Calculate the sides of rect B
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}
	//If none of the sides from A are outside B
	return true;
}

void ECollider::SetPosition(int xPos, int yPos)
{
	collider_rect.x = xPos;
	collider_rect.y = yPos;
}

SDL_Rect ECollider::GetColliderRect()
{
	return collider_rect;
}

int ECollider::GetColliderXPos()
{
	return collider_rect.x;
}

int ECollider::GetColliderYPos()
{
	return collider_rect.y;
}
