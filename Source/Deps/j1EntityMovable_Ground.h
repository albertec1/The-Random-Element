#ifndef __j1ENTITYMOVABLE_GROUND_H__
#define __j1ENTITYMOVABLE_GROUND_H__

#include "j1EntityMovable.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "Animation.h"


enum BotState
{
	None = 0,
	MoveTo,
};
enum mKeyInput
{
	GoLeft = 0,
	GoRight,
	GoDown,
	Jump,
	Dying,
	Count
};
class j1EntityMovable_ground : public j1EntityMovable
{
public:
	j1EntityMovable_ground(iPoint pos, ENTITY_TYPE type);

	virtual bool Awake(pugi::xml_node& node);

	virtual bool PreUpdate();
	
	virtual bool Update(float dt, bool doLogic);

	virtual void OnCollision(Collider* c1, Collider* c2);

public://ground bot functions

	void CharacterUpdate();

	void ChangeState(BotState newState);

	void GetContext(iPoint prevDest, iPoint currentDest, iPoint nextDest, bool destOnGround, bool reachedX, bool reachedY);

	void MoveTo(iPoint destination);

	bool ReachedNodeOnXAxis(iPoint pathPosition, iPoint prevDest, iPoint currentDest);

	bool ReachedNodeOnYAxis(iPoint pathPosition, iPoint prevDest, iPoint currentDest);
      
public:
	BotState mCurrentBotState;
	uint mCurrentNodeId;
	iPoint pathPosition;
	p2List<iPoint> pathList;
	bool mOnGround;
	uint pathCount;
	float Gravity;
	float falling_velocity;

	//Inputs array
	bool mInputs[6];

	//Update vars---
	iPoint prevDest, currentDest, nextDest;
	bool destOnGround, reachedY, reachedX;

	//Repath vars---
	int mStuckFrames;

	//Animations---
	Animation jumping;
	


};
#endif __j1ENTITYMOVABLE_GROUND_H__

