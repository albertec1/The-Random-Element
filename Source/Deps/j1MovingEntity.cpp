#include "j1Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1MovingEntity.h"


j1MovingEntity::j1MovingEntity(iPoint pos, ENTITY_TYPE type) : j1Entity(pos, type)
{
	state = ENTITY_STATES::ST_IDLE;
	return;
}

j1MovingEntity::~j1MovingEntity()
{
	return;
}

bool j1MovingEntity::PreUpdate()
{
	return true;
}

bool j1MovingEntity::Update(float dt)
{
	return true;
}

bool j1MovingEntity::Start()
{
	flipped = false;
	return true;
}

bool j1MovingEntity::Draw()
{
	bool ret = false;

	if (ret = App->render->Blit(entity_texture, current_position.x, current_position.y, &entity_rect, flipped) == 0)
	{
		LOG("Blit error: Entity Texture");
	}

	return ret;
}

bool j1MovingEntity::PostUpdate()
{
	return true;
}

bool j1MovingEntity::CleanUp()
{
	return true;
}
