#pragma once
#include <SDL_mixer.h>
#include <SDL.h>
#include <string>
#include "Commons.h"

class Sound
{
public:
	Sound(Mix_Chunk* chunk);
	~Sound();

	bool LoadFromFile(std::string path);
	void Play(std::string path,bool loop, int duration, int chunk_size);

private:
	Mix_Chunk* m_chunk;
};

