#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include <vector>

#include "CharacterKoopa.h"

class POWBlock;

class Character;

class Texture2D;

class CharacterMario;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	Character* my_character;
	Character* mario_character;
	Character* luigi_character;
	void SetLevelMap();
	LevelMap* m_level_map;
	POWBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenshake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	vector<CharacterKoopa*> m_enemies;
	float newEnemyTimer;
	
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();

};

