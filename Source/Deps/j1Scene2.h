#pragma once

#include "j1Module.h"
#include "p2Point.h"

class j1Scene2 : public j1Module
{
public:

	j1Scene2();
	virtual ~j1Scene2();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:
	p2Point<int> camera_init_pos;
};