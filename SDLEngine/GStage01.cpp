#include "GStage01.h"
#include "ETexture.h"
#include "ELog.h"
#include "GEntityFactory.h"
#include "GEntityCollisionTypes.h"
#include <string>

GStage01::GStage01(SDL_Window*& window, SDL_Renderer*& renderer)
{
	//Debug
	ELog::Print("Stage01 Loading;");
	currWindow = window;
	currRenderer = renderer;

	//Level
	//Text
	scoreText = EFont::Load("Score: ", renderer);
	comboText = EFont::Load("Combo: ", renderer);

	//Background 
	bgScroller = new GParallaxScroller(currWindow, currRenderer);
	
	//Level handlers
	playerParticleHandler = new GParticleHandler(currWindow,currRenderer);

	//Player
	player = GEntityFactory::Create(GEntityFactory::ENTITY_PLAYER, currWindow, currRenderer);
	player->SetPosition(0, 300);

	//Player Bullets
	playerBulletHandler = new GEntityHandler(30, GEntityFactory::ENTITY_BULLET, currWindow, currRenderer);

	//Boss
	stageBoss = new GEntityHandler(1, GEntityFactory::ENTITY_BOSS, currWindow, currRenderer);

	//Boss bullets
	stageBossBulletHandler = new GEntityHandler(30, GEntityFactory::ENTITY_BULLET, currWindow, currRenderer);

	//Enemies
	weakEnemyHandler = new GEntityHandler(50, GEntityFactory::ENTITY_WEAKENEMY, currWindow, currRenderer);
	strongEnemyHandler = new GEntityHandler(25, GEntityFactory::ENTITY_STRONGENEMY, currWindow, currRenderer);
	asteroidHandler = new GEntityHandler(25, GEntityFactory::ENTITY_ASTEROID, currWindow, currRenderer);

	//Audio
	audioHandler.LoadSounds(EAudio::OnLoadMusic("Resources/sounds/OpenGameArt/battleThemeA.mp3"), EAudio::OnLoadFx("Resources/sounds/OpenGameArt/explosion.wav"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot_Modify.ogg"));
	audioHandler.SetMusicVolume(MIX_MAX_VOLUME / 2 );
	audioHandler.SetChannelVolume(2, MIX_MAX_VOLUME / 3 ); //explosions
	audioHandler.SetChannelVolume(4, MIX_MAX_VOLUME / 2 ); //bullets

	//Debug
	ELog::Print("Stage01 Finished Loading;");
}

//On Stage Deallocation
GStage01::~GStage01()
{
	//Free ptrs
	delete bgScroller;
	 
	SDL_DestroyTexture(scoreText);
	SDL_DestroyTexture(comboText);

	delete player;
	delete playerBulletHandler;
	
	delete weakEnemyHandler;
	delete strongEnemyHandler;
	delete asteroidHandler;

	delete enemyBulletHandler;

	//Set to null
	currWindow = nullptr;
	currRenderer = nullptr;

	bgScroller = nullptr;

	scoreText = nullptr;
	comboText = nullptr;

	player = nullptr;
	playerBulletHandler = nullptr;

	weakEnemyHandler = nullptr;
	strongEnemyHandler = nullptr;
	asteroidHandler = nullptr;

	enemyBulletHandler = nullptr;

	//Debug
	ELog::Print("Freed Stage01.");

}

void GStage01::Events(bool& QUIT_FLAG)
{
	//Player Controls
	player->Events();
}

void GStage01::Collisions()
{
	//Boss
	stageBoss->HandleCollisions(player, GEntityCollisionTypes::COLLISION_PLAYER);

	//Enemy collisions (player should handle this, 1 entity vs like 200 doing the calcs)
	weakEnemyHandler->HandleCollisions(player, GEntityCollisionTypes::COLLISION_PLAYER);
	strongEnemyHandler->HandleCollisions(player, GEntityCollisionTypes::COLLISION_PLAYER);
	asteroidHandler->HandleCollisions(player, GEntityCollisionTypes::COLLISION_PLAYER);

	//Bullet collisions
	playerBulletHandler->HandleCollisions(weakEnemyHandler, GEntityCollisionTypes::COLLISION_ENEMY);
	playerBulletHandler->HandleCollisions(strongEnemyHandler, GEntityCollisionTypes::COLLISION_ENEMY);
	playerBulletHandler->HandleCollisions(asteroidHandler, GEntityCollisionTypes::COLLISION_ENEMY);
	playerBulletHandler->HandleCollisions(stageBoss, GEntityCollisionTypes::COLLISION_ENEMY);

	//Boss bullet
	stageBossBulletHandler->HandleCollisions(player, GEntityCollisionTypes::COLLISION_PLAYER);
}

void GStage01::Update(float updateStep)
{
	//Camera Shaking
	if (comboHandler.shakeCamera)
	{
		gameCamera->Shake(2, 10, 1);
	}

	//SLOW MOTION
	if (EEvent::OnKeyDown(SDL_SCANCODE_T))
	{
		updateStep *= 0.2f;
	}
	//REWINDING!
	if (EEvent::OnKeyDown(SDL_SCANCODE_Y))
	{
		updateStep -= 0.05f;
	}

	//Level
	bgScroller->Update(updateStep);

	//Player bullets 
	player->SetUseableBulletEntity(playerBulletHandler->GetSingleInactiveElementInContainer());

	//Boss bullets
	stageBoss->GetElementsInContainer()[0]->SetUseableBulletEntity(stageBossBulletHandler->GetSingleInactiveElementInContainer());

	//Player Entity
	player->Update(updateStep);
	player->ParticleUpdate(updateStep);

	//Boss
	stageBoss->HandleUpdates(updateStep);
	stageBoss->HandleParticleUpdates(updateStep);

	//EnemyHandlers
	weakEnemyHandler->HandleUpdates(updateStep);
	strongEnemyHandler->HandleUpdates(updateStep);
	asteroidHandler->HandleUpdates(updateStep);
	weakEnemyHandler->HandleParticleUpdates(updateStep);
	strongEnemyHandler->HandleParticleUpdates(updateStep);
	asteroidHandler->HandleParticleUpdates(updateStep);

	//Player bullet Handlers
	playerBulletHandler->HandleUpdates(updateStep);
	playerBulletHandler->HandleParticleUpdates(updateStep);

	//Boss bullet handler
	stageBossBulletHandler->HandleUpdates(updateStep);
	stageBossBulletHandler->HandleParticleUpdates(updateStep);

	//Combo/Score Handler
	comboHandler.UpdateCombos(updateStep);

	//Audio
	if (Mix_PlayingMusic() == 0)
	{
		audioHandler.Play(audioHandler.FX_MUSIC, NULL);
	}

	//Level Spawning
	//100-2000 Ticks - waves of weak
	if (stageTicks > 100 && stageTicks < 2000)
	{
		spawnTimer++;
		if (spawnTimer > 124)
		{
			//Spawn row
			//Weak enemies
			enemySpawner.SpawnLine(weakEnemyHandler, waveCounter, 900, 100 + (rand() % 50), 0, 0, -150 - (rand() % 100),0);
			enemySpawner.SpawnLine(weakEnemyHandler, waveCounter, 900, 300 + (rand() % 50), 0, 0, -150 - (rand() % 100),0);

			waveCounter++;
			spawnTimer = 0;
		}
	}
	//2000-4000 ticks -- Spawn waves of weak and spawn destroyers
	if (stageTicks > 2000 && stageTicks < 4000)
	{
		spawnTimer++;
		if (spawnTimer > 300)
		{
			//Spawn row
			//Weak enemies
			enemySpawner.SpawnLine(weakEnemyHandler, (int)(waveCounter/2), 900, 100 + (rand() % 50), 0, 0, -150 - (rand() % 100), 0);
			enemySpawner.SpawnLine(weakEnemyHandler, (int)(waveCounter/2), 900, 300 + (rand() % 50), 0, 0, -150 - (rand() % 100), 0);
			//Strong enemies
			enemySpawner.SpawnLine(strongEnemyHandler, 1, 900, 100 + (rand() % 50), 0, 0, -70 - (rand() % 70), 0);
			enemySpawner.SpawnLine(strongEnemyHandler, 1, 900, 300 + (rand() % 50), 0, 0, -70 - (rand() % 70), 0);
			
			waveCounter++;
			spawnTimer = 0;
		}
	}
	//4000-6000 ticks -- Spawn waves faster of weak, destroyers come faster but same rate, asteroids enter
	if (stageTicks > 4000 && stageTicks < 6000)
	{
		spawnTimer++;
		if (spawnTimer > 300)
		{
			//Spawn row
			//Weak enemies
			enemySpawner.SpawnLine(weakEnemyHandler, (int)(waveCounter / 2), 900, 100 + (rand() % 50), 0, 0, -250 - (rand() % 100), 0);
			enemySpawner.SpawnLine(weakEnemyHandler, (int)(waveCounter / 2), 900, 300 + (rand() % 50), 0, 0, -250 - (rand() % 100), 0);
			//Strong enemies
			enemySpawner.SpawnLine(strongEnemyHandler, 2, 900, 100 + (rand() % 100+50), 0, 0, -110 - (rand() % 70), 0);
			enemySpawner.SpawnLine(strongEnemyHandler, 2, 900, 300 + (rand() % 100+50), 0, 0, -110 - (rand() % 70), 0);

			waveCounter++;
			spawnTimer = 0;
		}
	}
	//6000-10000
	if (stageTicks > 6000 && stageTicks < 6040)
	{
		spawnTimer = 300;
	}
	if (stageTicks > 6500 && stageTicks < 7000)
	{
		if (spawnTimer > 200)
		{
			//Spawn row
			//Boss
			enemySpawner.SpawnLine(stageBoss, 1, 900, 220, 0, 0, -150, 0);

			ELog::Print("FINAL BOSS SPAWNED!");
			waveCounter++;
			spawnTimer = 0;
		}
	}
	if (stageTicks > 7000)
	{
		spawnTimer++;
		if (spawnTimer > 300)
		{
			ELog::Print(waveCounter);

			//Spawn row
			//Weak enemies
			enemySpawner.SpawnLine(weakEnemyHandler, (int)(waveCounter / 5), 900, 100 + (rand() % 50), 0, 0, -150 - (rand() % 100), 0);
			enemySpawner.SpawnLine(weakEnemyHandler, (int)(waveCounter / 5), 900, 300 + (rand() % 50), 0, 0, -150 - (rand() % 100), 0);

			waveCounter++;
			spawnTimer = 0;
		}
	}
	if (stageTicks > 13000)
	{
		spawnTimer++;
		if (spawnTimer > 300)
		{

			//Spawn row
			//Strong enemy
			enemySpawner.SpawnLine(strongEnemyHandler, 1, 900, 300 + (rand() % 50), 0, 0, -20 - (rand() % 70), 0);

			waveCounter++;
			spawnTimer = 0;
		}
	}
	stageTicks++;

	//Player Death
	if (player->GetHealth() <= 0)
	{
		SetStateQueue(STATE_STAGEDEATH);
	}
	//Boss Death
	if (stageBoss->GetElementsInContainer()[0]->GetHealth() <= 0)
	{
		SetStateQueue(STATE_STAGE01END);
	}
}

void GStage01::Render(SDL_Renderer * renderer)
{
	//Check if stage ended
	/*if (stageTicks >= MAX_STAGE_TICKS)
	{
		ELog::Print("Stage01 complete");
		return;
	}*/

	//Level
	bgScroller->Render(renderer);

	//SCORE
	//scoreText = nullptr;
	std::string s = "Score:    ";
	scoreText = EFont::Load((const char*)s.c_str(), renderer, { 0,0,0 }); //Update text
	EFont::Draw(renderer, scoreText, 28, -3, 64 + s.length(), 17 + s.length()); //Black
	scoreText = EFont::Load((const char*)s.c_str(), renderer); //Update text
	EFont::Draw(renderer, scoreText, 30, 0, 60 + s.length(), 15 + s.length()); //White
	EFont::Free(scoreText);
	//int
	s = std::to_string(comboHandler.playerScore); //Convert int to const char*
	scoreText = EFont::Load((const char*)s.c_str(), renderer, { 0,0,0 }); //Update text
	EFont::Draw(renderer, scoreText, 96, 4, 16 + s.length() * 4, 32 + s.length() * 2); //Black
	scoreText = EFont::Load((const char*)s.c_str(), renderer); //Update text
	EFont::Draw(renderer, scoreText, 94, 8, 14 + s.length() * 4, 30 + s.length() * 2); //White
	EFont::Free(scoreText);
	
	//COMBOS
	s = "Combo  x";
	comboText = EFont::Load((const char*)s.c_str(), renderer, { 0,0,0 }); //Update text
	EFont::Draw(renderer, comboText, 28, 561, 64 + s.length(), 17 + s.length()); //Black
	comboText = EFont::Load((const char*)s.c_str(), renderer); //Update text
	EFont::Draw(renderer, comboText, 30, 564, 60 + s.length(), 15 + s.length());//White
	//int
	s = std::to_string(comboHandler.killMultiplier); //Convert int to const char*
	comboText = EFont::Load((const char*)s.c_str(), renderer, { 0,0,0 }); //Update text
	EFont::Draw(renderer, comboText, 116, 531, 24 + s.length(), 48 + s.length()); //Black
	comboText = EFont::Load((const char*)s.c_str(), renderer); //Update text
	EFont::Draw(renderer, comboText, 114, 534, 22 + s.length(), 44 + s.length()); //White
	EFont::Free(comboText);

	//Health
	s = "Health x";
	comboText = EFont::Load((const char*)s.c_str(), renderer, { 0,0,0 }); //Update text
	EFont::Draw(renderer, comboText, 228, 561, 64 + s.length(), 17 + s.length()); //Black
	comboText = EFont::Load((const char*)s.c_str(), renderer); //Update text
	EFont::Draw(renderer, comboText, 230, 564, 60 + s.length(), 15 + s.length());//White
																				//int
	s = std::to_string(player->GetHealth()); //Convert int to const char*
	comboText = EFont::Load((const char*)s.c_str(), renderer, { 0,0,0 }); //Update text
	EFont::Draw(renderer, comboText, 316, 531, 24 + s.length(), 48 + s.length()); //Black
	comboText = EFont::Load((const char*)s.c_str(), renderer); //Update text
	EFont::Draw(renderer, comboText, 314, 534, 22 + s.length(), 44 + s.length()); //White
	EFont::Free(comboText);
	//Player Entity
	player->Render(renderer);

	//Boss
	stageBoss->HandleRendering(renderer);
	stageBoss->HandleParticleRendering(renderer);

	//Enemies
	weakEnemyHandler->HandleRendering(renderer);
	strongEnemyHandler->HandleRendering(renderer);
	asteroidHandler->HandleRendering(renderer);

	weakEnemyHandler->HandleParticleRendering(renderer);
	strongEnemyHandler->HandleParticleRendering(renderer);
	asteroidHandler->HandleParticleRendering(renderer);

	//Bullets
	playerBulletHandler->HandleRendering(renderer);
	playerBulletHandler->HandleParticleRendering(renderer);

	stageBossBulletHandler->HandleRendering(renderer);
	stageBossBulletHandler->HandleParticleRendering(renderer);
}
