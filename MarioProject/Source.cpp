#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"

// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//SDL_Texture* g_texture = nullptr;
Texture2D* g_texture = nullptr;


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
}

bool Update()
{
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

	return false;

}

void Renderer()
{
	// Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	g_texture->Renderer(Vector2D(), SDL_FLIP_NONE);

	// Update the screen
	SDL_RenderPresent(g_renderer);

}

//void FreeTexture()
//{
//	if(g_texture != nullptr)
//	{
//		SDL_DestroyTexture(g_texture);
//		g_texture = nullptr;
//	}
//}

//SDL_Texture* LoadTextureFromFile(string path)
//{
//	//FreeTexture();
//	
//	SDL_Texture* p_texture = nullptr;
//
//	// Load the image
//	SDL_Surface* p_surface = IMG_Load(path.c_str());
//
//	// Create the texture from the pixels on the surface
//	if (p_surface != nullptr)
//	{
//		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
//		if (p_texture == nullptr)
//		{
//			cout << "Unable to create texture from surface, Error: " << SDL_GetError();
//		}
//		// Remove the loaded surface now that we have a texture
//		SDL_FreeSurface(p_surface);
//	}
//
//	else
//	{
//		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
//	}
//
//	// Return the texture
//	return p_texture;
//}



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
	return true;
}


int main(int argc, char* args[])
{

	// Function prototypes
	InitSDL();
	if (InitSDL())
	{
		// Flag to check if we wish to quit
		bool quit = false;

		// Game Loop
		while (!quit)
		{
			Renderer();
			quit = Update();
		}
	}
	SDL_Texture* LoadTextureFromFile(string path);
	Renderer();
	//FreeTexture();
	CloseSDL();

	return 0;
}