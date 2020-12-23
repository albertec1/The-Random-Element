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
	camera_init_pos.x = config.child("camera").attribute("initial_pos_x").as_int(0);
	camera_init_pos.y = config.child("camera").attribute("initial_pos_y").as_int(0);
	pugi::xml_node imageNode = config.child("bg_image_path");
	for (imageNode; imageNode != nullptr; imageNode = imageNode.next_sibling("bg_image_path"))
	{
		BackroundImages.add(imageNode.attribute("value").as_string());
	}
	return true;
}

bool j1Scene::Start()
{
	App->scene_manager->SetBackgroundImages(&BackroundImages);
	App->map->Load("first-map-v01.tmx");

	int w = 0; int h = 0;
	uchar* data = NULL;
	if (App->map->SetPathTiles(&w, &h, &data))
		App->pathfinding->SetMap(w, h, data);

	App->render->camera.x = camera_init_pos.x;
	App->render->camera.y = camera_init_pos.y;

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
		if (origin_selected == true)
		{
			if (App->allow_debug_log == true)
			LOG("path dest selected. p: %d, %d", p.x, p.y);

			App->pathfinding->CreatePath(origin, p, ENTITY_TYPE::DEBUG);	
			App->pathfinding->CopyPathList(&pathList);

			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;

			if (App->allow_debug_log == true)
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
