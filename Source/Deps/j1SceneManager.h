#pragma once

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"

#include <vector>
#include "SDL_image/include/SDL_image.h"

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

public:

	void ChangeScene(int old_scene, int new_scene);

	void AddScene(j1Module* scene);

	//To set a static background.
	void SetBackgroundImages(const char* path);

	//Pass a vector with the paths to the different images that compose the background.
	//the parallax will be applied from first(0) to last(path_list.lenght)
	void SetBackgroundImages(p2List<p2SString>* path_list);

	void DrawBackground();

public:
	p2Point<int> camera_init_pos;
	j1Scene* scene1;
	j1Scene2* scene2;

	bool backgroundHasParallax = false;

private:
	p2List<j1Module*> scenes;
	int current_scene;

	p2SString	folder_path;
	p2SString	scene1_path;
	p2SString	scene2_path;

	p2List<SDL_Texture*> BackgroundTextures;
};
