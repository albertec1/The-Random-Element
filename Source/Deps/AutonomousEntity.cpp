#include "AutonomousEntity.h"
#include "j1Render.h"
#include "Pathfinding.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include "p2Point.h"

AutonomousEntity::AutonomousEntity(iPoint pos, ENTITY_TYPE type) : j1MovingEntity(pos, type)
{
	name.create("autonomousEntity");
	entityReach = 0;
	pathfindingRange = 0;
	player = nullptr;
	target = nullptr;
	starting_position.x = pos.x;
	starting_position.y = pos.y;
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

	//-- Load range depending on type.
	pathfindingRange = 300;
	entityReach = 5;
	destination = current_position;
	pathPtr = &path;
	return true;
}

bool AutonomousEntity::Start()
{
	player = (j1Entity*)App->manager->player;
	
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
				target = player;

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
	return true;
}

bool AutonomousEntity::PostUpdate()
{
	return true;
}

bool AutonomousEntity::CleanUp()
{
	return true;
}

bool AutonomousEntity::Draw()
{
	if (type == ENTITY_TYPE::AIR_ENEMY)
		App->render->DrawQuad({current_position.x, current_position.y, 32, 32}, 239, 127, 26, 255);

	if (type == ENTITY_TYPE::GROUND_ENEMY)
		App->render->DrawQuad({ current_position.x, current_position.y, 32, 32 }, 101, 67, 33, 255);
	return true;
}

int AutonomousEntity::FindDistanceToPlayer()
{
	int distance = sqrtf((this->current_position.x - player->current_position.x) * (this->current_position.x - player->current_position.x) + (this->current_position.y - player->current_position.y) * (this->current_position.y - player->current_position.y));
	return distance;
}

void AutonomousEntity::GoTo(iPoint destination, ENTITY_TYPE type)
{
	iPoint mapCurrentPosition = App->map->WorldToMap(current_position.x, current_position.y);
	iPoint mapDestination = App->map->WorldToMap(destination.x, destination.y);
	int distanceToPlayer = FindDistanceToPlayer();

	if (distanceToPlayer <= pathfindingRange)
	{
		int pathSize = App->pathfinding->CreatePath(mapCurrentPosition, mapDestination, type);
		if (pathSize > 0)
		{
			App->pathfinding->CopyPathList(pathPtr); // CopyPathList already clears the path inside.
			path = *pathPtr;
			pathPtr = &path;
			if (pathPtr->end != nullptr)
			{
				this->destination = App->map->MapToWorld(pathPtr->end->data.x, pathPtr->end->data.y); //set the destination
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
				GoTo(player->current_position, type);
			}
		}
	}
	else
	{
		if (pathPtr->count() != 0)
		{
			App->map->MapToWorld(pathPtr->end->data.x, pathPtr->end->data.y);
			pathPtr->clear();
		}
	}
}

void AutonomousEntity::Move(float dt)
{
	current_movementSpeed = movement_speed * dt;

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
		current_velocity.x = current_movementSpeed;
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
		current_velocity.x = -current_movementSpeed;
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
				current_velocity.y = current_movementSpeed;
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
			current_velocity.y = -current_movementSpeed;
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
		destination = App->map->MapToWorld(pathPtr->end->data.x, pathPtr->end->data.y);
		pathPtr->del(pathPtr->end);	
	}
}
