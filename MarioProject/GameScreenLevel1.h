#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"

class Character;

class Texture2D;

class CharacterMari0;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	Character* my_character;
	Character* mario_character;
	Character* luigi_character;
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;
};

