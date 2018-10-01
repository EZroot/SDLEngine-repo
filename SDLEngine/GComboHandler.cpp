#include "GComboHandler.h"
#include "ELog.h"


GComboHandler::GComboHandler()
{
}


GComboHandler::~GComboHandler()
{
}

void GComboHandler::AddKill()
{
	killCounter++;
}

void GComboHandler::AddScore(int score)
{
	switch(killMultiplier)
	{
	case 2:
		playerScore += score * 2;
		break;
	case 3:
		playerScore += score * 3;
		break;
	case 4:
		playerScore += score * 4;
		break;
	case 5:
		playerScore += score * 5;
		break;
	default:
		playerScore += score;
		break;
	}
}

void GComboHandler::UpdateCombos(float updateStep)
{
	//If we just killed someone
	if (killCounter > (prevCounter+1))
	{
		prevCounter = killCounter; //record kill
		shakeCamera = true;

		//check if our timer is running for a multiplier
		if (killMultiplier <= 3 && killTimer > 0) //limit multiplier to 3
		{
			killMultiplier++; //go up a multiplier
		}
		//reset timer 
		killTimer = 60;
	}

	//Update timer
	if (killTimer > 0)
	{
		killTimer -= 1;
	}

	//End camera shake
	if (killTimer <= 50)
	{
		//Default camera shake
		shakeCamera = false;
	}
	//End multiplier
	if (killTimer <= 0)
	{
		killMultiplier = 0;
		killTimer = 0;
	}
}

int GComboHandler::killCounter = 0;
int GComboHandler::killMultiplier = 0;
int GComboHandler::playerScore = 0;