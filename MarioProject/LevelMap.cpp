#include "LevelMap.h"

/*
 * When making a map remember:
 * 0 = Empty space, 1= Blocked/Occupied Space
 */

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	// Allocate memory for the level map
	m_map = new int* [MAP_HEIGHT];
	for(unsigned int i = 0; i < MAP_HEIGHT; i ++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}

	// Populate the array
	for(unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for(unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	// Delete all elements of the array
	for(unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[]m_map[i];
	}
	delete[]m_map;
}

int LevelMap::GetTileAt(unsigned h, unsigned w)
{
	if(h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}
	return 0;
}
