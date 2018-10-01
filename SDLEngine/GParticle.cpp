#include "GParticle.h"
#include "ELog.h"


GParticle::GParticle(ParticleType type, SDL_Window* window, SDL_Renderer* renderer)
{
	switch (type)
	{
	case TYPE_EXPLOSION:
		particleSprite = EAnimation::OnLoad(window, renderer, (char*)"Resources/explosions/96x96explosion12frames.png", particleAnimationClips, 12, 96, 96);
		SetParticleType(TYPE_EXPLOSION);
		SetActiveStatus(true);
		SetPosition(0,0);
		currFrameCounter = 0;
		break;
	case TYPE_BIGEXPLOSION:
		particleSprite = EAnimation::OnLoad(window, renderer, (char*)"Resources/explosions/167x167explosion12frames.png", particleAnimationClips, 12, 167, 167);
		SetParticleType(TYPE_BIGEXPLOSION);
		SetActiveStatus(true);
		SetPosition(0, 0);
		currFrameCounter = 0;
		break;
	case TYPE_BULLETEXPLOSION:
		particleSprite = EAnimation::OnLoad(window, renderer, (char*)"Resources/explosions/bulletexplosion.png", particleAnimationClips, 6, 25, 25);
		SetParticleType(TYPE_BULLETEXPLOSION);
		SetActiveStatus(true);
		SetPosition(0, 0);
		currFrameCounter = 0;
		break;
	default:
		ELog::Print("Couldnt create partile");
		return;
		break;
	}
}


GParticle::~GParticle()
{
	EAnimation::OnFree(particleSprite, particleAnimationClips);
}

void GParticle::Update(float updateStep)
{
	if (isActive)
	{
		//Get particle type
		switch (currentType)
		{
		case TYPE_EXPLOSION:
			//If explosion animation ends
			if (currFrameCounter > 12)
			{
				//Reset animation
				currFrameCounter = 0.0f;
				//Disable obj
				SetActiveStatus(false);
			}
			//Update animation
			currFrameCounter += 9.0f*updateStep;
			break;
		case TYPE_BIGEXPLOSION:
			//If explosion animation ends
			if (currFrameCounter > 12)
			{
				//Reset animation
				currFrameCounter = 0.0f;
				//Disable obj
				SetActiveStatus(false);
			}
			//Update animation
			currFrameCounter += 9.0f*updateStep;
			break;
		case TYPE_BULLETEXPLOSION:
			//If explosion animation ends
			if (currFrameCounter > 6)
			{
				//Reset animation
				currFrameCounter = 0.0f;
				//Disable obj
				SetActiveStatus(false);
			}
			//Update animation
			currFrameCounter += 15.0f*updateStep;
			break;
		}
	}
}

void GParticle::Render(SDL_Renderer * renderer)
{
	if (isActive)
	{
		EAnimation::OnDraw(particleSprite, renderer, xPos-36, yPos-36, particleAnimationClips, 12, (int)currFrameCounter, 1);
	}
}

//Getters
int GParticle::GetCurrentParticleType()
{
	return currentType;
}

bool GParticle::GetActiveStatus()
{
	return isActive;
}

int GParticle::GetPosX()
{
	return xPos;
}

int GParticle::GetPosY()
{
	return yPos;
}

int GParticle::GetXVel()
{
	return xVel;
}

int GParticle::GetYVel()
{
	return yVel;
}

//Setters
void GParticle::SetParticleType(ParticleType type)
{
	currentType = type;
}

void GParticle::SetActiveStatus(bool statusFlag)
{
	isActive = statusFlag;
}

void GParticle::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void GParticle::SetVelocity(int x, int y)
{
	xVel = x;
	yVel = y;
}

//Functions
void GParticle::XPMovement(float updateStep)
{
	//Slow down to a stop
	if (xVel > 0 && yVel > 0)
	{
		xVel--;
		yVel--;
	}
	else if (xVel < 0 && yVel < 0)
	{
		xVel++;
		yVel++;
	}
	else
	{
		xVel = 0;
		yVel = 0;
	}

	//Translate
	xPos += xVel * updateStep;
	yPos += yVel * updateStep;

}
