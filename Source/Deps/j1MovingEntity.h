#pragma once

#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "j1Animation.h"

struct Collider;
struct SDL_Texture;

class j1MovingEntity : public j1Entity
{
public:

	enum class ENTITY_STATES
	{
		ST_UNKNOWN,
		ST_IDLE,
		ST_IDLE_FLIPPED,
		ST_LEFT,
		ST_AIR_LEFT,
		ST_RIGHT,
		ST_AIR_RIGHT,
		ST_JUMP,
		ST_JUMP_LEFT,
		ST_JUMP_RIGHT,
		ST_LEFT_JUMPING,
		ST_RIGHT_JUMPING,
		ST_AIR,
		ST_AIR_FLIPPED,
		ST_DO_SPECIAL_LEFT,
		ST_DO_SPECIAL_RIGHT,
		ST_SPECIAL_LEFT,
		ST_SPECIAL_RIGHT,
		ST_DEAD,
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

	virtual void SetCurrentPosition(int x, int y)
	{
		current_position.x = x;
		current_position.y = y;
	}

	void Animate(p2SString name, int coll, int row, const int width,
		const int height, const int collumns, const int frames, float speed, bool loop);
	
	Animation* GetAnimation(p2SString name);

public:

	fPoint			starting_velocity;
	fPoint			starting_acceleration;
	fPoint			current_velocity;
	fPoint			current_acceleration;
	fPoint			gravity;
	float			movement_speed;

	//ANIMATION
	p2SString			texture_path;
	p2List<Animation*>	animations;
	Animation*			current_animation;		
	SDL_Rect			rotating_animation;		
	bool				flipped = false;
	
	ENTITY_STATES	state;

	//pathfind?

	friend class j1EntityManager;
};