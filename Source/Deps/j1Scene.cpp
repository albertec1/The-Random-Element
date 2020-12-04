#include "j1Scene.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1EntityManager.h"
#include "Pathfinding.h"
#include "p2Log.h"

j1Scene::j1Scene()
{
	name.create("scene");
}

j1Scene::~j1Scene()
{}

bool j1Scene::Awake(pugi::xml_node& config)
{
	camera_init_pos.x = config.child("camera").attribute("initial_pos_x").as_int(0);
	camera_init_pos.y = config.child("camera").attribute("initial_pos_y").as_int(0);
	return true;
}

bool j1Scene::Start()
{
	//App->scene_manager->SetBackgroundImages("big-background.png");
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
	if (App->input->GetKey(SDL_SCANCODE_UP) == j1KeyState::KEY_REPEAT)
		App->render->camera.y += 10;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == j1KeyState::KEY_REPEAT)
		App->render->camera.y -= 10;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == j1KeyState::KEY_REPEAT)
		App->render->camera.x += 10;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == j1KeyState::KEY_REPEAT)
		App->render->camera.x -= 10;
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == j1KeyState::KEY_DOWN)
	{
		if (App->map->debug_metadata == false)
			App->map->debug_metadata = true;
		else
			App->map->debug_metadata = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == j1KeyState::KEY_UP)
	{
		App->map->debug_pathtiles = !(App->map->debug_pathtiles);
		App->pathfinding->debug_pathList = !(App->pathfinding->debug_pathList);
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == j1KeyState::KEY_UP)
	{
		App->manager->godMode = !(App->manager->godMode);
	}

	App->map->Draw();

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
