#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load texture!" << std::endl;
		//return false;
	}
	else
	{
		//return true;
	}

	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_can_jump = true;
	m_collision_radius = 15.0f;
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Renderer()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Renderer(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Renderer(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	// Deal with jumping first
	if(m_jumping)
	{
		// Adjust position
		m_position.y -= m_jump_force * deltaTime;

		// Reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		// Is jump forxe 0?
		if(m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}

	AddGravity(deltaTime);
	
	if(m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
	//new_position = m_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::AddGravity(float deltaTime)
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}



// Up to Tutorial 7 after adding jumping