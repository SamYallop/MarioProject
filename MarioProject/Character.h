#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"

using namespace std;

class Texture2D;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	float m_collision_radius;
private:
	FACING m_facing_direction;
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~Character();
	virtual void Renderer();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	virtual void AddGravity(float deltaTime);
	virtual void Jump();
	float GetCollisionRadius();
};

