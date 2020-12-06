#include "AutonomousEntity.h"
#include "j1Render.h"
#include "Pathfinding.h"
#include "j1Collision.h"
#include "j1EntityManager.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "p2Point.h"

AutonomousEntity::AutonomousEntity(fPoint pos, ENTITY_TYPE type, ENTITY_STATES state) : j1MovingEntity(pos, type, state)
{
	name.create("autonomousEntity");
	entityReach = 0;
	pathfindingRange = 0;
	target = nullptr;
	starting_position.x = pos.x;
	starting_position.y = pos.y;
	pathPtr = nullptr;
}

AutonomousEntity::~AutonomousEntity()
{
	target = nullptr;
	pathPtr->clear();
}

bool AutonomousEntity::Awake(pugi::xml_node& node)
{
	//Load properties
	pugi::xml_node stats = node.child("autonomousEntity").child("entity_stats");

	rect_size.x = stats.child("character_width").attribute("value").as_uint();
	rect_size.y = stats.child("character_height").attribute("value").as_uint();
	current_position.x = starting_position.x;
	current_position.y = starting_position.y;
	movement_speed = stats.child("movement_speed").attribute("value").as_uint();
	gravity.y = stats.child("gravity").attribute("value").as_float();

	//--- main_Collider creation
	entity_rect.w = stats.child("character_width").attribute("value").as_uint();
	entity_rect.h = stats.child("character_height").attribute("value").as_uint();
	entity_rect.x = stats.child("initial_pos_x").attribute("value").as_uint();
	entity_rect.y = stats.child("initial_pos_y").attribute("value").as_uint();

	texture_path = stats.child("texture_path").attribute("value").as_string();
	
	//entity_collider = App->coll->AddCollider(entity_rect, COLLIDER_TYPE::ENEMY, this);

	//-- Load range depending on type.
	pathfindingRange = 300;
	entityReach = 5;
	destination = current_position;
	pathPtr = &path;
	return true;
}

bool AutonomousEntity::Start()
{
	enemyTexture = App->tex->Load(texture_path.GetString());
	return true;
}

bool AutonomousEntity::PreUpdate()
{
	return true;
}

bool AutonomousEntity::Update(float dt, bool doLogic)
{
	if (dt != 0.0f)
	{
		if (doLogic)
		{
			if (FindDistanceToPlayer() <= entityReach)
				target = App->manager->player;
			else
				target = nullptr;

			Chase(pathfindingRange);

			if (destination != current_position)
				Move(dt);
			else
			{
				NextStep();

				if (target != nullptr)
				{
					//attack
				}
			}

			
		}
	}
	
	//entity_collider->rect.x = current_position.x;
	//entity_collider->rect.y = current_position.y;
	//entity_rect.x = current_position.x;
	//entity_rect.y = current_position.y;

	return true;
}

bool AutonomousEntity::PostUpdate()
{
	return true;
}

bool AutonomousEntity::CleanUp()
{
	if (entity_collider != nullptr)
	{
		entity_collider->to_delete = true;
		entity_collider = nullptr;
	}
	return true;
}

bool AutonomousEntity::Draw()
{
	if (type == ENTITY_TYPE::AIR_ENEMY)
	{
		SDL_Rect temp;
		temp.x = temp.y = 0;
		temp.w = temp.h = 32;
		rotating_animation = temp;
		App->render->Blit(enemyTexture, (int)current_position.x, (int)current_position.y, &rotating_animation);
		//App->render->DrawQuad({(int)current_position.x, (int)current_position.y, 32, 32}, 239, 127, 26, 255);
	}
	if (type == ENTITY_TYPE::GROUND_ENEMY)
	{
		SDL_Rect temp;
		temp.x = 33;
		temp.y = 0;
		temp.w = temp.h = 32;
		rotating_animation = temp;
		App->render->Blit(enemyTexture, (int)current_position.x, (int)current_position.y, &rotating_animation);
		//App->render->DrawQuad({(int)current_position.x, (int)current_position.y, 32, 32 }, 101, 67, 33, 255);

	}
	return true;
}

int AutonomousEntity::FindDistanceToPlayer()
{
	int distance = sqrtf((this->current_position.x - App->manager->player->current_position.x) * (this->current_position.x - App->manager->player->current_position.x) + (this->current_position.y - App->manager->player->current_position.y) * (this->current_position.y - App->manager->player->current_position.y));
	return distance;
}

void AutonomousEntity::GoTo(fPoint destination, ENTITY_TYPE type)
{
	iPoint mapCurrentPosition = App->map->WorldToMap((int)current_position.x, (int)current_position.y);
	iPoint mapDestination = App->map->WorldToMap((int)destination.x, (int)destination.y);
	int distanceToPlayer = FindDistanceToPlayer();

	if (distanceToPlayer <= pathfindingRange)
	{
	int pathSize = App->pathfinding->CreatePath(mapCurrentPosition, mapDestination, type);
		if (pathSize > 1)
		{
			App->pathfinding->GetLastPath(pathPtr); // CopyPathList already clears the path inside.
			if (pathPtr->start != nullptr)
			{
				iPoint temp = App->map->MapToWorld(pathPtr->start->data.x, pathPtr->start->data.y); //set the destination
				this->destination.x = temp.x;
				this->destination.y = temp.y;
			}
			else
				this->destination = current_position; //set the destination
		}
		else
			this->destination = current_position; //set the destination
	}
	this->destination = current_position; //set the destination
}

void AutonomousEntity::Chase(int range)
{
	if (target == nullptr)
	{   
		if (pathPtr->count() == 0)
		{
			//temporary chase, Entities should be able to chase each other if needed, not only the player.
			{
				GoTo(App->manager->player->current_position, type);
			}
		}
	}
	else
	{
		if (pathPtr->count() != 0)
		{
			App->map->MapToWorld(pathPtr->start->data.x, pathPtr->start->data.y);
			pathPtr->clear();
		}
	}
}

void AutonomousEntity::Move(float dt)
{
	normalized_movement_speed = movement_speed * dt;

	if (type != ENTITY_TYPE::AIR_ENEMY) 
	{
		current_acceleration.x = gravity.x;
		current_acceleration.y = gravity.y;
	}

	current_position.x += current_velocity.x;
	current_position.y += current_velocity.y;

	state = ENTITY_STATES::ST_IDLE;

	if (current_position.x < destination.x)
	{
		state = ENTITY_STATES::ST_RIGHT;
		current_velocity.x = normalized_movement_speed;
		current_velocity.y = 0;
		if ((current_position.x + current_velocity.x) > destination.x)
		{
			current_position.x = destination.x;
			current_velocity = { 0,0 };
		}
	}
	else if (current_position.x > destination.x)
	{
		state = ENTITY_STATES::ST_LEFT;
		current_velocity.x = -normalized_movement_speed;
		current_velocity.y = 0;
		if ((current_position.x + current_velocity.x) < destination.x)
		{
			current_position.x = destination.x;
			current_velocity = { 0,0 };
		}
	}
	else if (current_position.y < destination.y)
	{
		if (state == ENTITY_STATES::ST_IDLE)
		{
			if (type == ENTITY_TYPE::AIR_ENEMY || type == ENTITY_TYPE::UNDERGROUND_ENEMY)
			{
				state = ENTITY_STATES::ST_DOWN;
				current_velocity.y = normalized_movement_speed;
				current_velocity.x = 0;
			}
			else
			{
				current_velocity.x += current_acceleration.x;
				current_velocity.y += current_acceleration.y;
			}
		}
		if ((current_position.y + current_velocity.y) > destination.y)
		{
			current_position.y = destination.y;
			current_velocity = { 0,0 };
		}
	}
	else if (current_position.y > destination.y)
	{
		if (state == ENTITY_STATES::ST_IDLE)
		{
			state = ENTITY_STATES::ST_IDLE;
			current_velocity.y = -normalized_movement_speed;
			current_velocity.x = 0;
		}

		if ((current_position.y + current_velocity.y) < destination.y)
		{
			current_position.y = destination.y;
			current_velocity = { 0,0 };
		}
	}
	else
	{
		current_velocity.x = 0;
		current_velocity.y = 0;
	}
}

void AutonomousEntity::NextStep()
{
	if (pathPtr->count() != 0)
	{
		iPoint temp = App->map->MapToWorld(pathPtr->start->data.x, pathPtr->start->data.y);
		destination.x = temp.x;
		destination.y = temp.y;
		pathPtr->del(pathPtr->start);	
	}
}

