
#include "j1EntityPlayer.h"
#include "j1MovingEntity.h"
#include "j1Collision.h"
#include "PugiXml/src/pugixml.hpp"

class j1EntityPlayer::j1EntityPlayer(iPoint pos, ENTITY_TYPE type) : j1MovingEntity(pos, type)
{
	bool j1EntityPlayer::Awake(pugi::xml_node& node)
	{
		//Player loaded from xml
		pugi::xml_node colliders = node.child("player").child("colliders");
		pugi::xml_node player_stats = node.child("player").child("player_stats");
	
		size.x = player_stats.child("charachter_width").attribute("value").as_uint();
		size.y = player_stats.child("character_height").attribute("value").as_uint();
		starting_position.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
		starting_position.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
		surrent_position.x = starting_position.x;
		current_position.y = starting_position.y;
		velocity = player_stats.child("PlayerVel_w").attribute("value").as_uint();
		gravity = player_stats.child("Gravity").attribute("value").as_float();
		falling_velocity = player_stats.child("falling_velocity").attribute("value").as_float();
	
		//--- main_Collider creation
		entity_rect.w = player_stats.child("character_width").attribute("value").as_uint();
		entity_rect.h = player_stats.child("character_height").attribute("value").as_uint();
		entity_rect.x = player_stats.child("initial_pos_x").attribute("value").as_uint();
		entity_rect.y = player_stats.child("initial_pos_y").attribute("value").as_uint();
		entity_collider = App->coll->AddCollider(EntityRect, COLLIDER_TYPE::PLAYER);
	
		//--collider ID's
		WALL_id = colliders.child("tile_types").child("WALL").attribute("value").as_uint();
		CLIMB_WALL_id = colliders.child("tile_types").child("CLIMB_WALL").attribute("value").as_uint();
		BONUS_id = colliders.child("tile_types").child("BONUS").attribute("value").as_uint();
	
		EntityCollider->callback = this;
		return true;
	}
};