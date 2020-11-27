#pragma once
#pragma once

#include "j1MovingEntity.h"

struct Collider;
struct SDL_Texture;

class AutonomousEntity : public j1MovingEntity
{
public:
	AutonomousEntity(iPoint pos, ENTITY_TYPE type);

	virtual ~AutonomousEntity();

	virtual bool Awake(pugi::xml_node& node);

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update(float dt);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	virtual bool Draw();
	
public:

	int FindDistanceToPlayer();
	void GoTo(iPoint destination, ENTITY_TYPE type);
	void Chase(int range);
	void Move(float dt);
	void NextStep();

	inline iPoint GetDestination()
	{
		if (path->count() != 0)
			return path->end->data;
		return destination;
	}

	inline void SetDestination(iPoint destination)
	{
		this->destination = destination;
	}

	inline void ResetPath()
	{
		if (path->count() != 0)
			path->clear();
		destination = { 0,0 };
	}


public:

	//"transform" variables (pos vel and acc) inherited 
	//animation methods and variables inherited too

	//pathfind! ---
	iPoint destination;
	p2List<iPoint>* path;
	j1Entity* target;
	int pathfindingRange;
	int entityReach;

	j1Entity* player;
	
	friend class j1EntityManager;
};