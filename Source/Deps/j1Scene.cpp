#include "j1Scene.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Render.h"
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
	App->map->Load("test-map-v02.tmx");
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
	App->map->Draw();

	if (App->input->GetKey(SDL_SCANCODE_UP) == j1KeyState::KEY_REPEAT)
		App->render->camera.y += 3;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == j1KeyState::KEY_REPEAT)
		App->render->camera.y -= 3;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == j1KeyState::KEY_REPEAT)
		App->render->camera.x += 3;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == j1KeyState::KEY_REPEAT)
		App->render->camera.x -= 3;
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == j1KeyState::KEY_DOWN)
	{
		if (App->map->debug_metadata == false)
			App->map->debug_metadata = true;
		else
			App->map->debug_metadata = false;
	}


	return true;
}

bool j1Scene::PostUpdate()
{
	return true;
}

bool j1Scene::CleanUp()
{
	return true;
}
