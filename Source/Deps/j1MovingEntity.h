#pragma once

#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"

struct Collider;
struct SDL_Texture;

class j1MovingEntity : public j1Entity
{
public:

	enum class ENTITY_STATES
	{
		ST_UNKNOWN,
		ST_IDLE,
		ST_LEFT_W,
		ST_LEFT_R,
		ST_RIGHT_W,
		ST_RIGHT_R,
		ST_JUMPING,
		ST_SLIDING,
		ST_CLIMBING,
		ST_DYING,
	};

public:
	j1MovingEntity(iPoint pos, ENTITY_TYPE type);

	~j1MovingEntity();

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update(float dt);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	virtual bool Draw();

	virtual const iPoint GetCurrentPosition()
	{
		return current_position;
	}

protected:

	fPoint			starting_velocity;
	fPoint			starting_acceleration;
	fPoint			current_velocity;
	fPoint			current_acceleration;
	fPoint			gravity;

	ENTITY_STATES	state;

	//pathfind?

	friend class j1EntityManager;
};