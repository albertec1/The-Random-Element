#include "j1App.h"
#include "j1SceneManager.h"
#include "j1Scene.h"
#include "j1Scene2.h"

j1SceneManager::j1SceneManager()
{
	name.create("SceneManager");
	
	current_scene = 1; //config plz
	scene1 = new j1Scene();
	scene2 = new j1Scene2();

	AddScene(scene1);
	AddScene(scene2);
}

j1SceneManager::~j1SceneManager()
{

}

bool j1SceneManager::Awake(pugi::xml_node& config)
{
	scene1_path = config.child("scene1").child("path").attribute("value").as_string();
	scene2_path = config.child("scene2").child("path").attribute("value").as_string();
	
	bool ret = true;
	j1Module* pModule = NULL;

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL && ret == true; scene = scene->next)
	{
		pModule = scene->data;

		if (pModule->active == false)
			continue;

		ret = scene->data->Awake(config);
	}
	return ret;
}
	
bool j1SceneManager::Start()
{
	return true;
}
	
bool j1SceneManager::PreUpdate()
{
	bool ret = false;
	j1Module* pModule = NULL;
	int scene_number = 0;

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL; scene = scene->next)
	{
		if (scene_number == current_scene)
		{
			pModule = scene->data;

			if (pModule->active == false)
				continue;

			ret = scene->data->PreUpdate();
		}
	}
	return ret;
}
	
bool j1SceneManager::Update(float dt)
{
	bool ret = false;
	j1Module* pModule = NULL;
	int scene_number = 0;

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL; scene = scene->next )
	{
		if (scene_number == current_scene)
		{
			pModule = scene->data;

			if (pModule->active == false)
				continue;

			ret = scene->data->Update(dt);
		}
	}
	return ret;
}
	
bool j1SceneManager::PostUpdate()
{
	bool ret = false;
	j1Module* pModule = NULL;
	int scene_number = 0;

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL; scene = scene->next)
	{
		if (scene_number == current_scene)
		{
			pModule = scene->data;

			if (pModule->active == false)
				continue;

			ret = scene->data->PostUpdate();
		}
	}

	return ret;
}
		
bool j1SceneManager::CleanUp()
{
	bool ret = false;
	j1Module* pModule = NULL;
	int scene_number = 0;

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL; scene = scene->next)
	{
		if (scene_number == current_scene)
		{
			pModule = scene->data;

			if (pModule->active == false)
				continue;

			ret = scene->data->CleanUp();
		}
	}
	return ret;
}

void j1SceneManager::ChangeScene(int old_scene, int new_scene)
{
	switch (old_scene)
	{
	case 1:
		scene1->CleanUp();
		break;

	case 2:
		scene2->CleanUp();
		break;
	}

	switch (new_scene)
	{
	case 1:
		scene1->Start();
		break;

	case 2:
		scene2->Start();
		break;
	}
}

void j1SceneManager::AddScene(j1Module* scene)
{
	scene->Init();
	scenes.add(scene);
}