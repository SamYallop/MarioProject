#pragma once
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Renderer();
	virtual void Update(float deltaTime, SDL_Event e);
};

