#include "GBullet.h"
#include "ELog.h"

GBullet::GBullet(BulletType bulletType, SDL_Window * window, SDL_Renderer * renderer)
{
	switch (bulletType)
	{
	case TYPE_WEAK:
		//Loading
		sprite = ETexture::OnLoad(window, renderer, (char*)"Resources/spaceships/Fighter1B.png");
		SPRITE_WIDTH = 16;
		SPRITE_HEIGHT = 12;

		//Create collider
		collider = new ECollider(SPRITE_WIDTH, SPRITE_HEIGHT);
		collider->SetPosition(xPos, yPos);

		//Handler
		particleHandler = new GParticleHandler(window, renderer);

		//Health
		SetHealth(1);

		//Deactivate
		SetActiveStatus(false);
		break;
	default:
		ELog::Print("Error! Enemy Type not set!");
		break;
	}
}

GBullet::~GBullet()
{
}

void GBullet::Events()
{
}

void GBullet::Collided(GEntityCollisionTypes::CollisionType collisionType)
{
	switch (collisionType)
	{
	case GEntityCollisionTypes::COLLISION_ENEMY:
		OnDeath(1, false, false, true); //KILL
		break;
	case GEntityCollisionTypes::COLLISION_PLAYER:
		OnDeath(1, false, false, true); //KILL
		break;
	}
}

void GBullet::Update(float updateStep)
{
	//Apply movement
	xPos += xVel * updateStep;
	yPos += yVel * updateStep;

	//Update Collider
	collider->SetPosition(xPos, yPos);

	//OUT OF BOUNDS!
	if(xPos > 1000 || xPos < -40)
	{
		SetActiveStatus(false);
	}
}

void GBullet::Render(SDL_Renderer * renderer)
{
	ETexture::OnDraw(sprite, renderer, xPos, yPos, 0, NULL, SDL_FLIP_NONE);
}

void GBullet::ParticleUpdate(float updateStep)
{
	particleHandler->UpdateParticles(updateStep);
}

void GBullet::ParticleRender(SDL_Renderer * renderer)
{
	particleHandler->RenderParticles(renderer);
}
