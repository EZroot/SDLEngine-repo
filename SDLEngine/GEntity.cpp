#include "GEntity.h"
#include "ELog.h"

GEntity::~GEntity()
{
	ETexture::OnFree(sprite);
	delete collider;
	collider = nullptr;
}

void GEntity::Shoot(int xSpriteOffset, int ySpriteOffset, int xVel)
{
	//if we have a bullet loaded
	if (bullet != nullptr)
	{
		bullet->SetActiveStatus(true);
		bullet->SetPosition(xPos + xSpriteOffset, yPos + ySpriteOffset);
		bullet->GetCollider()->SetPosition(xPos + xSpriteOffset, yPos + ySpriteOffset);
		bullet->SetVelocity(xVel, 0);
		return;
	}
	ELog::Print("FAILED TO SHOOT. Forget to Entity.SetBulletEntity()???");
	return;
}

void GEntity::DecreaseHealth(int setHealthValue, bool useBigExplosion, bool useSmallExplosion)
{
	entityHealth--;
	if (entityHealth <= 0)
	{
		OnDeath(setHealthValue, true, useBigExplosion,useSmallExplosion);
	}
}

void GEntity::OnDeath(int setHealthValue, bool addToKillCount, bool useBigExplosion, bool useSmallExplosion)
{
	//Add to combo counter
	if (addToKillCount)
	{
		GComboHandler::AddKill();
	}

	if (particleHandler != nullptr)
	{
		//Play explosion sound
		GAudioHandler::Play(GAudioHandler::FX_EXPLOSION, 0);
		//Create particle
		particleHandler->CreateExplosion(xPos, yPos, useBigExplosion, useSmallExplosion);
		//particleHandler->CreateXP(xPos+30, yPos+30, 115,114);
	}
	//Reset health
	SetHealth(setHealthValue);
	//Kill
	SetActiveStatus(false);
}

int GEntity::GetHealth()
{
	return entityHealth;
}

ECollider* GEntity::GetCollider()
{
	return collider;
}

//Getters
//Status
bool GEntity::GetActiveStatus()
{
	return isActive;
}

//Position
int GEntity::GetPosX()
{
	return xPos;
}

int GEntity::GetPosY()
{
	return yPos;
}

int GEntity::GetVelX()
{
	return xVel;
}

int GEntity::GetVelY()
{
	return yVel;
}


void GEntity::SetHealth(int number)
{
	entityHealth = number;
}

void GEntity::SetUseableBulletEntity(GEntity* bulletEntity)
{
	bullet = bulletEntity;
}

//Setters
//Status
void GEntity::SetActiveStatus(bool statusFlag)
{
	isActive = statusFlag;
}

//Position
void GEntity::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void GEntity::SetVelocity(int hSpeed, int vSpeed)
{
	xVel = hSpeed;
	yVel = vSpeed;
}
