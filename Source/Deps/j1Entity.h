#pragma once

#include "j1Module.h"
#include "p2Point.h"

struct Collider;
struct SDL_Texture;

enum class ENTITY_TYPE
{
	PLAYER,
	FLYING_ENEMY,
	WALKING_ENEMY,
	UNKNOWN_TYPE,
};

class j1Entity : public j1Module
{
public:
	j1Entity(iPoint pos, ENTITY_TYPE type);

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update(float dt);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	virtual bool Draw();

	virtual void OnCollision(Collider* c1, Collider* c2);

	virtual const Collider* GetCollider()
	{
		return entity_collider;
	}

	virtual const iPoint GetStartingPosition()
	{
		return starting_position;
	}

	virtual void SetTexture(SDL_Texture* texture) 
	{
		entity_texture = texture;
	}

protected:
	ENTITY_TYPE		type;
	Collider*		entity_collider;

	iPoint			starting_position;
	fPoint			starting_velocity;
	fPoint			starting_acceleration;
	iPoint			current_position;
	fPoint			current_velocity;
	fPoint			current_acceleration;

	SDL_Texture*	entity_texture;
	SDL_Rect		entity_rect;

	iPoint			sprite_size;
	bool			flipped;

	friend class j1EntityManager;
};