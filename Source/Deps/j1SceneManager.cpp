#include "j1SceneManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Scene2.h"
#include "j1Input.h"
#include "j1Render.h"
#include "p2Log.h"

j1SceneManager::j1SceneManager()
{
	name.create("SceneManager");
	
	current_scene = 0; //config plz
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
	folder_path = config.attribute("folder").as_string();
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

			ret = scene->data->Start();
		}
		scene_number++;
	}
	return ret;
}
	
bool j1SceneManager::PreUpdate()
{
	bool ret = false;
	j1Module* pModule = NULL;
	int scene_number = 0;

	if (App->input->GetKey(SDL_SCANCODE_1) == j1KeyState::KEY_DOWN)
		ChangeScene(current_scene, 1);

	if (App->input->GetKey(SDL_SCANCODE_2) == j1KeyState::KEY_DOWN)
		ChangeScene(current_scene, 2);

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL; scene = scene->next)
	{
		if (scene_number == current_scene)
		{
			pModule = scene->data;

			if (pModule->active == false)
				continue;

			ret = scene->data->PreUpdate();
		}
		scene_number++;
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
		scene_number++;
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
		scene_number++;
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
		scene_number++;
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
	current_scene = new_scene;
}

void j1SceneManager::AddScene(j1Module* scene)
{
	scene->Init();
	scenes.add(scene);
}

void j1SceneManager::SetBackgroundImages(const char* path)
{	
	if (path != nullptr)
	{
		p2SString full_path(folder_path.GetString());
		full_path += path;
		
		BackgroundTextures.clear();
		BackgroundTextures.add(App->tex->Load(full_path.GetString()));
	}
}

void j1SceneManager::SetBackgroundImages()
{
	if (path != nullptr)
	{
		p2SString full_path(folder_path.GetString());
		full_path += path;

		BackgroundTextures.clear();
		BackgroundTextures.add(App->tex->Load(full_path.GetString()));
	}
}

void j1SceneManager::DrawBackground()
{
	if (!BackgroundHasParallax)
	{
		App->render->Blit(Background);
	}
	else
	{

	}
}