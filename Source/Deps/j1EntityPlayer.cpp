
#include "j1App.h"
#include "j1Entity.h"
#include "j1MovingEntity.h"
#include "j1EntityPlayer.h"
#include "j1Collision.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Timer.h"
#include "p2Log.h"
#include "PugiXml/src/pugixml.hpp"

#define SPECIAL_TIMER 0.3

j1EntityPlayer::j1EntityPlayer(iPoint pos, ENTITY_TYPE type) : j1MovingEntity(pos, type)
{
	name.create("player");	
}

j1EntityPlayer::~j1EntityPlayer()
{
}

bool j1EntityPlayer::Awake(pugi::xml_node& node)
{
	//Player loaded from xml
	pugi::xml_node player_stats = node.child("player").child("player_stats");

	rect_size.x =			player_stats.child("charachter_width").attribute("value").as_uint();
	rect_size.y =			player_stats.child("character_height").attribute("value").as_uint();
	starting_position.x =	player_stats.child("initial_pos_x").attribute("value").as_uint();
	starting_position.y =	player_stats.child("initial_pos_y").attribute("value").as_uint();
	current_position.x =	starting_position.x;
	current_position.y =	starting_position.y;
	movement_speed =		player_stats.child("movement_speed").attribute("value").as_uint();
	max_special_range =		player_stats.child("special_range").attribute("value").as_uint();
	gravity.y =				player_stats.child("gravity").attribute("value").as_float();

	//--- main_Collider creation
	entity_rect.w =			player_stats.child("character_width").attribute("value").as_uint();
	entity_rect.h =			player_stats.child("character_height").attribute("value").as_uint();
	entity_rect.x =			player_stats.child("initial_pos_x").attribute("value").as_uint();
	entity_rect.y =			player_stats.child("initial_pos_y").attribute("value").as_uint();

	texture_path =			player_stats.child("texture_path").attribute("value").as_string();

	entity_collider = App->coll->AddCollider(entity_rect, COLLIDER_TYPE::PLAYER);
	entity_collider->callback = this; 
	
	pugi::xml_node spritesheet = node.child("player").child("sprites");
	for (pugi::xml_node animation = spritesheet.child("animation"); animation; animation = animation.next_sibling("animation"))
	{
		p2SString name = animation.attribute("name").as_string();
 		int coll = animation.attribute("coll").as_int();
		int row = animation.attribute("row").as_int();
		int width = animation.attribute("width").as_int();
		int height = animation.attribute("height").as_int();
		int collumns = animation.attribute("collumns").as_int();
		int frames = animation.attribute("frames").as_int();
		float speed = animation.attribute("speed").as_float();
		bool loop = animation.attribute("loop").as_bool();

		Animate(name, coll, row, width, height, collumns, frames, speed, loop);
	}

	return true;
}

bool j1EntityPlayer::Start()
{
	entity_texture = App->tex->Load(texture_path.GetString());

	movement_speed = movement_speed * App->win->GetScale();

	state = ENTITY_STATES::ST_AIR;
	entity_rect.x = current_position.x;
	entity_rect.y = current_position.y;

	current_acceleration.x += gravity.x;
	current_acceleration.y += gravity.y; 
	return true;
}


bool j1EntityPlayer::PreUpdate()
{
	bool ret = true;
	//SHORTCUTS INPUTS--- 
	player_input.F1_enabled = App->input->keyboard[SDL_SCANCODE_F1] == j1KeyState::KEY_DOWN;
	player_input.F2_enabled = App->input->keyboard[SDL_SCANCODE_F2] == j1KeyState::KEY_DOWN;
	player_input.F3_enabled = App->input->keyboard[SDL_SCANCODE_F3] == j1KeyState::KEY_DOWN;
	player_input.F5_enabled = App->input->keyboard[SDL_SCANCODE_F5] == j1KeyState::KEY_DOWN;
	player_input.F6_enabled = App->input->keyboard[SDL_SCANCODE_F6] == j1KeyState::KEY_DOWN;
	player_input.F7_enabled = App->input->keyboard[SDL_SCANCODE_F7] == j1KeyState::KEY_DOWN;
	player_input.F8_enabled = App->input->keyboard[SDL_SCANCODE_F8] == j1KeyState::KEY_DOWN;

	if (god_mode == false)
	{
		player_input.W_enabled = App->input->keyboard[SDL_SCANCODE_W] == j1KeyState::KEY_REPEAT;

		if (App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_DOWN)
			player_input.A_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_UP)
			player_input.A_enabled = false;

		player_input.S_enabled = App->input->keyboard[SDL_SCANCODE_S] == j1KeyState::KEY_DOWN;

		if (App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_DOWN)
			player_input.D_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_UP)
			player_input.D_enabled = false;

		player_input.K_enabled = App->input->keyboard[SDL_SCANCODE_K] == j1KeyState::KEY_DOWN;

		/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_DOWN)
			player_input.Space_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_UP)
			player_input.Space_enabled = false;*/

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_DOWN)
			player_input.Space_enabled = true;
		else
			player_input.Space_enabled = false;

	}
	else
	{
	player_input.W_GOD_enabled = App->input->keyboard[SDL_SCANCODE_W] == j1KeyState::KEY_REPEAT;
	player_input.A_GOD_enabled = App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_REPEAT;
	player_input.S_GOD_enabled = App->input->keyboard[SDL_SCANCODE_S] == j1KeyState::KEY_REPEAT;
	player_input.D_GOD_enabled = App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_REPEAT;
	}

	//PLAYER STATES
	if (god_mode == false)
	{
		current_acceleration.x = gravity.x;
		current_acceleration.y = gravity.y;
		current_velocity.x += current_acceleration.x;
		current_velocity.y += current_acceleration.y;
		current_position.x += current_velocity.x;
		current_position.y += current_velocity.y;

		switch (state)
		{
		case ENTITY_STATES::ST_IDLE:
			if (player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_LEFT;
			}
			if (player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_RIGHT;
			}
			if (player_input.Space_enabled)
			{
				state = ENTITY_STATES::ST_JUMP;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_RIGHT;
			}
			break;

		case ENTITY_STATES::ST_IDLE_FLIPPED:
			if (player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_LEFT;
			}
			if (player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_RIGHT;
			}
			if (player_input.Space_enabled)
			{
				state = ENTITY_STATES::ST_JUMP;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_LEFT;
			}

			break;

		case ENTITY_STATES::ST_LEFT:
			if (!player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_IDLE_FLIPPED;
			}
			if (player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_RIGHT;
			}
			if (player_input.Space_enabled && jump_available)
			{
				state = ENTITY_STATES::ST_JUMP_LEFT;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_LEFT;
			}
			break;

		case ENTITY_STATES::ST_RIGHT:
			if (!player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_IDLE;
			}
			if (player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_LEFT;
			}
			if (player_input.Space_enabled && jump_available)
			{
				state = ENTITY_STATES::ST_JUMP_RIGHT;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_RIGHT;
			}
			break;


		case ENTITY_STATES::ST_JUMP:
			if (jump_available == false)
			{
				state = ENTITY_STATES::ST_AIR;
			}
			break;

		case ENTITY_STATES::ST_JUMP_LEFT:

			if (jump_available == false)
			{
				state = ENTITY_STATES::ST_LEFT_JUMPING;
			}
			break;

		case ENTITY_STATES::ST_JUMP_RIGHT:
			if (jump_available == false)
			{
				state = ENTITY_STATES::ST_RIGHT_JUMPING;
			}
			break;

		case ENTITY_STATES::ST_LEFT_JUMPING:
			if (player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_AIR_RIGHT;
			}
			if (jump_available == true && player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_LEFT;
			}
			else if (jump_available == true)
			{
				state = ENTITY_STATES::ST_IDLE_FLIPPED;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_LEFT;
			}
			jumping = false;
			break;

		case ENTITY_STATES::ST_RIGHT_JUMPING:
			if (player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_AIR_LEFT;
			}

			if (jump_available == true && player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_RIGHT;
			}
			else if (jump_available == true)
			{
				state = ENTITY_STATES::ST_IDLE;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_RIGHT;
			}
			jumping = false;
			break;

		case ENTITY_STATES::ST_AIR:
			if (jump_available == true)
			{
				state = ENTITY_STATES::ST_IDLE;
			}
			if (player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_AIR_LEFT;
			}
			if (player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_AIR_RIGHT;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_RIGHT;
			}
			jumping = false;
			break;

		case ENTITY_STATES::ST_AIR_FLIPPED:
			if (jump_available == true)
			{
				state = ENTITY_STATES::ST_IDLE;
			}
			if (player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_AIR_LEFT;
			}
			if (player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_AIR_RIGHT;

			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_LEFT;
			}
			jumping = false;
			break;
		
		case ENTITY_STATES::ST_AIR_LEFT:
			
			if (!player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_AIR_FLIPPED;
			}
			if (player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_AIR_RIGHT;
			}
			if (jump_available == true && player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_LEFT;
			}
			else if (jump_available == true)
			{
				state = ENTITY_STATES::ST_IDLE_FLIPPED;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_LEFT;
			}
			break;

		case ENTITY_STATES::ST_AIR_RIGHT:

			if (!player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_AIR;
			}
			if (player_input.A_enabled)
			{
				state = ENTITY_STATES::ST_AIR_LEFT;
			}
			if (jump_available == true && player_input.D_enabled)
			{
				state = ENTITY_STATES::ST_RIGHT;
			}
			else if (jump_available == true)
			{
				state = ENTITY_STATES::ST_IDLE;
			}
			if (player_input.K_enabled)
			{
				state = ENTITY_STATES::ST_DO_SPECIAL_RIGHT;
			}
			break;

		case ENTITY_STATES::ST_DO_SPECIAL_LEFT:
			if (special_distance != 0)
			{
				state = ENTITY_STATES::ST_SPECIAL_LEFT;
			}
			else
			{
				if (jump_available == false)
				{
					if (player_input.A_enabled == true)
					{
						state = ENTITY_STATES::ST_AIR_LEFT;
					}
					else
					{
						state = ENTITY_STATES::ST_AIR_FLIPPED;
					}
				}
				else
				{
					if (player_input.A_enabled == true)
					{
						state = ENTITY_STATES::ST_LEFT;
					}
					else
					{
						state = ENTITY_STATES::ST_IDLE_FLIPPED;
					}
				}
			}
			break;
		case ENTITY_STATES::ST_DO_SPECIAL_RIGHT:
			if (special_distance != 0)
			{
				state = ENTITY_STATES::ST_SPECIAL_RIGHT;
			}
			else
			{
				if (jump_available == false)
				{
					if (player_input.D_enabled == true)
					{
						state = ENTITY_STATES::ST_AIR_RIGHT;
					}
					else
					{
						state = ENTITY_STATES::ST_AIR;
					}
				}
				else
				{
					if (player_input.A_enabled == true)
					{
						state = ENTITY_STATES::ST_RIGHT;
					}
					else
					{
						state = ENTITY_STATES::ST_IDLE;
					}
				}
			}
			break;
		case ENTITY_STATES::ST_SPECIAL_LEFT:
			if (special_timer == 0)
			{
				if (jump_available == false)
				{
					if (player_input.A_enabled)
					{
						state = ENTITY_STATES::ST_AIR_LEFT;
					}
					else
					{
						state = ENTITY_STATES::ST_AIR_FLIPPED;
					}
				}
				else
				{
					if (player_input.A_enabled)
					{
						state = ENTITY_STATES::ST_LEFT;
					}
					else
					{
						state = ENTITY_STATES::ST_IDLE_FLIPPED;
					}
				}
			}
			break;
		case ENTITY_STATES::ST_SPECIAL_RIGHT:
			if (special_timer == 0)
			{
				if (jump_available == false)
				{
					if (player_input.D_enabled)
					{
						state = ENTITY_STATES::ST_AIR_RIGHT;
					}
					else
					{
						state = ENTITY_STATES::ST_AIR;
					}
				}
				else
				{
					if (player_input.A_enabled)
					{
						state = ENTITY_STATES::ST_RIGHT;
					}
					else
					{
						state = ENTITY_STATES::ST_IDLE;
					}
				}
			}
			break;
		}	
	}
	return true;
}

bool j1EntityPlayer::Update(float dt, bool doLogic)
{
	//MOVEMENT THROUGH STATES
	movement_speed = movement_speed * dt;
	switch (state)
	{
	case ENTITY_STATES::ST_IDLE:
		if (App->allow_debug_log == true)
			LOG("IDLE");

		current_velocity.x = 0;

		flipped = false;
		current_animation = GetAnimation("idle");
		break;

	case ENTITY_STATES::ST_IDLE_FLIPPED:
		if (App->allow_debug_log == true)
			LOG("IDLE");

		current_velocity.x = 0;

		flipped = true;
		current_animation = GetAnimation("idle");
		break;

  	case ENTITY_STATES::ST_LEFT:
		if (App->allow_debug_log == true)
			LOG("MOVING LEFT");

		current_velocity.x = -movement_speed;

		flipped = true;
		current_animation = GetAnimation("run");
		break;

	case ENTITY_STATES::ST_RIGHT:
 		if (App->allow_debug_log == true)
			LOG("MOVING RIGHT");

		current_velocity.x = movement_speed;

		flipped = false;
		current_animation = GetAnimation("run");
		break;

	case ENTITY_STATES::ST_JUMP:
		if (App->allow_debug_log == true)
			LOG("STRAIGHT JUMP");

		current_velocity.y -= 50;

		flipped = false;
		jumping = true;
		jump_available = false;
		current_animation = GetAnimation("idle");
		break;

	case ENTITY_STATES::ST_JUMP_RIGHT:
		if (App->allow_debug_log == true)
			LOG("RIGHT JUMP");

		current_velocity.y -= 50;

		flipped = false;
		jumping = true;
		jump_available = false;
		current_animation = GetAnimation("idle");
		break;

	case ENTITY_STATES::ST_JUMP_LEFT:
		if (App->allow_debug_log == true)
			LOG("LEFT JUMP");

		current_velocity.y -= 50;

		flipped = true;
		jumping = true;
		jump_available = false;
		current_animation = GetAnimation("idle");
		break;

	case ENTITY_STATES::ST_LEFT_JUMPING:
		if (App->allow_debug_log == true)
			LOG("JUMPING LEFT");

		flipped = true;
		current_animation = GetAnimation("jump");
		break;

	case ENTITY_STATES::ST_RIGHT_JUMPING:
		if (App->allow_debug_log == true)
			LOG("JUMPING RIGHT");
		flipped = false;
		current_animation = GetAnimation("jump");
		break;	

	case ENTITY_STATES::ST_AIR_LEFT:
		if (App->allow_debug_log == true)
			LOG("MOVING LEFT ON AIR");

		flipped = true;
		current_velocity.x = -movement_speed * 0.5 * dt;
		current_animation = GetAnimation("fall");
		break;
		
	case ENTITY_STATES::ST_AIR_RIGHT:
		if (App->allow_debug_log == true)
			LOG("MOVING RIGHT ON AIR");

		flipped = false;
		current_velocity.x = movement_speed * 0.5 * dt;
		current_animation = GetAnimation("fall");
		break;

	case ENTITY_STATES::ST_AIR_FLIPPED:
		if (App->allow_debug_log == true)
			LOG("FALLING FLIPPED");

		flipped = true;
		current_animation = GetAnimation("fall");
		break;

	case ENTITY_STATES::ST_AIR:
		if (App->allow_debug_log == true)
			LOG("FALLING");

		current_animation = GetAnimation("fall");
		break;

	case ENTITY_STATES::ST_DEAD:
		if (App->allow_debug_log == true)
			LOG("DYING");
		current_animation = GetAnimation("die");
		break;
	
	case ENTITY_STATES::ST_DO_SPECIAL_LEFT:
		if (App->allow_debug_log == true)
			LOG("DO SPECIAL LEFT");

		special_distance = DoSpecialLeft();
		special_timer = SPECIAL_TIMER;
		 
		GetAnimation("special")->Reset();
		break;

	case ENTITY_STATES::ST_DO_SPECIAL_RIGHT: 
		if (App->allow_debug_log == true)
			LOG("DO SPECIAL RIGHT");

		special_distance = DoSpecialRight();
		special_timer = SPECIAL_TIMER;

		GetAnimation("special")->Reset();
		break;

	case ENTITY_STATES::ST_SPECIAL_LEFT:
		if (App->allow_debug_log == true)
			LOG("SPECIAL LEFT");

		current_velocity = { 0,0 };
		current_acceleration = { 0,0 };

		current_animation = GetAnimation("special");
		special_timer -= dt;
		if (special_timer <= 0)
		{
			special_timer = 0;
			current_position.x -= special_distance;
			special_last_frame = false;
		}
		break;

	case ENTITY_STATES::ST_SPECIAL_RIGHT:
		if (App->allow_debug_log == true)
			LOG("SPECIAL RIGHT");
		 
		current_velocity = { 0,0 };
		current_acceleration = { 0,0 };

		current_animation = GetAnimation("special");
		special_timer -= dt;
		if (special_timer <= 0)
		{
			special_timer = 0;
			current_position.x += special_distance;
			special_last_frame = false;
		}
		break;
	}	

	if (special_last_frame == false && state != ENTITY_STATES::ST_SPECIAL_RIGHT && state != ENTITY_STATES::ST_SPECIAL_LEFT)
	{
		current_animation = GetAnimation("special");
		special_last_frame = true;
	}

	if (current_velocity.x > MAX_VELOCITY)
		current_velocity.x = MAX_VELOCITY;
	else if (current_velocity.x < -MAX_VELOCITY)
		current_velocity.x = -MAX_VELOCITY;

	if (current_velocity.y > MAX_VELOCITY)
		current_velocity.y = MAX_VELOCITY;
	if (current_velocity.y < -(MAX_VELOCITY*3.5))
		current_velocity.y = MAX_VELOCITY*3.5;

	entity_rect.x = current_position.x;
	entity_rect.y = current_position.y;
	entity_collider->SetPos(current_position.x, current_position.y);

	return true;
}

bool j1EntityPlayer::PostUpdate()
{
	entity_rect.x = current_position.x;
	entity_rect.y = current_position.y;
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

int j1EntityPlayer::DoSpecialLeft()
{
	int ret = 0; 

	iPoint teleport_destination = App->map->WorldToMap(current_position.x - max_special_range, current_position.y);
	int tile_width = App->map->mapdata.tile_width;

	for (teleport_destination; teleport_destination.x < current_position.x; teleport_destination.x += 1)
	{
		if (App->map->metadata->Get(teleport_destination.x, teleport_destination.y) == 0)
		{
			iPoint teleport = App->map->MapToWorld(teleport_destination.x, teleport_destination.y);
			ret = current_position.x - teleport.x;
			break;
		}
	}
	return ret;
}

int j1EntityPlayer::DoSpecialRight()
{
	int ret = 0;

	iPoint teleport_origin = App->map->WorldToMap(current_position.x, current_position.y);
	iPoint teleport_destination = App->map->WorldToMap(current_position.x + max_special_range, current_position.y);

	for (teleport_destination; teleport_destination.x > teleport_origin.x; teleport_destination.x -= 1)
	{
		if (App->map->metadata->Get(teleport_destination.x, teleport_destination.y) == 0)
		{
			iPoint teleport = App->map->MapToWorld(teleport_destination.x, teleport_destination.y);
			ret = teleport.x - current_position.x;
			break;
		}
	}
	return ret;
}

void j1EntityPlayer::ResetPlayerAT(int x, int y)
{
	current_acceleration = { 0,0 };
	current_velocity = { 0,0 };
	current_position = { x, y };

	player_state = ENTITY_STATES::ST_IDLE;
}