#pragma once

#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "j1Animation.h"

struct Collider;
struct SDL_Texture;


enum class EntityStates
{
	ST_UNKNOWN,
	ST_IDLE,			//idle state
	ST_IDLE_FLIPPED,	//idle state (texture flipped)
	ST_LEFT,			//going left
	ST_AIR_LEFT,		//going left while in the air
	ST_RIGHT,			//going right
	ST_AIR_RIGHT,		//going right while in the air
	ST_DOWN,			//going down (only available to air units) or player with godMode
	ST_UP,				//going down (only available to air units) or player with godMode
	ST_JUMP,			//just about to start a vertical jump (when forces are applied)
	ST_JUMP_LEFT,		//just about to start a jump to the left (when forces are applied)
	ST_JUMP_RIGHT,		//just about to start a jump to the right (when forces are applied)
	ST_LEFT_JUMPING,	//in the air after a left jump
	ST_RIGHT_JUMPING,	//in the air after a right jump
	ST_AIR,				//in the air falling straight
	ST_AIR_FLIPPED,		//in the air falling straight (texture flipped)
	ST_DO_SPECIAL_LEFT,	//just about to do the special ability to the left
	ST_DO_SPECIAL_RIGHT,//just about to do the special ability to the right
	ST_SPECIAL_LEFT,	//teleporting to the left 
	ST_SPECIAL_RIGHT,	//teleporting to the right 
	ST_DEAD,			//dead 
};

class j1MovingEntity : public j1Entity
{
public:
	j1MovingEntity(fPoint pos, ENTITY_TYPE type, EntityStates state = EntityStates::ST_IDLE);

	~j1MovingEntity();

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update(float dt);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	virtual bool Draw();

	virtual const fPoint GetCurrentPosition()
	{
		return currentPosition;
	} 

	virtual void SetCurrentPosition(int x, int y)
	{
		currentPosition.x = x;
		currentPosition.y = y;
	}

	void Animate(p2SString name, int coll, int row, const int width,
		const int height, const int collumns, const int frames, float speed, bool loop);
	
	Animation* GetAnimation(p2SString name);

public:

	fPoint startingVelocity;
	fPoint startingAcceleration;
	fPoint currentVelocity;
	fPoint currentAcceleration;
	fPoint gravity;
	fPoint normalizedGravity;
	float movementSpeed;
	float normalizedMovementSpeed;

	//ANIMATION
	p2SString texturePath;
	p2List<Animation*> animations;
	Animation* currentAnimation;		
	SDL_Rect rotatingAnimation;		
	bool flipped = false;
	
	EntityStates	state;

	friend class j1EntityManager;
};