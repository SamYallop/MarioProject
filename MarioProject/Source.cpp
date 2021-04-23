#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//SDL_Texture* g_texture = nullptr;
Texture2D* g_texture = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
Mix_Music* g_music = nullptr;

void LoadMusic(string path)
{
	g_music = Mix_LoadMUS(path.c_str());
	if(g_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}
}

void CloseSDL()
{
	// Release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	// Clear the texture
	void FreeTexture();
	
	// Release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_texture = nullptr;

	// Release the texture
	delete g_texture;
	g_texture = nullptr;

	// Destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	// Clear up music
	Mix_FreeMusic(g_music);
	g_music = nullptr;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();
	
	// Event handler
	SDL_Event e;

	// Get events
	SDL_PollEvent(&e);

	// Handle the events
	switch(e.type)
	{
	// Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	
	return false;

}

void Renderer()
{
	// Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//g_texture->Renderer(Vector2D(), SDL_FLIP_NONE);
	game_screen_manager->Renderer();

	// Update the screen
	SDL_RenderPresent(g_renderer);

}


bool InitSDL()
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	else
	{
		// Setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		// Did the window get created?
		if (g_window == nullptr)
		{
			// Window Failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

	}
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if(g_renderer != nullptr)
	{
		// Init PNG loading
		int imageFlags = IMG_INIT_PNG;
		if(!(IMG_Init(imageFlags)& imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
		// Load the background texture
		g_texture = new Texture2D(g_renderer);
		if (!g_texture->LoadFromFile("Images/test.bmp"))
		{
			return false;
		}
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}

	// Initialise the mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)< 0)
	{
		cout << "Mixer could not initialise. Error: " << Mix_GetError();
		return false;
	}
	return true;
}


int main(int argc, char* args[])
{

	// Function prototypes
	//InitSDL();
	if (InitSDL())
	{
		LoadMusic("Music/Mario.mp3");
		if(Mix_PlayingMusic() ==0)
		{
			Mix_PlayMusic(g_music, -1);
		}
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		// Set the time
		g_old_time = SDL_GetTicks();
		// Flag to check if we wish to quit
		bool quit = false;

		// Game Loop
		while (!quit)
		{
			Renderer();
			quit = Update();
		}
	}
	//SDL_Texture* LoadTextureFromFile(string path);
	//Renderer();
	//FreeTexture();
	CloseSDL();

	return 0;
}