#include "j1EntityManager.h"
#include "p2Log.h" 
#include "j1Entity.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Scene.h"
#include "j1EntityPlayer.h"

j1EntityManager::j1EntityManager()
{
	name.create("EntityManager");
}

j1EntityManager::~j1EntityManager()
{
	return;
}

bool j1EntityManager::Awake(pugi::xml_node& node)
{
	bool ret = true;

	player = (j1EntityPlayer*)CreateEntity(ENTITY_TYPE::PLAYER, {0,0});

	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
	{
		ret = item->data->Awake(node);
	}
	return ret;
}

bool j1EntityManager::Start()
{
	bool ret = true;

	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
	{
		ret = item->data->Start();
	}

	return true;
}

bool j1EntityManager::PreUpdate()
{
	bool ret = true;

	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
	{
		ret = item->data->PreUpdate();
	}

	return true;
}

bool j1EntityManager::Update(float dt)
{
	bool ret = true;

	for (p2List_item<j1Entity*>* EntityIterator = entities.start; EntityIterator != nullptr; EntityIterator = EntityIterator->next)
	{
		ret = EntityIterator->data->Update(dt, false);
		if (ret == false)
		{
			LOG("Entity update error");
		}
	}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	bool ret = true;

	for (p2List_item<j1Entity*>* EntityIterator = entities.start; EntityIterator != nullptr; EntityIterator = EntityIterator->next)
	{
		ret = EntityIterator->data->PostUpdate();
	}

	if (ret == true)
		ret = DrawEntity();

	return ret;
}

bool j1EntityManager::DrawEntity()
{
	bool ret = true;

	for (p2List_item<j1Entity*>* EntityIterator = entities.start; EntityIterator != nullptr; EntityIterator = EntityIterator->next)
	{
		ret = EntityIterator->data->Draw();
	}
	return true;
}

bool j1EntityManager::CleanUp()
{
	bool ret = true;

	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
	{
		ret = entities.del(item);
	}
	return ret;
}

j1Entity* j1EntityManager::CreateEntity(ENTITY_TYPE type, iPoint initPos)
{
	static_assert((INT)ENTITY_TYPE::UNKNOWN_TYPE == 3, "CODE NEEDS UPDATE");
	j1Entity* ret = nullptr;
	switch (type)
	{
	case ENTITY_TYPE::PLAYER:			ret = new j1EntityPlayer(initPos, type); break;
	//case ENTITY_TYPE::WALKING_ENEMY:	ret = new j1EntityMovable_ground(initPos, type); break;
	case ENTITY_TYPE::UNKNOWN_TYPE:		ret = nullptr; break;
	}

	if (ret == nullptr)
	{
		LOG("Entity type WAS UNKNOWN_TYPE");
		return false;
	}

	entities.add(ret);
	return ret;
}

bool j1EntityManager::DestroyEntity(j1Entity* entity)
{
	p2List_item<j1Entity*>* item = nullptr; item->data = entity;
	entities.del(item);

	entity = nullptr;

	return true;
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	
	if (c1->type == PLAYER)
	{
		iPoint wall_position = App->map->WorldToMap(c2->rect.x, c2->rect.y);
		uint tileid = App->map->metadata->GetLayerPositon(wall_position.x, wall_position.y);

		if (c1->rect.y < (c2->rect.y + c2->rect.h) && c1->rect.y < c2->rect.y
			&& (c1->rect.y + c1->rect.h) >= c2->rect.y && (c1->rect.y + c1->rect.h) < (c2->rect.y + c2->rect.h) && App->coll->canCollide_top(tileid)) //Player collides from top
		{
			if (c2->type == WALL || c2->type == PLATFORM)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c1->callback;
				callback->current_position.y = c2->rect.y - c2->rect.h;

				if (player->jumping == false)
				{
					if (player->jump_available == false)
						player->jump_available = true;
				}
			}
		}

		else if (c1->rect.x > c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) &&
			(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) > (c2->rect.x + c2->rect.w) && App->coll->canCollide_right(tileid)) //Player collides from right side
		{
			if (c2->type == WALL)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c1->callback;
				callback->current_position.x = c2->rect.x + c2->rect.w;
				player->current_acceleration.x = 0;
			}
		}

		else if (c1->rect.x < c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) &&
			(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) < (c2->rect.x + c2->rect.w) && App->coll->canCollide_left(tileid))//Player collides from left side
		{
			if (c2->type == WALL)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c1->callback;
				callback->current_position.x = c2->rect.x - c1->rect.w;
				player->current_acceleration.x = 0;	
			}		
		}			

		else if (c1->rect.y > c2->rect.y && c1->rect.y < (c2->rect.y + c2->rect.h) &&
			(c1->rect.y + c1->rect.h)>(c2->rect.y + c2->rect.h) && (c1->rect.y + c1->rect.h) > c2->rect.y && App->coll->canCollide_bottom(tileid))//Player collides from bottom
		{
			if (c2->type == WALL)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c1->callback;
				callback->current_position.y = c2->rect.y + c2->rect.h;
			}
		}

	}

	if (c2->type == PLAYER)
	{
		iPoint wall_position = App->map->WorldToMap(c1->rect.x, c1->rect.y);
		uint tileid = App->map->metadata->GetLayerPositon(wall_position.x, wall_position.y);

		if (c2->rect.y < (c1->rect.y + c1->rect.h) && c2->rect.y < c1->rect.y &&
			(c2->rect.y + c2->rect.h) >= c1->rect.y && (c2->rect.y + c2->rect.h) < (c1->rect.y + c1->rect.h) && App->coll->canCollide_top(tileid)) //Player collides from top
		{
			if (c2->type == WALL || c2->type == PLATFORM)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c2->callback;
				callback->current_position.y = c1->rect.y - c1->rect.h;

				if (player->jumping == false)
				{
					if (player->jump_available == false)
						player->jump_available = true;

					if (player->jump_available == true)
					{
						player->current_velocity.y = 0;
						player->current_acceleration.y = 0;
					}

				}
			}
		}

		else if (c2->rect.x > c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
			(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) > (c1->rect.x + c1->rect.w) && App->coll->canCollide_right(tileid)) //Player collides from right side
		{
			if (c2->type == WALL)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c2->callback;
				callback->current_position.x = c1->rect.x + c1->rect.w;
				player->current_acceleration.x = 0;
			}
		}

		else if (c2->rect.x < c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
			(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) < (c1->rect.x + c1->rect.w) && App->coll->canCollide_left(tileid))//Player collides from left side
		{
			if (c2->type == WALL)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c2->callback;
				callback->current_position.x = c1->rect.x - c2->rect.w;
				player->current_acceleration.x = 0;
			}
		}

		else if (c2->rect.y > c1->rect.y && c2->rect.y < (c1->rect.y + c1->rect.h) &&
			(c2->rect.y + c2->rect.h)>(c1->rect.y + c1->rect.h) && (c2->rect.y + c2->rect.h) > c1->rect.y && App->coll->canCollide_bottom(tileid))//Player collides from bottom
		{
			if (c2->type == WALL)
			{
				j1EntityPlayer* callback = (j1EntityPlayer*)c2->callback;
				callback->current_position.y = c1->rect.y + c1->rect.h;
				player->current_velocity.y = 0;
				player->current_acceleration.y = 0;
			}
		}
	}
	

} 