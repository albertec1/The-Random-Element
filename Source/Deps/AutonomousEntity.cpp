#include "AutonomousEntity.h"
#include "j1Render.h"
#include "Pathfinding.h"
#include "j1Collision.h"
#include "j1EntityManager.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "p2Point.h"

AutonomousEntity::AutonomousEntity(fPoint pos, ENTITY_TYPE type, EntityStates state) : j1MovingEntity(pos, type, state)
{
	name.create("autonomousEntity");
	entityReach = 0;
	pathfindingRange = 0;
	target = nullptr;
	startingPosition.x = pos.x;
	startingPosition.y = pos.y;
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

	rectSize.x = stats.child("character_width").attribute("value").as_uint();
	rectSize.y = stats.child("character_height").attribute("value").as_uint();
	currentPosition.x = startingPosition.x;
	currentPosition.y = startingPosition.y;
	movementSpeed = stats.child("movement_speed").attribute("value").as_uint();
	gravity.y = stats.child("gravity").attribute("value").as_float();

	//--- main_Collider creation
	entiyRect.w = stats.child("character_width").attribute("value").as_uint();
	entiyRect.h = stats.child("character_height").attribute("value").as_uint();
	entiyRect.x = stats.child("initial_pos_x").attribute("value").as_uint();
	entiyRect.y = stats.child("initial_pos_y").attribute("value").as_uint();

	texturePath = stats.child("texture_path").attribute("value").as_string();
	
	//entity_collider = App->coll->AddCollider(entity_rect, COLLIDER_TYPE::ENEMY, this);

	//-- Load range depending on type.
	pathfindingRange = 300;
	entityReach = 5;
	destination = currentPosition;
	pathPtr = &path;
	return true;
}

bool AutonomousEntity::Start()
{
	enemyTexture = App->tex->Load(texturePath.GetString());
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

			if (destination != currentPosition)
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
	if (entityCollider != nullptr)
	{
		entityCollider->to_delete = true;
		entityCollider = nullptr;
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
		rotatingAnimation = temp;
		App->render->Blit(enemyTexture, (int)currentPosition.x, (int)currentPosition.y, &rotatingAnimation);
		//App->render->DrawQuad({(int)current_position.x, (int)current_position.y, 32, 32}, 239, 127, 26, 255);
	}
	if (type == ENTITY_TYPE::GROUND_ENEMY)
	{
		SDL_Rect temp;
		temp.x = 33;
		temp.y = 0;
		temp.w = temp.h = 32;
		rotatingAnimation = temp;
		App->render->Blit(enemyTexture, (int)currentPosition.x, (int)currentPosition.y, &rotatingAnimation);
		//App->render->DrawQuad({(int)current_position.x, (int)current_position.y, 32, 32 }, 101, 67, 33, 255);

	}
	return true;
}

int AutonomousEntity::FindDistanceToPlayer()
{
	int distance = sqrtf((this->currentPosition.x - App->manager->player->currentPosition.x) * (this->currentPosition.x - App->manager->player->currentPosition.x) + (this->currentPosition.y - App->manager->player->currentPosition.y) * (this->currentPosition.y - App->manager->player->currentPosition.y));
	return distance;
}

void AutonomousEntity::GoTo(fPoint destination, ENTITY_TYPE type)
{
	iPoint mapCurrentPosition = App->map->WorldToMap((int)currentPosition.x, (int)currentPosition.y);
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
				this->destination = currentPosition; //set the destination
		}
		else
			this->destination = currentPosition; //set the destination
	}
	this->destination = currentPosition; //set the destination
}

void AutonomousEntity::Chase(int range)
{
	if (target == nullptr)
	{   
		if (pathPtr->count() == 0)
		{
			//temporary chase, Entities should be able to chase each other if needed, not only the player.
			{
				GoTo(App->manager->player->currentPosition, type);
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
	normalizedMovementSpeed = movementSpeed * dt;

	if (type != ENTITY_TYPE::AIR_ENEMY) 
	{
		currentAcceleration.x = gravity.x;
		currentAcceleration.y = gravity.y;
	}

	currentPosition.x += currentVelocity.x;
	currentPosition.y += currentVelocity.y;

	state = EntityStates::ST_IDLE;

	if (currentPosition.x < destination.x)
	{
		state = EntityStates::ST_RIGHT;
		currentVelocity.x = normalizedMovementSpeed;
		currentVelocity.y = 0;
		if ((currentPosition.x + currentVelocity.x) > destination.x)
		{
			currentPosition.x = destination.x;
			currentVelocity = { 0,0 };
		}
	}
	else if (currentPosition.x > destination.x)
	{
		state = EntityStates::ST_LEFT;
		currentVelocity.x = -normalizedMovementSpeed;
		currentVelocity.y = 0;
		if ((currentPosition.x + currentVelocity.x) < destination.x)
		{
			currentPosition.x = destination.x;
			currentVelocity = { 0,0 };
		}
	}
	else if (currentPosition.y < destination.y)
	{
		if (state == EntityStates::ST_IDLE)
		{
			if (type == ENTITY_TYPE::AIR_ENEMY || type == ENTITY_TYPE::UNDERGROUND_ENEMY)
			{
				state = EntityStates::ST_DOWN;
				currentVelocity.y = normalizedMovementSpeed;
				currentVelocity.x = 0;
			}
			else
			{
				currentVelocity.x += currentAcceleration.x;
				currentVelocity.y += currentAcceleration.y;
			}
		}
		if ((currentPosition.y + currentVelocity.y) > destination.y)
		{
			currentPosition.y = destination.y;
			currentVelocity = { 0,0 };
		}
	}
	else if (currentPosition.y > destination.y)
	{
		if (state == EntityStates::ST_IDLE)
		{
			state = EntityStates::ST_IDLE;
			currentVelocity.y = -normalizedMovementSpeed;
			currentVelocity.x = 0;
		}

		if ((currentPosition.y + currentVelocity.y) < destination.y)
		{
			currentPosition.y = destination.y;
			currentVelocity = { 0,0 };
		}
	}
	else
	{
		currentVelocity.x = 0;
		currentVelocity.y = 0;
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

