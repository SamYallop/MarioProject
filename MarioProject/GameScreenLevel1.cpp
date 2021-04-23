#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Collisions.h"
#include "Commons.h"
#include "POWBlock.h"


bool GameScreenLevel1::SetUpLevel()
{
	m_pow_block = new POWBlock(m_renderer, m_level_map);
	
	SetLevelMap();

	// Set up player character
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(96, 330), m_level_map);
	
	// Load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		return true;
	}

	

}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete my_character;
	my_character = nullptr;
	delete luigi_character;
	luigi_character = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Renderer()
{
	// Draw the background
	m_background_texture->Renderer(Vector2D(), SDL_FLIP_NONE);
	mario_character->Renderer();
	luigi_character->Renderer();
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// Update character
	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);

	UpdatePOWBlock();

	if(Collisions::Instance()->Circle(mario_character,luigi_character))
	{
		cout << "Circle hit!" << endl;
	}

	if(Collisions::Instance()->Box(mario_character->GetCollisionBox(),luigi_character->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
										{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

	// Clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	// Set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if(m_pow_block->IsAvailable())
		{
			// Collided while jumping
			if(mario_character->IsJumping())
			{
				//DoScreenShake();
				m_pow_block->TakeHit();
				mario_character->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}


