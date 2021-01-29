#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"

// Globals
SDL_Window* g_window = nullptr;

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
	return true;
}

void CloseSDL()
{
	// Release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	// Event handler
	SDL_Event e;

	// Get events
	SDL_PollEvent(&e);

	// Handle the events
	switch (e.type)
	{
		// Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}
	
	return false;
	
}


int main(int argc, char* args[])
{

	// Function prototypes
	bool InitSDL();
	if(InitSDL())
	{
		// Flag to check if we wish to quit
		bool quit = false;

		// Game Loop
		while(!quit)
		{
			quit = Update();
		}
	}
	CloseSDL();

	return 0;
}
