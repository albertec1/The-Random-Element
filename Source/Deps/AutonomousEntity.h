#pragma once
#pragma once

#include "j1MovingEntity.h"

struct Collider;
struct SDL_Texture;

class AutonomousEntity : public j1MovingEntity
{
public:
	AutonomousEntity(fPoint pos, ENTITY_TYPE type, ENTITY_STATES state = ENTITY_STATES::ST_IDLE);

	virtual ~AutonomousEntity();

	virtual bool Awake(pugi::xml_node& node);

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update(float dt, bool doLogic);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	virtual bool Draw();
	
public:

	int FindDistanceToPlayer();
	void GoTo(fPoint destination, ENTITY_TYPE type);
	void Chase(int range);
	void Move(float dt);
	void NextStep();

	inline fPoint GetDestination()
	{
		if (pathPtr->count() != 0)
		{
			fPoint temp;
			temp.x = pathPtr->end->data.x; 
			temp.y = pathPtr->end->data.y;
			return temp;
		}
			
		return destination;
	}

	inline void SetDestination(fPoint destination)
	{
		this->destination = destination;
	}

	inline void ResetPath()
	{
		if (pathPtr->count() != 0)
			pathPtr->clear();
		destination = { 0,0 };
	}


public:

	//all "transform" variables (pos vel and acc) inherited except:
	float current_movementSpeed = 0;

	//animation methods and variables inherited too

	//pathfind! ---
	fPoint destination;
	p2List<iPoint> path;
	p2List<iPoint>* pathPtr;
	j1Entity* target;
	int pathfindingRange;
	int entityReach;
	
	friend class j1EntityManager;
};