#ifndef GSTAGE01_H
#define GSTAGE01_H
#include "EFont.h"

#include "GGameState.h"
#include "GEntityHandler.h"
#include "GParticleHandler.h"
#include "GComboHandler.h"
#include "GEntity.h"
#include "GParallaxScroller.h"
#include "GEnemySpawner.h"
#include <random>

//Audio
#include "GAudioHandler.h"

class GStage01 : public GGameState
{
public:
	GStage01(SDL_Window*& window, SDL_Renderer*& renderer);
	~GStage01();

	//Stage Functions
	void Events(bool& QUIT_FLAG);
	void Collisions();
	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

private:

	//Stupid SDL bullshit that shouldve been removed
	SDL_Window* currWindow = nullptr;
	SDL_Renderer* currRenderer = nullptr;

	//Level
	//Progress
	const int MAX_STAGE_TICKS = 10000; //max level length
	int stageTicks = 0; //how far along the level we are
	int spawnTimer = 0; //interval between enemy spawns
	int waveCounter = 0; //how many times the enemies been spawned

	//Text
	SDL_Texture* scoreText = nullptr;
	SDL_Texture* comboText = nullptr;

	//Background
	GParallaxScroller* bgScroller = nullptr;

	//Particles
	GParticleHandler* playerParticleHandler = nullptr;

	//Player
	GEntity* player = nullptr;
	GEntityHandler* playerBulletHandler = nullptr;

	//Boss
	GEntityHandler* stageBoss = nullptr;
	GEntityHandler* stageBossBulletHandler = nullptr;

	//Handlers
	GEntityHandler* weakEnemyHandler = nullptr;
	GEntityHandler* strongEnemyHandler = nullptr;
	GEntityHandler* asteroidHandler = nullptr;

	GEntityHandler* enemyBulletHandler = nullptr;

	//Spawner
	GEnemySpawner enemySpawner;

	//Combo Controler
	GComboHandler comboHandler;

	//Stage audio
	GAudioHandler audioHandler;
};

#endif