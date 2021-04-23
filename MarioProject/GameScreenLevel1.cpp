#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Collisions.h"
#include "Commons.h"
#include "POWBlock.h"


bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();
	
	m_pow_block = new POWBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;

	newEnemyTimer = 10.0f;
	

	// Set up player character
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(96, 330), m_level_map);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	
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
	m_enemies.clear();
}

void GameScreenLevel1::Renderer()
{
	// Draw the enemies
	for(int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Renderer();
	}
	// Draw the background
	m_background_texture->Renderer(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	mario_character->Renderer();
	luigi_character->Renderer();
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	/*
	 * Do the screen shake if required
	 */
	if(m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		// End shake after duration
		if(m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	// Update character
	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);

	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();
	
	if(Collisions::Instance()->Circle(mario_character,luigi_character))
	{
		cout << "Circle hit!" << endl;
	}

	if(Collisions::Instance()->Box(mario_character->GetCollisionBox(),luigi_character->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	newEnemyTimer -= deltaTime;
	if(newEnemyTimer <= 0.0f)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		newEnemyTimer = 10.0f;
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
				DoScreenshake();
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

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if(!m_enemies.empty())
	{
		int enemyIndexToSelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			// Check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				// Is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))m_enemies[i]->SetAlive(false);
			}
			// Now do the update

			m_enemies[i]->Update(deltaTime, e);

			// Check to see if enemy collides with player
			if((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				// Ignore collisions if behind pipe
			}
			else
			{
				if(Collisions::Instance()->Circle(m_enemies[i], mario_character))
				{
					if(m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						// Kill mario
					}
				}
			}
			// If the enemy is no longer alive then schedule it for deletion
			if(!m_enemies[i]->GetAlive())
			{
				enemyIndexToSelete = i;
			}
		}

		// Remove dead enemies -1 each update

		if(enemyIndexToSelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToSelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back(new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed));
}



