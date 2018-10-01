#include "GPlayerController.h"
#include "EEvent.h"
#include "ELog.h"

GPlayerController::GPlayerController(int xStart, int yStart, SDL_Window* window, SDL_Renderer* renderer)
{
	//Loading
	sprite = ETexture::OnLoad(window, renderer, (char*)"Resources/spaceships/AssaultBoatC.png");
	SPRITE_WIDTH = 43;
	SPRITE_HEIGHT = 34;
	
	//Create collider
	collider = new ECollider(SPRITE_WIDTH, SPRITE_HEIGHT);
	
	//Set Positions
	SetPosition(xStart, yStart);
	collider->SetPosition(xStart, yStart);

	//Set Health
	SetHealth(5);
}

GPlayerController::GPlayerController(SDL_Window * window, SDL_Renderer * renderer)
{
	//Loading
	sprite = ETexture::OnLoad(window, renderer, (char*)"Resources/spaceships/AssaultBoatB.png");
	SPRITE_WIDTH = 43;
	SPRITE_HEIGHT = 34;
	
	//Create collider
	collider = new ECollider(SPRITE_WIDTH, SPRITE_HEIGHT);
	
	//Set Positions
	SetPosition(0, 0);
	collider->SetPosition(0, 0);
	
	//Set Health
	SetHealth(5);
}


GPlayerController::~GPlayerController()
{
}

void GPlayerController::Events()
{
	if (isActive)
	{
		PlayerMovement(300);
		PlayerShooting();
	}
}

void GPlayerController::Collided(GEntityCollisionTypes::CollisionType collisionType)
{
	if (isActive)
	{
		switch (collisionType)
		{
		case GEntityCollisionTypes::COLLISION_ENEMY:
			ELog::Print("YOU DIED");
			DecreaseHealth(0, false, true);
			break;
		case GEntityCollisionTypes::COLLISION_BULLET:
			ELog::Print("YOU DIED");
			DecreaseHealth(0, false, true);
			break;
		case GEntityCollisionTypes::COLLISION_PLAYER:
			ELog::Print("YOU DIED");
			DecreaseHealth(0, false, true);
			break;
		}
	}
	return;
}

void GPlayerController::Update(float updateStep)
{
	if (isActive)
	{
		//Update left + right
		xPos += xVel * updateStep;
		yPos += yVel * updateStep;

		//Update Collider
		collider->SetPosition(xPos, yPos);
	}
	return;
}

void GPlayerController::Render(SDL_Renderer * renderer)
{
	if (isActive) {
		SDL_Rect dest;
		dest.x = 0;
		dest.y = 0;
		dest.w = SPRITE_WIDTH;
		dest.h = SPRITE_HEIGHT;

		ETexture::OnDraw(sprite, renderer, xPos, yPos, &dest);
	}
	return;
}

void GPlayerController::ParticleUpdate(float updateStep)
{
}

void GPlayerController::ParticleRender(SDL_Renderer * renderer)
{
}

void GPlayerController::PlayerMovement(int speed)
{
	//Left + Right
	if (EEvent::OnKeyDown(SDL_SCANCODE_LEFT))
	{
		xVel = -speed;
	}
	if (EEvent::OnKeyDown(SDL_SCANCODE_RIGHT))
	{
		xVel = speed;
	}
	if (!EEvent::OnKeyDown(SDL_SCANCODE_LEFT) && !EEvent::OnKeyDown(SDL_SCANCODE_RIGHT))
	{
		xVel = 0;
	}
	//Up + Down
	if (EEvent::OnKeyDown(SDL_SCANCODE_UP))
	{
		yVel = -speed;
	}
	if (EEvent::OnKeyDown(SDL_SCANCODE_DOWN))
	{
		yVel = speed;
	}
	if (!EEvent::OnKeyDown(SDL_SCANCODE_UP) && !EEvent::OnKeyDown(SDL_SCANCODE_DOWN))
	{
		yVel = 0;
	}
}

void GPlayerController::PlayerShooting()
{
	shootTimer++;
	if (shootTimer >= maxShootTimerValue)
	{
		//incase of UNLIKELY overflow
		shootTimer = maxShootTimerValue;
		//Shoot
		if (EEvent::OnKeyDown(SDL_SCANCODE_C))
		{
			//Shoot our set bullet entity
			Shoot(32,4+((rand() % 12)), 800);
			shootTimer = 0;

			//Play FX
			GAudioHandler::Play(GAudioHandler::FX_SHOOT, 0);
			return;
		}
	}
}
