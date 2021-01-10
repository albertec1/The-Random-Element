#include "j1Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1MovingEntity.h"


j1MovingEntity::j1MovingEntity(fPoint pos, ENTITY_TYPE type, EntityStates _state) : j1Entity(pos, type)
{
	currentPosition = startingPosition;
	normalizedMovementSpeed = 0;
	movementSpeed = 0;
	currentAnimation = nullptr;
	rotatingAnimation = { 0,0,0,0 };
	currentVelocity = { 0,0 };
	state = _state;
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

void j1MovingEntity::Animate(p2SString name, int coll, int row, const int width, const int height, const int collumns, const int frames, float speed, bool loop)
{
	Animation* anim = new Animation(name, speed, loop);
	for (int i = 0; i < frames; i++)
	{
		anim->PushBack({ width * coll, height * row, width, height });
		coll++;
		if (coll == collumns)
		{
			coll = 0;
			row++;
		}
	}
	animations.add(anim);
}

Animation* j1MovingEntity::GetAnimation(p2SString name)
{
	for (p2List_item<Animation*>* animation = animations.start; animation != nullptr; animation = animation->next)
		if (name == animation->data->name)
			return animation->data;

	return nullptr;
}

bool j1MovingEntity::Draw()
{
	bool ret = false;

	//if(current_animation != nullptr)
		rotatingAnimation = currentAnimation->GetCurrentFrame(); 

 	if (ret = App->render->Blit(entityTexture, currentPosition.x, currentPosition.y, &rotatingAnimation, flipped) == 0)
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
