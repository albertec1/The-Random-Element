
#include "j1App.h"
#include "j1Entity.h"
#include "j1MovingEntity.h"
#include "j1EntityPlayer.h"
#include "j1Collision.h"
#include "p2Log.h"
#include "PugiXml/src/pugixml.hpp"

j1EntityPlayer::j1EntityPlayer(iPoint pos, ENTITY_TYPE type) : j1MovingEntity(pos, type)
{

}

j1EntityPlayer::~j1EntityPlayer()
{
}

bool j1EntityPlayer::Awake(pugi::xml_node& node)
{
	//Player loaded from xml
	pugi::xml_node colliders = node.child("player").child("colliders");
	pugi::xml_node player_stats = node.child("player").child("player_stats");

	size.x = player_stats.child("charachter_width").attribute("value").as_uint();
	size.y = player_stats.child("character_height").attribute("value").as_uint();
	starting_position.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
	starting_position.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
	current_position.x = starting_position.x;
	current_position.y = starting_position.y;
	gravity.y = player_stats.child("Gravity").attribute("value").as_float();

	//--- main_Collider creation
	entity_rect.w = player_stats.child("character_width").attribute("value").as_uint();
	entity_rect.h = player_stats.child("character_height").attribute("value").as_uint();
	entity_rect.x = player_stats.child("initial_pos_x").attribute("value").as_uint();
	entity_rect.y = player_stats.child("initial_pos_y").attribute("value").as_uint();
	entity_collider = App->coll->AddCollider(entity_rect, COLLIDER_TYPE::PLAYER);

	entity_collider->callback = this;
	return true;
}

bool j1EntityPlayer::Start()
{
	//LOAD TEXTURES 

	state = ENTITY_STATES::ST_IDLE;
	entity_rect = { current_position.x, current_position.y, size.x, size.y };
	return true;
}


bool j1EntityPlayer::PreUpdate()
{
	return true;
}

bool j1EntityPlayer::Update(float dt, bool doLogic)
{
	entity_collider->SetPos(current_position.x, current_position.y);

	return true;
}

bool j1EntityPlayer::CleanUp()
{
	return true;
}

void j1EntityPlayer::OnCollision(Collider* c1, Collider* c2)
{
	return;
}
