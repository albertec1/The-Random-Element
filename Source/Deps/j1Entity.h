#pragma once

#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "p2Point.h"

struct Collider;
struct SDL_Texture;

enum class ENTITY_TYPE
{
	PLAYER,
	AIR_ENEMY,
	GROUND_ENEMY,
	UNDERGROUND_ENEMY,
	DEBUG,
	UNKNOWN_TYPE,
};

class j1Entity : public j1Module
{
public:
	j1Entity(fPoint pos, ENTITY_TYPE type);

	~j1Entity();

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update(float dt, bool do_logic);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	virtual bool Draw();

	virtual void OnCollision(Collider* c1, Collider* c2);

	virtual const Collider* GetCollider()
	{
		return entityCollider;
	}

	virtual const fPoint GetStartingPosition()
	{
		return startingPosition;
	}

	virtual void SetTexture(SDL_Texture* texture) 
	{
		entityTexture = texture;
	}

public:
	ENTITY_TYPE		type;
	Collider*		entityCollider;

	fPoint			startingPosition;
	fPoint			currentPosition;

	SDL_Texture*	entityTexture;
	SDL_Rect		entiyRect;
	iPoint			rectSize;

	iPoint			sprite_size;
	bool			flipped;
	//save and load?

	friend class j1EntityManager;
};