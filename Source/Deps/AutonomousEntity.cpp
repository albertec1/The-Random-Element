#include "AutonomousEntity.h"
#include "j1Render.h"
#include "Pathfinding.h"
#include "j1EntityManager.h"

AutonomousEntity::AutonomousEntity(iPoint pos, ENTITY_TYPE type) : j1MovingEntity(pos, type)
{
	name.create("autonomousEntity");
	target = nullptr;
}

AutonomousEntity::~AutonomousEntity()
{
	target = nullptr;
	path->clear();
}

bool AutonomousEntity::Awake(pugi::xml_node& node)
{
	//Load properties
	pugi::xml_node stats = node.child("player").child("player_stats");

	rect_size.x = stats.child("charachter_width").attribute("value").as_uint();
	rect_size.y = stats.child("character_height").attribute("value").as_uint();
	starting_position.x = stats.child("initial_pos_x").attribute("value").as_uint();
	starting_position.y = stats.child("initial_pos_y").attribute("value").as_uint();
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
	return true;
}

bool AutonomousEntity::Start()
{
	player = (j1Entity*)App->manager->player;
	return false;
}

bool AutonomousEntity::PreUpdate()
{
	return false;
}

bool AutonomousEntity::Update(float dt)
{
	if (dt != 0.0f)
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
	return false;
}

bool AutonomousEntity::PostUpdate()
{
	return false;
}

bool AutonomousEntity::CleanUp()
{
	return false;
}

bool AutonomousEntity::Draw()
{
	App->render->DrawQuad({current_position.x, current_position.y, 32, 32}, 239, 127, 26, 255);
	return false;
}

int AutonomousEntity::FindDistanceToPlayer()
{
	int distance = sqrtf((this->current_position.x - player->current_position.x) * (this->current_position.x - player->current_position.x) + (this->current_position.y - player->current_position.y) * (this->current_position.y - player->current_position.y));
	return distance;
}

void AutonomousEntity::GoTo(iPoint destination, ENTITY_TYPE type)
{
	int pathSize = App->pathfinding->CreatePath(this->current_position, destination, type);
	if (pathSize != 0)
	{
		App->pathfinding->CopyPathList(path); // CopyPathList already clears the path inside.

		this->destination = path->start->data; //set the destination
	}
	else
		this->destination = current_position; 
}

void AutonomousEntity::Chase(int range)
{
	if (target == nullptr)
	{
		if (path->count() == 0)
		{
			//temporary chase, Entities should be able to chase each other if needed, not only the player.
			int distanceToPlayer = FindDistanceToPlayer();
			if (distanceToPlayer != 0)
			{
				GoTo(player->current_position, type);
			}
		}
	}
	else
	{
		if (path->count() != 0)
		{
			destination = path->start->data;
			path->clear();
		}
	}
}

void AutonomousEntity::Move(float dt)
{
	movement_speed = movement_speed * dt;

	if (type != ENTITY_TYPE::AIR_ENEMY) 
	{
		current_acceleration.x = gravity.x;
		current_acceleration.y = gravity.y;
	}

	current_velocity.x += current_acceleration.x;
	current_velocity.y += current_acceleration.y;
	current_position.x += current_velocity.x;
	current_position.y += current_velocity.y;

	state = ENTITY_STATES::ST_IDLE;

	if (current_position.x < destination.x)
	{
		state = ENTITY_STATES::ST_RIGHT;
		current_position.x = movement_speed;
		if (current_position.x > destination.x)
			current_position.x = destination.x;
	}
	else if (current_position.x > destination.x)
	{
		state = ENTITY_STATES::ST_LEFT;
		current_position.x = -movement_speed;

		if (current_position.x < destination.x)
			current_position.x = destination.x;
	}
	else if (current_position.y < destination.y)
	{
		if (state == ENTITY_STATES::ST_IDLE)
		{
			if (type == ENTITY_TYPE::AIR_ENEMY || type == ENTITY_TYPE::UNDERGROUND_ENEMY)
			{
				state = ENTITY_STATES::ST_DOWN;
				current_position.y = movement_speed;
			}
			else
			{
				//just fall :)
			}
		}
		if (current_position.y > destination.y)
			current_position.y = destination.y;
	}
	else if (current_position.y > destination.y)
	{
		if (state == ENTITY_STATES::ST_IDLE)
		{
			state = ENTITY_STATES::ST_IDLE;
			current_position.y = -movement_speed;
		}

		if (current_position.y < destination.y)
			current_position.y = destination.y;
	}
	else
	{
		current_velocity.x = 0;
	}
}

void AutonomousEntity::NextStep()
{
	if (path->count() != 0)
	{
		path->del(path->start);
		destination = path->start->data;
	}
}
