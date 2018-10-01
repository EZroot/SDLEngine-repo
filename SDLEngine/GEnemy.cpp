#include "GEnemy.h"
#include "ELog.h"


//Enemy Setup and Deactivation
GEnemy::GEnemy(EnemyType enemyType, SDL_Window * window, SDL_Renderer * renderer)
{
	//Object setup
	switch (enemyType)
	{
	case TYPE_WEAK:
		//Loading
		sprite = ETexture::OnLoad(window, renderer, (char*)"Resources/spaceships/Bomber2.png");
		SPRITE_WIDTH = 23;
		SPRITE_HEIGHT = 28;

		//Set type
		currentType = TYPE_WEAK;

		//Create collider
		collider = new ECollider(SPRITE_WIDTH, SPRITE_HEIGHT);
		collider->SetPosition(xPos, yPos);

		//Create particles
		particleHandler = new GParticleHandler(window, renderer);

		//Set Health
		SetHealth(1);
		//Deactivate
		SetActiveStatus(false);
		break;
	case TYPE_STRONG:
		//Loading
		sprite = ETexture::OnLoad(window, renderer, (char*)"Resources/spaceships/Destroyer.png");
		SPRITE_WIDTH = 130;
		SPRITE_HEIGHT = 45;

		//Set type
		currentType = TYPE_STRONG;

		//Create collider
		collider = new ECollider(SPRITE_WIDTH, SPRITE_HEIGHT);
		collider->SetPosition(xPos, yPos);

		//Create particles
		particleHandler = new GParticleHandler(window, renderer);

		//Set Health
		SetHealth(8);
		//Deactivate
		SetActiveStatus(false);
		break;
	case TYPE_ASTEROID:
		//Loading
		sprite = ETexture::OnLoad(window, renderer, (char*)"Resources/spaceships/Bomber.png");
		SPRITE_WIDTH = 30;
		SPRITE_HEIGHT = 26;

		//Set type
		currentType = TYPE_ASTEROID;

		//Create collider
		collider = new ECollider(SPRITE_WIDTH, SPRITE_HEIGHT);
		collider->SetPosition(xPos, yPos);

		//Create particles
		particleHandler = new GParticleHandler(window, renderer);

		//Set Health
		SetHealth(3);
		//Deactivate
		SetActiveStatus(false);
		break;
	case TYPE_BOSS:
		//Loading
		sprite = ETexture::OnLoad(window, renderer, (char*)"Resources/spaceships/Battleship.png");
		SPRITE_WIDTH = 368;
		SPRITE_HEIGHT = 160;

		//Set type
		currentType = TYPE_BOSS;

		//Create collider
		collider = new ECollider(SPRITE_WIDTH, SPRITE_HEIGHT);
		collider->SetPosition(xPos, yPos);

		//Create particles
		particleHandler = new GParticleHandler(window, renderer);

		//Set Health
		SetHealth(700);
		//Deactivate
		SetActiveStatus(false);
		ELog::Print("BOSS SPAWNED");
		break;
	default:
		ELog::Print("Error! Enemy Type not set!");
		break;
	}
}

GEnemy::~GEnemy()
{
}

void GEnemy::Events()
{
}

void GEnemy::Collided(GEntityCollisionTypes::CollisionType collisionType)
{
	switch (currentType)
	{
	case TYPE_WEAK:
		switch (collisionType)
		{
		case GEntityCollisionTypes::COLLISION_PLAYER:
			GComboHandler::AddScore(1);
			DecreaseHealth(1, false, false);
			break;
		case GEntityCollisionTypes::COLLISION_BULLET:
			GComboHandler::AddScore(1);
			DecreaseHealth(1, false, false);
			break;
		case GEntityCollisionTypes::COLLISION_ENEMY:
			GComboHandler::AddScore(1);
			DecreaseHealth(1, false, false);
			break;
		}
		break;
	case TYPE_STRONG:
		switch (collisionType)
		{
		case GEntityCollisionTypes::COLLISION_PLAYER:
			GComboHandler::AddScore(3);
			DecreaseHealth(8,true);
			break;
		case GEntityCollisionTypes::COLLISION_BULLET:
			GComboHandler::AddScore(3);
			DecreaseHealth(8, true);
			break;
		case GEntityCollisionTypes::COLLISION_ENEMY:
			GComboHandler::AddScore(3);
			DecreaseHealth(8, true);
			break;
		}
		break;
	case TYPE_ASTEROID:
		switch (collisionType)
		{
		case GEntityCollisionTypes::COLLISION_PLAYER:
			GComboHandler::AddScore(3);
			DecreaseHealth(3,false,false);
			break;
		case GEntityCollisionTypes::COLLISION_BULLET:
			GComboHandler::AddScore(3);
			DecreaseHealth(3, false, false);
			break;
		case GEntityCollisionTypes::COLLISION_ENEMY:
			GComboHandler::AddScore(3);
			DecreaseHealth(3, false, false);
			break;
		}
		break;
	case TYPE_BOSS:
			switch (collisionType)
			{
			case GEntityCollisionTypes::COLLISION_PLAYER:
				GComboHandler::AddScore(15);
				DecreaseHealth(3, true, false);
				break;
			case GEntityCollisionTypes::COLLISION_BULLET:
				GComboHandler::AddScore(15);
				DecreaseHealth(3, true, false);
				break;
			case GEntityCollisionTypes::COLLISION_ENEMY:
				GComboHandler::AddScore(15);
				DecreaseHealth(3, true, false);
				break;
			}
		break;
	default:
		ELog::Print("No enemy type selected");
	}
}

void GEnemy::Update(float updateStep)
{
	switch (currentType)
	{
	case TYPE_WEAK:
		//Apply movement
		xPos += xVel * updateStep;
		yPos += yVel * updateStep;

		//Update Collider
		collider->SetPosition(xPos, yPos);

		//reached outside of screen
		if (xPos <= -64)
		{
			//destroy
			SetActiveStatus(false);
		}
		break;
	case TYPE_STRONG:
		//Apply movement
		xPos += xVel * updateStep;
		yPos += yVel * updateStep;

		//Update Collider
		collider->SetPosition(xPos, yPos);

		//reached outside of screen
		if (xPos <= -164)
		{
			//destroy
			SetActiveStatus(false);
		}
		break;
	case TYPE_ASTEROID:
		//Apply movement
		xPos += xVel * updateStep;
		yPos += yVel * updateStep;

		//Update Collider
		collider->SetPosition(xPos, yPos);

		//reached outside of screen
		if (xPos <= -64 || xPos >= 1200)
		{
			//destroy
			SetActiveStatus(false);
		}
		break;
	case TYPE_BOSS:
		//Apply movement
		xPos += xVel * updateStep;
		yPos += yVel * updateStep;

		//Update Collider
		collider->SetPosition(xPos, yPos);

		//Movement
		BossAI();
			break;
	}
}

void GEnemy::Render(SDL_Renderer * renderer)
{
	ETexture::OnDraw(sprite, renderer, xPos, yPos, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void GEnemy::ParticleUpdate(float updateStep)
{
	//Update particles
	particleHandler->UpdateParticles(updateStep);
}

void GEnemy::ParticleRender(SDL_Renderer * renderer)
{
	//Draw particles
	particleHandler->RenderParticles(renderer);
}

void GEnemy::BossAI()
{
	//Move faster as we get destroyed
	if (GetHealth() < 500)
	{
		bossMoveSpeed = 100;
	}
	if (GetHealth() < 400)
	{
		bossMoveSpeed = 200;
	}
	if (GetHealth() < 350)
	{
		bossMoveSpeed = 300;
	}
	if (GetHealth() < 250)
	{
		bossMoveSpeed = 500;
	}

	//Boss Movement
	if (xPos <= 450)
	{
		xVel = 0;
		yVel = 0;

		//if we stopped
		if (moveUp == true)
		{
			yVel = bossMoveSpeed;
		}
		if (moveDown == true)
		{
			yVel = -bossMoveSpeed;
		}

		if (yPos > 450)
		{
			moveUp = false;
			moveDown = true;
		}
		if (yPos <= 0)
		{
			moveDown = false;
			moveUp = true;
		}

		//Stops the boss and waits for 100 ticks
		if (stopTimer < 0)
		{
			xVel = 0;
			yVel = 0;

			//Add shoot code
			shootTimer--;
			if (shootTimer < 0)
			{
				if(GetHealth()<600)
				{
					Shoot(5, 74, -600);
					shootTimer = 15;
				}
				if (GetHealth()<400)
				{
					Shoot(5, 74, -700);
					shootTimer = 10;
				}
				if (GetHealth()<300)
				{
					Shoot(5, 74, -800);
					shootTimer = 5;
				}
				if (GetHealth()<200)
				{
					Shoot(5, 74, -900);
					shootTimer = 2;
				}
			}
		}

		//Reset Timer
		if (stopTimer < -100)
		{
			//Reset timer
			stopTimer = 200;
		}
		stopTimer--;
	}
}
