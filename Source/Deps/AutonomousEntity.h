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

	void GoTo(fPoint destination, ENTITY_TYPE type);
	void Chase(int range, int enemy);
	void Move(float dt);
	void NextStep();

	inline fPoint GetDestination()
	{
		if (path.count() != 0)
			return path.end->data;
		return destination;
	}

	inline void SetDestination(fPoint destination)
	{
		this->destination = destination;
	}

	inline void ResetPath()
	{
		if (path.count() != 0)
			path.clear();
		destination = { 0,0 };
	}


public:

	//"transform" variables (pos vel and acc) inherited 
	//animation methods and variables inherited too

	//pathfind! ---
	fPoint destination;
	p2List<fPoint> path;
	j1Entity* path_target;
	
	friend class j1EntityManager;
};