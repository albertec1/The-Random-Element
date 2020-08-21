#pragma once

#include "j1Module.h"
#include "p2Point.h"

class j1Scene : public j1Module
{
public:

	j1Scene();
	virtual ~j1Scene();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:
	p2Point<int> camera_init_pos;
};