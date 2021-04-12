#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>

bool GameScreenLevel1::SetUpLevel()
{
	// Set up player character
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(96, 330));
	
	// Load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
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
}

void GameScreenLevel1::Renderer()
{
	// Draw the background
	m_background_texture->Renderer(Vector2D(), SDL_FLIP_NONE);
	mario_character->Renderer();
	luigi_character->Renderer();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// Update character
	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);
}