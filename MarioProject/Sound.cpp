#include "Sound.h"

#include <iostream>
using namespace std;

Sound::Sound(Mix_Chunk* chunk)
{
	m_chunk = chunk;
}

Sound::~Sound()
{
	m_chunk = nullptr;
}

bool Sound::LoadFromFile(string path)
{
	m_chunk = Mix_LoadWAV(path.c_str());
	if (m_chunk == nullptr)
	{
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
	}
	return true;
}


void Sound::Play(string path, bool loop, int duration, int chunk_size)
{
	LoadFromFile(path);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, chunk_size) < 0)
	{
		cout << "Mixer could not initialise. Error: " << Mix_GetError();
	}

}
