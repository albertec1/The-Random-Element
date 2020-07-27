#ifndef __j1ENTITYMOVABLE_CPP__

#include "J1EntityMovable.h"
#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "Animation.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1Render.h"

j1EntityMovable::j1EntityMovable(iPoint pos, ENTITY_TYPE type) : j1Entity(pos, type)
{
	//PUSHBACKS

	LOG("Loading EntityMovable textures");
	//Graphics = App->tex->Load("Spritesheets/Enemies/Bugfly/Idle_Flying.png");

	EntityState = Current_State::ST_IDLE;
	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
	
}

bool j1EntityMovable::Awake()
{
	EntityCollider->callback = this;
	return true;
}
bool j1EntityMovable::Update(float dt, bool doLogic)
{
	//TODO: state machine of the bat

	//PLAYER
	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
	EntityCollider->SetPos(CurrentPosition.x, CurrentPosition.y);

	return true;
}

bool j1EntityMovable::CleanUp()
{
	LOG("Unloading Entity");

	App->tex->UnLoad(EntityTexture);

	return true;
}

void j1EntityMovable::OnCollision(Collider* c1, Collider* c2)
{
	// TODO: Launch dead animation if hit from top
	// TODO: Go a few tiles backwards after hitting the player before trying to attack again 
}

#define __j1ENTITYMOVABLE_CPP__
#endif	__j1ENTITYMOVABLE_CPP__

