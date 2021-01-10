#include "j1Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"


j1Entity::j1Entity(fPoint pos, ENTITY_TYPE type) : startingPosition(pos), type(type), entityTexture(nullptr), entityCollider(nullptr)
{
	flipped = false;
	entiyRect = { 0,0,0,0 };
}

j1Entity::~j1Entity()
{
	return;
}

bool j1Entity::PreUpdate()
{
	return true;
}

bool j1Entity::Update(float dt, bool do_logic)
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