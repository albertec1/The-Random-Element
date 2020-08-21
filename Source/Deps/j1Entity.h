#pragma once

#include "j1Module.h"
#include "SDL/include/SDL.h"
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

	~j1Entity();

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
	iPoint			current_position;

	SDL_Texture*	entity_texture;
	SDL_Rect		entity_rect;

	iPoint			sprite_size;
	bool			flipped;

	//save and load?

	friend class j1EntityManager;
};