#pragma once
#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	virtual void Update(float deltaTime, SDL_Event e) override;
	virtual void Renderer() override;

	bool GetInjured();
	
private:
	void FlipRightwayUp();
	
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	FACING m_facing_direction;
	float m_movement_speed;

};

