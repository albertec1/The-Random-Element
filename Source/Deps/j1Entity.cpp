#include "j1Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"


j1Entity::j1Entity(iPoint pos, ENTITY_TYPE type) : starting_position(pos), type(type), entity_texture(nullptr), entity_collider(nullptr)
{
	flipped = false;
}

j1Entity::~j1Entity()
{
	return;
}

bool j1Entity::PreUpdate()
{
	return true;
}

bool j1Entity::Update(float dt)
{
	return true;
}

bool j1Entity::Start()
{
	flipped = false;
	return true;
}

bool j1Entity::Draw()
{
	bool ret = false;

	if (ret = App->render->Blit(entity_texture, starting_position.x, starting_position.y, &entity_rect, flipped) == 0)
	{
		LOG("Blit error: Entity Texture");
	}

	return ret;
}

bool j1Entity::PostUpdate()
{
	return true;
}

bool j1Entity::CleanUp()
{
	return true;
}

//save?

//load?

void j1Entity::OnCollision(Collider* c1, Collider* c2) 
{
	return;
}