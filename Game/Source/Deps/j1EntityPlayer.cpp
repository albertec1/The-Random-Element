
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
#include "External/PugiXml/src/pugixml.hpp"

#define SPECIAL_TIMER 0.3

j1EntityPlayer::j1EntityPlayer(fPoint pos, ENTITY_TYPE type, EntityStates state) : j1MovingEntity(pos, type, state)
{
	name.create("player");	
	maxSpecialRange = 0;
	playerState = state;
	specialDistance = 0;
	specialLastFrame = 0;
	specialTimer = 0;
	startingPosition = pos;
	gravity = { 0,0 };
	currentAcceleration = { 0,0 };
}

j1EntityPlayer::~j1EntityPlayer()
{
}

bool j1EntityPlayer::Awake(pugi::xml_node& node)
{
	//Player loaded from xml
	pugi::xml_node player_stats = node.child("player").child("player_stats");

	rectSize.x =			player_stats.child("charachter_width").attribute("value").as_uint();
	rectSize.y =			player_stats.child("character_height").attribute("value").as_uint();

	if (startingPosition.x == 0|| startingPosition.y == 0)
	{
		startingPosition.x = player_stats.child("initial_pos_x").attribute("value").as_uint();
		startingPosition.y = player_stats.child("initial_pos_y").attribute("value").as_uint();
	}
	currentPosition.x =	startingPosition.x;
	currentPosition.y =	startingPosition.y;
	movementSpeed =		player_stats.child("movement_speed").attribute("value").as_uint();
	maxSpecialRange =		player_stats.child("special_range").attribute("value").as_uint();
	gravity.y =				player_stats.child("gravity").attribute("value").as_float();
	gravity.x =				0;

	//--- main_Collider creation
	entiyRect.w =			player_stats.child("character_width").attribute("value").as_uint();
	entiyRect.h =			player_stats.child("character_height").attribute("value").as_uint();
	entiyRect.x =			player_stats.child("initial_pos_x").attribute("value").as_uint();
	entiyRect.y =			player_stats.child("initial_pos_y").attribute("value").as_uint();

	texturePath =			player_stats.child("texture_path").attribute("value").as_string();

	entityCollider = App->coll->AddCollider(entiyRect, COLLIDER_TYPE::PLAYER, this);

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
	entityTexture = App->tex->Load(texturePath.GetString());

	movementSpeed = movementSpeed * App->win->GetScale();

	state = EntityStates::ST_AIR;
	entiyRect.x = currentPosition.x;
	entiyRect.y = currentPosition.y;

	currentAcceleration.x = gravity.x;
	currentAcceleration.y += gravity.y; 
	return true;
}


bool j1EntityPlayer::PreUpdate()
{
	bool ret = true;
	godMode = App->manager->godMode;
	//SHORTCUTS INPUTS--- 
	playerInput.F1_enabled = App->input->keyboard[SDL_SCANCODE_F1] == j1KeyState::KEY_DOWN;
	playerInput.F2_enabled = App->input->keyboard[SDL_SCANCODE_F2] == j1KeyState::KEY_DOWN;
	playerInput.F3_enabled = App->input->keyboard[SDL_SCANCODE_F3] == j1KeyState::KEY_DOWN;
	playerInput.F5_enabled = App->input->keyboard[SDL_SCANCODE_F5] == j1KeyState::KEY_DOWN;
	playerInput.F6_enabled = App->input->keyboard[SDL_SCANCODE_F6] == j1KeyState::KEY_DOWN;
	playerInput.F7_enabled = App->input->keyboard[SDL_SCANCODE_F7] == j1KeyState::KEY_DOWN;
	playerInput.F8_enabled = App->input->keyboard[SDL_SCANCODE_F8] == j1KeyState::KEY_DOWN;

	if (godMode == false)
	{
		playerInput.W_enabled = App->input->keyboard[SDL_SCANCODE_W] == j1KeyState::KEY_REPEAT;

		if (App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_DOWN)
			playerInput.A_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_UP)
			playerInput.A_enabled = false;

		playerInput.S_enabled = App->input->keyboard[SDL_SCANCODE_S] == j1KeyState::KEY_DOWN;

		if (App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_DOWN)
			playerInput.D_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_UP)
			playerInput.D_enabled = false;

		playerInput.K_enabled = App->input->keyboard[SDL_SCANCODE_K] == j1KeyState::KEY_DOWN;

		/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_DOWN)
			player_input.Space_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_UP)
			player_input.Space_enabled = false;*/

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == j1KeyState::KEY_DOWN)
			playerInput.Space_enabled = true;
		else
			playerInput.Space_enabled = false;

	}
	else
	{
		if (App->input->keyboard[SDL_SCANCODE_W] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_W] == j1KeyState::KEY_DOWN)
			playerInput.W_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_W] == j1KeyState::KEY_UP)
			playerInput.W_enabled = false;

		if (App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_DOWN)
			playerInput.A_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_A] == j1KeyState::KEY_UP)
			playerInput.A_enabled = false;

		if (App->input->keyboard[SDL_SCANCODE_S] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_S] == j1KeyState::KEY_DOWN)
			playerInput.S_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_S] == j1KeyState::KEY_UP)
			playerInput.S_enabled = false;

		if (App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_REPEAT || App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_DOWN)
			playerInput.D_enabled = true;
		else if (App->input->keyboard[SDL_SCANCODE_D] == j1KeyState::KEY_UP)
			playerInput.D_enabled = false;

		playerInput.K_enabled = App->input->keyboard[SDL_SCANCODE_K] == j1KeyState::KEY_DOWN;
	}

	//PLAYER STATES
	if (godMode == false)
	{
		currentAcceleration.x = 0;
		currentAcceleration.y = gravity.y;
		currentVelocity.x += currentAcceleration.x;
		currentVelocity.y += currentAcceleration.y;
		currentPosition.x += currentVelocity.x;
		currentPosition.y += currentVelocity.y;

		switch (state)
		{
		case EntityStates::ST_IDLE:
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.Space_enabled)
			{
				state = EntityStates::ST_JUMP;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			break;

		case EntityStates::ST_IDLE_FLIPPED:
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.Space_enabled)
			{
				state = EntityStates::ST_JUMP;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_LEFT;
			}

			break;

		case EntityStates::ST_LEFT:
			if (!playerInput.A_enabled)
			{
				state = EntityStates::ST_IDLE_FLIPPED;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.Space_enabled && jumpAvailable)
			{
				state = EntityStates::ST_JUMP_LEFT;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_LEFT;
			}
			break;

		case EntityStates::ST_RIGHT:
			if (!playerInput.D_enabled)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.Space_enabled && jumpAvailable)
			{
				state = EntityStates::ST_JUMP_RIGHT;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			break;


		case EntityStates::ST_JUMP:
			if (jumpAvailable == false)
			{
				state = EntityStates::ST_AIR;
			}
			break;

		case EntityStates::ST_JUMP_LEFT:

			if (jumpAvailable == false)
			{
				state = EntityStates::ST_LEFT_JUMPING;
			}
			break;

		case EntityStates::ST_JUMP_RIGHT:
			if (jumpAvailable == false)
			{
				state = EntityStates::ST_RIGHT_JUMPING;
			}
			break;

		case EntityStates::ST_LEFT_JUMPING:
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_AIR_RIGHT;
			}
			if (jumpAvailable == true && playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			else if (jumpAvailable == true)
			{
				state = EntityStates::ST_IDLE_FLIPPED;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_LEFT;
			}
			jumping = false;
			break;

		case EntityStates::ST_RIGHT_JUMPING:
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_AIR_LEFT;
			}

			if (jumpAvailable == true && playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			else if (jumpAvailable == true)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			jumping = false;
			break;

		case EntityStates::ST_AIR:
			if (jumpAvailable == true)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_AIR_LEFT;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_AIR_RIGHT;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			jumping = false;
			break;

		case EntityStates::ST_AIR_FLIPPED:
			if (jumpAvailable == true)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_AIR_LEFT;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_AIR_RIGHT;

			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_LEFT;
			}
			jumping = false;
			break;
		
		case EntityStates::ST_AIR_LEFT:
			
			if (!playerInput.A_enabled)
			{
				state = EntityStates::ST_AIR_FLIPPED;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_AIR_RIGHT;
			}
			if (jumpAvailable == true && playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			else if (jumpAvailable == true)
			{
				state = EntityStates::ST_IDLE_FLIPPED;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_LEFT;
			}
			break;

		case EntityStates::ST_AIR_RIGHT:

			if (!playerInput.D_enabled)
			{
				state = EntityStates::ST_AIR;
			}
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_AIR_LEFT;
			}
			if (jumpAvailable == true && playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			else if (jumpAvailable == true)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			break;

		case EntityStates::ST_DO_SPECIAL_LEFT:
			if (specialDistance != 0)
			{
				state = EntityStates::ST_SPECIAL_LEFT;
			}
			else
			{
				if (jumpAvailable == false)
				{
					if (playerInput.A_enabled == true)
					{
						state = EntityStates::ST_AIR_LEFT;
					}
					else
					{
						state = EntityStates::ST_AIR_FLIPPED;
					}
				}
				else
				{
					if (playerInput.A_enabled == true)
					{
						state = EntityStates::ST_LEFT;
					}
					else
					{
						state = EntityStates::ST_IDLE_FLIPPED;
					}
				}
			}
			break;
		case EntityStates::ST_DO_SPECIAL_RIGHT:
			if (specialDistance != 0)
			{
				state = EntityStates::ST_SPECIAL_RIGHT;
			}
			else
			{
				if (jumpAvailable == false)
				{
					if (playerInput.D_enabled == true)
					{
						state = EntityStates::ST_AIR_RIGHT;
					}
					else
					{
						state = EntityStates::ST_AIR;
					}
				}
				else
				{
					if (playerInput.A_enabled == true)
					{
						state = EntityStates::ST_RIGHT;
					}
					else
					{
						state = EntityStates::ST_IDLE;
					}
				}
			}
			break;
		case EntityStates::ST_SPECIAL_LEFT:
			if (specialTimer == 0)
			{
				if (jumpAvailable == false)
				{
					if (playerInput.A_enabled)
					{
						state = EntityStates::ST_AIR_LEFT;
					}
					else
					{
						state = EntityStates::ST_AIR_FLIPPED;
					}
				}
				else
				{
					if (playerInput.A_enabled)
					{
						state = EntityStates::ST_LEFT;
					}
					else
					{
						state = EntityStates::ST_IDLE_FLIPPED;
					}
				}
			}
			break;
		case EntityStates::ST_SPECIAL_RIGHT:
			if (specialTimer == 0)
			{
				if (jumpAvailable == false)
				{
					if (playerInput.D_enabled)
					{
						state = EntityStates::ST_AIR_RIGHT;
					}
					else
					{
						state = EntityStates::ST_AIR;
					}
				}
				else
				{
					if (playerInput.A_enabled)
					{
						state = EntityStates::ST_RIGHT;
					}
					else
					{
						state = EntityStates::ST_IDLE;
					}
				}
			}
			break;
		}	
	}
	else
	{
		currentPosition.x += currentVelocity.x;
		currentPosition.y += currentVelocity.y;

		switch (state)
		{
		case EntityStates::ST_IDLE:
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.W_enabled)
			{
				state = EntityStates::ST_UP;
			}
			if (playerInput.S_enabled)
			{
				state = EntityStates::ST_DOWN;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			break;

		case EntityStates::ST_IDLE_FLIPPED:
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.W_enabled)
			{
				state = EntityStates::ST_UP;
			}
			if (playerInput.S_enabled)
			{
				state = EntityStates::ST_DOWN;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_LEFT;
			}

			break;

		case EntityStates::ST_LEFT:
			if (!playerInput.A_enabled)
			{
				state = EntityStates::ST_IDLE_FLIPPED;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.W_enabled)
			{
				state = EntityStates::ST_UP;
			}
			if (playerInput.S_enabled)
			{
				state = EntityStates::ST_DOWN;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_LEFT;
			}
			break;

		case EntityStates::ST_RIGHT:
			if (!playerInput.D_enabled)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.W_enabled)
			{
				state = EntityStates::ST_UP;
			}
			if (playerInput.S_enabled)
			{
				state = EntityStates::ST_DOWN;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			break;

		case EntityStates::ST_UP:
			if (!playerInput.W_enabled)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.S_enabled)
			{
				state = EntityStates::ST_DOWN;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			break;

		case EntityStates::ST_DOWN:
			if (!playerInput.S_enabled)
			{
				state = EntityStates::ST_IDLE;
			}
			if (playerInput.D_enabled)
			{
				state = EntityStates::ST_RIGHT;
			}
			if (playerInput.A_enabled)
			{
				state = EntityStates::ST_LEFT;
			}
			if (playerInput.W_enabled)
			{
				state = EntityStates::ST_UP;
			}
			if (playerInput.K_enabled)
			{
				state = EntityStates::ST_DO_SPECIAL_RIGHT;
			}
			break;
		
		case EntityStates::ST_DO_SPECIAL_LEFT:
			if (specialDistance != 0)
			{
				state = EntityStates::ST_SPECIAL_LEFT;
			}
			else
			{
				if (playerInput.A_enabled == true)
				{
					state = EntityStates::ST_LEFT;
				}
				else
				{
					state = EntityStates::ST_IDLE_FLIPPED;
				}
			}
			break;
		case EntityStates::ST_DO_SPECIAL_RIGHT:
			if (specialDistance != 0)
			{
				state = EntityStates::ST_SPECIAL_RIGHT;
			}
			else
			{
				if (playerInput.A_enabled == true)
				{
					state = EntityStates::ST_RIGHT;
				}
				else
				{
					state = EntityStates::ST_IDLE;
				}
			}
			break;
		case EntityStates::ST_SPECIAL_LEFT:
			if (specialTimer == 0)
			{
				if (playerInput.A_enabled)
				{
					state = EntityStates::ST_LEFT;
				}
				else
				{
					state = EntityStates::ST_IDLE_FLIPPED;
				}	
			}
			break;
		case EntityStates::ST_SPECIAL_RIGHT: //error?
			if (specialTimer == 0)
			{
				if (playerInput.A_enabled)
				{
					state = EntityStates::ST_RIGHT;
				}
				else
				{
					state = EntityStates::ST_IDLE;
				}				
			}
			break;
		
		}
	}
	return true;
}

bool j1EntityPlayer::Update(float dt, bool doLogic)
{
	//only if god_mode is false
	/*current_acceleration.x = gravity.x;
	current_acceleration.y = gravity.y;
	current_velocity.x += current_acceleration.x;
	current_velocity.y += current_acceleration.y;
	current_position.x += current_velocity.x * dt;
	current_position.y += current_velocity.y * dt;*/ //change character measurements from integer to float.

	normalizedMovementSpeed = movementSpeed * dt;
	//MOVEMENT THROUGH STATES
	switch (state)
	{
	case EntityStates::ST_IDLE:
		if (App->allowDebugLog == true)
			LOG("IDLE");

		currentVelocity.x = 0;
		if (godMode)
			currentVelocity.y = 0;

		flipped = false;
		currentAnimation = GetAnimation("idle");
		break;

	case EntityStates::ST_IDLE_FLIPPED:
		if (App->allowDebugLog == true)
			LOG("IDLE");

		currentVelocity.x = 0;
		if (godMode)
			currentVelocity.y = 0;

		flipped = true;
		currentAnimation = GetAnimation("idle");
		break;

  	case EntityStates::ST_LEFT:
		if (App->allowDebugLog == true)
			LOG("MOVING LEFT");

		currentVelocity.x = -normalizedMovementSpeed;

		flipped = true;
		currentAnimation = GetAnimation("run");
		break;

	case EntityStates::ST_RIGHT:
 		if (App->allowDebugLog == true)
			LOG("MOVING RIGHT");

		currentVelocity.x = normalizedMovementSpeed;

		flipped = false;
		currentAnimation = GetAnimation("run");
		break;
	case EntityStates::ST_UP:
		if (App->allowDebugLog == true)
			LOG("MOVING UP");

		currentVelocity.y = -normalizedMovementSpeed;
		break;

	case EntityStates::ST_DOWN:
		if (App->allowDebugLog == true)
			LOG("MOVING DOWN");

		currentVelocity.y = normalizedMovementSpeed;
		break;

	case EntityStates::ST_JUMP:
		if (App->allowDebugLog == true)
			LOG("STRAIGHT JUMP");

		currentVelocity.y -= 45;

		flipped = false;
		jumping = true;
		jumpAvailable = false;
		currentAnimation = GetAnimation("idle");
		break;

	case EntityStates::ST_JUMP_RIGHT:
		if (App->allowDebugLog == true)
			LOG("RIGHT JUMP");

		currentVelocity.y -= 45;

		flipped = false;
		jumping = true;
		jumpAvailable = false;
		currentAnimation = GetAnimation("idle");
		break;

	case EntityStates::ST_JUMP_LEFT:
		if (App->allowDebugLog == true)
			LOG("LEFT JUMP");

		currentVelocity.y -= 45;

		flipped = true;
		jumping = true;
		jumpAvailable = false;
		currentAnimation = GetAnimation("idle");
		break;

	case EntityStates::ST_LEFT_JUMPING:
		if (App->allowDebugLog == true)
			LOG("JUMPING LEFT");

		flipped = true;
		currentAnimation = GetAnimation("jump");
		break;

	case EntityStates::ST_RIGHT_JUMPING:
		if (App->allowDebugLog == true)
			LOG("JUMPING RIGHT");
		flipped = false;
		currentAnimation = GetAnimation("jump");
		break;	

	case EntityStates::ST_AIR_LEFT:
		if (App->allowDebugLog == true)
			LOG("MOVING LEFT ON AIR");

		flipped = true;
		currentVelocity.x = -normalizedMovementSpeed * 0.5;
		currentAnimation = GetAnimation("fall");
		break;
		
	case EntityStates::ST_AIR_RIGHT:
		if (App->allowDebugLog == true)
			LOG("MOVING RIGHT ON AIR");

		flipped = false;
		currentVelocity.x = normalizedMovementSpeed * 0.5;
		currentAnimation = GetAnimation("fall");
		break;

	case EntityStates::ST_AIR_FLIPPED:
		if (App->allowDebugLog == true)
			LOG("FALLING FLIPPED");

		flipped = true;
		currentAnimation = GetAnimation("fall");
		break;

	case EntityStates::ST_AIR:
		if (App->allowDebugLog == true)
			LOG("FALLING");

		currentAnimation = GetAnimation("fall");
		break;

	case EntityStates::ST_DEAD:
		if (App->allowDebugLog == true)
			LOG("DYING");
		currentAnimation = GetAnimation("die");
		break;
	
	case EntityStates::ST_DO_SPECIAL_LEFT:
		if (App->allowDebugLog == true)
			LOG("DO SPECIAL LEFT");

		specialDistance = DoSpecialLeft();
		specialTimer = SPECIAL_TIMER;
		 
		GetAnimation("special")->Reset();
		break;

	case EntityStates::ST_DO_SPECIAL_RIGHT: 
		if (App->allowDebugLog == true)
			LOG("DO SPECIAL RIGHT");

		specialDistance = DoSpecialRight();
		specialTimer = SPECIAL_TIMER;

		GetAnimation("special")->Reset();
		break;

	case EntityStates::ST_SPECIAL_LEFT:
		if (App->allowDebugLog == true)
			LOG("SPECIAL LEFT");

		currentVelocity = { 0,0 };
		currentAcceleration = { 0,0 };

		currentAnimation = GetAnimation("special");
		specialTimer -= dt;
		if (specialTimer <= 0)
		{
			specialTimer = 0;
			currentPosition.x -= specialDistance;
			specialLastFrame = false;
		}
		break;

	case EntityStates::ST_SPECIAL_RIGHT:
		if (App->allowDebugLog == true)
			LOG("SPECIAL RIGHT");
		 
		currentVelocity = { 0,0 };
		currentAcceleration = { 0,0 };

		currentAnimation = GetAnimation("special");
		specialTimer -= dt;
		if (specialTimer <= 0)
		{
			specialTimer = 0;
			currentPosition.x += specialDistance;
			specialLastFrame = false;
		}
		break;
	}	

	if (specialLastFrame == false && state != EntityStates::ST_SPECIAL_RIGHT && state != EntityStates::ST_SPECIAL_LEFT)
	{
		currentAnimation = GetAnimation("special");
		specialLastFrame = true;
	}

	if (currentVelocity.x > MAX_VELOCITY)
		currentVelocity.x = MAX_VELOCITY;
	else if (currentVelocity.x < -MAX_VELOCITY)
		currentVelocity.x = -MAX_VELOCITY;

	if (currentVelocity.y > MAX_VELOCITY)
		currentVelocity.y = MAX_VELOCITY;
	if (currentVelocity.y < -(MAX_VELOCITY*3.5))
		currentVelocity.y = MAX_VELOCITY*3.5;

	if (gravity.x < 0.5)
		gravity.x = 0;

	if (godMode)
	{
		if (entityCollider != nullptr)
		{
			entityCollider->to_delete = true;
			entityCollider = nullptr;	
			currentVelocity = { 0,0 };
			state = EntityStates::ST_IDLE;
		}
	}
	else
	{
		if (entityCollider == nullptr)
		{
			entityCollider = App->coll->AddCollider(entiyRect, COLLIDER_TYPE::PLAYER, this);
		}

		entityCollider->rect.x = currentPosition.x;
		entityCollider->rect.y = currentPosition.y;
		entiyRect.x = currentPosition.x;
		entiyRect.y = currentPosition.y;

	}
	if (currentPosition.x < 0)
	{
		currentPosition.x = startingPosition.x;
		entityCollider->rect.x = startingPosition.x;
	}

	return true;
}

bool j1EntityPlayer::PostUpdate()
{	
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

	iPoint teleport_origin = App->map->WorldToMap(currentPosition.x, currentPosition.y);
	iPoint teleport_destination = App->map->WorldToMap(currentPosition.x - maxSpecialRange, currentPosition.y);
	int tile_width = App->map->mapdata.tile_width;

	for (teleport_destination; teleport_destination.x < teleport_origin.x; teleport_destination.x += 1)
	{
		if (App->map->metadata->Get(teleport_destination.x, teleport_destination.y) == 0)
		{
			iPoint teleport = App->map->MapToWorld(teleport_destination.x, teleport_destination.y);
			ret = currentPosition.x - teleport.x;
			break;
		}
	}
	return ret;
}

int j1EntityPlayer::DoSpecialRight()
{
	int ret = 0;

	iPoint teleport_origin = App->map->WorldToMap(currentPosition.x, currentPosition.y);
	iPoint teleport_destination = App->map->WorldToMap(currentPosition.x + maxSpecialRange, currentPosition.y);

	for (teleport_destination; teleport_destination.x > teleport_origin.x; teleport_destination.x -= 1)
	{
		if (App->map->metadata->Get(teleport_destination.x, teleport_destination.y) == 0)
		{
			iPoint teleport = App->map->MapToWorld(teleport_destination.x, teleport_destination.y);
			ret = teleport.x - currentPosition.x;
			break;
		}
	}
	return ret;
}

void j1EntityPlayer::ResetPlayer(float x, float y)
{
	currentAcceleration = { 0,0 };
	currentVelocity = { 0,0 };
	currentPosition = { x, y };

	playerState = EntityStates::ST_IDLE;
}