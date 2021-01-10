#include "j1Scene2.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1EntityManager.h"
#include "Pathfinding.h"

j1Scene2::j1Scene2()
{
	name.create("scene");
}

j1Scene2::~j1Scene2()
{}

bool j1Scene2::Awake(pugi::xml_node& _config)
{
	pugi::xml_node config = _config.child("scene2");
	cameraInitPos.x = config.child("camera").attribute("initial_pos_x").as_int(0);
	cameraInitPos.y = config.child("camera").attribute("initial_pos_y").as_int(0);
	pugi::xml_node imageNode = config.child("bg_image_path");

	for (imageNode; imageNode != nullptr; imageNode = imageNode.next_sibling("bg_image_path"))
	{
		BackroundImages.add(imageNode.attribute("value").as_string());
	}
	return true;
}

bool j1Scene2::Start()
{
	App->map->Load("second-map-v01.tmx");

	App->manager->player = (j1EntityPlayer*)App->manager->CreateEntity(ENTITY_TYPE::PLAYER, { 808, 700 });

	//MUST GO TO CONFIG FILE
	/*App->manager->CreateEntity(ENTITY_TYPE::GROUND_ENEMY, { 3072, 768 });
	App->manager->CreateEntity(ENTITY_TYPE::AIR_ENEMY, { 4750, 190 });
	App->manager->CreateEntity(ENTITY_TYPE::GROUND_ENEMY, { 6482, 353 });
	App->manager->CreateEntity(ENTITY_TYPE::GROUND_ENEMY, { 7482, 357 });*/

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

bool j1Scene2::PreUpdate()
{
	return true;
}

bool j1Scene2::Update(float dt)
{
	App->map->Draw();

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

	return true;
}

bool j1Scene2::PostUpdate()
{
	return true;
}

bool j1Scene2::CleanUp()
{
	
	return true;
}
