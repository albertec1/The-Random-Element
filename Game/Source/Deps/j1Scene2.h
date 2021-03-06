#pragma once

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"

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
	int sceneNumber = 2;
	p2Point<int> cameraInitPos;
	bool originSelected = false;
	iPoint origin;
	p2List<iPoint> pathList; //private?

private:
	p2List<p2SString> BackroundImages;
};