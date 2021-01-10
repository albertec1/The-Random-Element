#pragma once

//This is j1Module.h, the interface for all engine modules
//---------------------------------------------------------

#include "p2SString.h"
#include "PugiXml\src\pugixml.hpp"

class j1App;
class j1Element;
//class Collider;

enum class GUI_Event
{
	EVENT_UNKOWNN = -1,

	EVENT_ONCLICK,
	EVENT_LEFTCLICK,
	EVENT_DRAG,
	EVENT_HOVER,
};

class j1Module
{
public:

	j1Module() : active(false)
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}

	virtual void GUI_Event_Manager(GUI_Event type, j1Element* element)
	{

	}
public:

	p2SString name;
	bool active;

	//Callbacks ---
	//virtual void OnCollision(Collider* c1, Collider* c2) {}
};