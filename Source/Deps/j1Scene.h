#pragma once

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"

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

	int sceneNumber = 1;
	p2Point<int> camera_init_pos;
	bool origin_selected = false;
	iPoint origin;
	p2List<iPoint> pathList; //private?

private:

	p2List<p2SString> BackroundImages;
};
