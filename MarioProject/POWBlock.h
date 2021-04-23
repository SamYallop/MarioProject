#pragma once
#include <SDL_render.h>
#include "Commons.h"
#include "LevelMap.h"

class Texture2D;

class POWBlock
{
public:
	POWBlock(SDL_Renderer* renderer, LevelMap* map);
	~POWBlock();

	virtual void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y , m_single_sprite_w, m_single_sprite_h); };
	void TakeHit();
	bool IsAvailable() { return m_num_hits_left > 0; };


	Vector2D m_position;
	
	
private:
	SDL_Renderer* m_renderer;
	//Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;
};

