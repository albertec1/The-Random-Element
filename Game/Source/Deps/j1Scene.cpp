#include "j1Scene.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1EntityManager.h"
#include "j1Textures.h"
#include "Pathfinding.h"
#include "p2Log.h"

j1Scene::j1Scene()
{
	name.create("scene1");
}

j1Scene::~j1Scene()
{}

bool j1Scene::Awake(pugi::xml_node& _config)
{
	pugi::xml_node config = _config.child("scene1");
	cameraInitPos.x = config.child("camera").attribute("initial_pos_x").as_int(0);
	cameraInitPos.y = config.child("camera").attribute("initial_pos_y").as_int(0);
	pugi::xml_node imageNode = config.child("bg_image_path");	

	for (imageNode; imageNode != nullptr; imageNode = imageNode.next_sibling("bg_image_path"))
	{
		BackroundImages.add(imageNode.attribute("value").as_string());
	}
	return true;
}

bool j1Scene::Start()
{
	App->sceneManager->SetBackgroundImages(&BackroundImages);
	App->map->Load("first_map_v01.tmx");

	App->manager->player = (j1EntityPlayer*)App->manager->CreateEntity(ENTITY_TYPE::PLAYER, { 808, 700 });

	//MUST GO TO CONFIG FILE
	App->manager->CreateEntity(ENTITY_TYPE::GROUND_ENEMY, { 3072, 768 });
	App->manager->CreateEntity(ENTITY_TYPE::AIR_ENEMY, { 4750, 190 });
	App->manager->CreateEntity(ENTITY_TYPE::GROUND_ENEMY, { 6482, 353 });
	App->manager->CreateEntity(ENTITY_TYPE::GROUND_ENEMY, { 7482, 357 });

	//--Awake all scene entities
	App->manager->AwakeAgain();
	//--

	int w = 0; int h = 0;
	uchar* data = NULL;
	if (App->map->SetPathTiles(&w, &h, &data))
		App->pathfinding->SetMap(w, h, data);

	App->render->camera.x = cameraInitPos.x;
	App->render->camera.y = cameraInitPos.y;

	return true;
}

bool j1Scene::PreUpdate()
{
	return true;
}

bool j1Scene::Update(float dt)
{
	
	return true;
}

bool j1Scene::PostUpdate()
{
	//--- Debug Pathfinding ---//
	int x, y;

	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y); //current mouse position

	if (App->input->GetKey(SDL_SCANCODE_P) == j1KeyState::KEY_UP)
	{
		if (originSelected == true)
		{
			if (App->allowDebugLog == true)
			LOG("path dest selected. p: %d, %d", p.x, p.y);

			App->pathfinding->CreatePath(origin, p, ENTITY_TYPE::DEBUG);	
			App->pathfinding->CopyPathList(&pathList);

			originSelected = false;
		}
		else
		{
			origin = p;
			originSelected = true;

			if (App->allowDebugLog == true)
			LOG("path start selected. origin: %d, %d", origin.x, origin.y);
		}
	}
	return true;

	//--- End Debug Pathfinding ---//

	return true;
}

bool j1Scene::CleanUp()
{
	return true;
}
