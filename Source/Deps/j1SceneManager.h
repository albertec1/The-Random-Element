#pragma once

#include "j1Module.h"
#include "p2Point.h"

//Scenes
class j1Scene;
class j1Scene2;

class j1SceneManager : public j1Module
{
public:

	j1SceneManager();
	virtual ~j1SceneManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate(); 

	bool CleanUp(); //CleanUp all scenes 

	void ChangeScene(int old_scene, int new_scene);

	void AddScene(j1Module* scene);

public:
	p2Point<int> camera_init_pos;
	j1Scene* scene1;
	j1Scene2* scene2;

private:
	p2List<j1Module*> scenes;
	int current_scene;

	p2SString	scene1_path;
	p2SString	scene2_path;
};

//Since scenes are modules, I should do like the App list but only updating the scene with
//the number of the scene that has to be updated

//change current_scene to change the scene number that will update.