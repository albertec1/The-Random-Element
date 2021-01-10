#include "j1SceneManager.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Scene2.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Map.h"
#include "Pathfinding.h"
#include "j1EntityManager.h"
#include "j1MainMenuUI.h"
#include "p2Log.h"

j1SceneManager::j1SceneManager()
{
	name.create("SceneManager");
	
	currentScene = 0; //config plz
	scene0 = new j1MainMenuUI();
	scene1 = new j1Scene();
	scene2 = new j1Scene2();
	
	AddScene(scene0);
	AddScene(scene1);
	AddScene(scene2);
}

j1SceneManager::~j1SceneManager()
{

}

bool j1SceneManager::Awake(pugi::xml_node& config)
{
	folderPath = App->folder;
	scene1Path = config.child("scene1").child("path").attribute("value").as_string();
	scene2Path = config.child("scene2").child("path").attribute("value").as_string();
	
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

	for (p2List_item<j1Module*>* scene = scenes.start; scene != nullptr; scene = scene->next)
	{
		if (scene_number == currentScene)
		{
			if (scene == nullptr)
				continue;

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

	if (App->input->GetKey(SDL_SCANCODE_1) == j1KeyState::KEY_DOWN || exitMenu)
	{
		ChangeScene(currentScene, 1);
		if (exitMenu)
			exitMenu = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == j1KeyState::KEY_DOWN)
		ChangeScene(currentScene, 2);

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL; scene = scene->next)
	{
		if (scene_number == currentScene)
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

	if (currentScene != 0)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == j1KeyState::KEY_REPEAT)
			App->render->camera.y += 10;

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == j1KeyState::KEY_REPEAT)
			App->render->camera.y -= 10;

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == j1KeyState::KEY_REPEAT)
			App->render->camera.x += 10;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == j1KeyState::KEY_REPEAT)
			App->render->camera.x -= 10;

		if (App->input->GetKey(SDL_SCANCODE_F9) == j1KeyState::KEY_UP)
		{
			App->map->debug_metadata = !(App->map->debug_metadata);
			App->map->debug_pathtiles = !(App->map->debug_pathtiles);
			App->pathfinding->debug_pathList = !(App->pathfinding->debug_pathList);
		}

		if (App->input->GetKey(SDL_SCANCODE_F10) == j1KeyState::KEY_UP)
		{
			App->manager->godMode = !(App->manager->godMode);
		}

		if (App->input->GetKey(SDL_SCANCODE_F11) == j1KeyState::KEY_UP)
		{
			if (App->framerate_cap == 30) { App->framerate_cap = 60; }
			else
				App->framerate_cap = 30;
		}

		App->sceneManager->DrawBackground();
		App->map->Draw();
	}
	else
	{
		scene0->ActivateMenu();
	}

	for (p2List_item<j1Module*>* scene = scenes.start; scene != NULL; scene = scene->next )
	{
		if (scene_number == currentScene)
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
		if (scene_number == currentScene)
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
		if (scene_number == currentScene)
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
	case 0:
		scene0->CleanUp();
		scene0->DeactivateMenu();
		App->pathfinding->CleanUp();
		App->manager->CleanUp();
		break;

	case 1:
		scene1->CleanUp();
		App->pathfinding->CleanUp();
		App->manager->CleanUp();
		break;

	case 2:
		scene2->CleanUp();
		App->pathfinding->CleanUp();
		App->manager->CleanUp();
		break;
	}

	switch (new_scene)
	{
	case 0:
		scene0->Start();
		break;

	case 1:
		scene1->Start();
		break;

	case 2:
		scene2->Start();
		break;
	}
	currentScene = new_scene;
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
		p2SString full_path(folderPath.GetString());
		full_path += path;
		
		BackgroundTextures.clear();
		SDL_Texture* tex = App->tex->Load(full_path.GetString());
		BackgroundTextures.add(tex);
	}
}

void j1SceneManager::SetBackgroundImages(p2List<p2SString>* path_list)
{
	if (path_list->count() != 0)
	{
		for(int i = 0; i < path_list->count(); i++)
		{
			p2SString string = path_list->At(i)->data;

			p2SString full_path(folderPath.GetString());
			full_path += string.GetString();

			SDL_Texture* tex = App->tex->Load(full_path.GetString());
			BackgroundTextures.add(tex);
		}
	}
}

void j1SceneManager::DrawBackground()
{
	if (!backgroundHasParallax)
	{
		//Fill a blit(...) with info of the picture taken from the tiled map directly.
		for(int i = 0; i < BackgroundTextures.count(); i++)
			App->render->Blit(BackgroundTextures[i], i*2500, -450);		
	}
	else
	{

	}
}