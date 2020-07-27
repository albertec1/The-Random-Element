//#ifndef __j1ENTITYPLAYER_CPP__
//#define __j1ENTITYPLAYER_CPP__
//
//#include "j1EntityMovable_Ground.h"
//#include "j1EntityMovable.h"
//#include "p2Point.h"
//#include "p2Log.h"
//#include "j1App.h"
//#include "j1Textures.h"
//#include "j1Render.h"
//#include "j1Input.h"
//#include "Animation.h"
//#include "j1Player.h"
//#include "j1Audio.h"
//#include "j1Collision.h"
//#include "j1Map.h"
//#include "j1Window.h"
//#include "j1EntityPlayer.h"
//
//j1EntityPlayer::j1EntityPlayer(iPoint pos, ENTITY_TYPE type) : j1EntityMovable_ground(pos, type)
//{
//	name.create("player");
//
//	//IDLE
//	idle.PushBack({ 5,1,48,75 });
//	idle.PushBack({ 135,1,48,75 });
//	idle.PushBack({ 266,1,48,75 });
//	idle.PushBack({ 395,1,48,75 });
//	idle.PushBack({ 525,1,48,75 });
//	idle.PushBack({ 655,1,48,75 });
//	idle.PushBack({ 785,1,48,75 });
//	idle.PushBack({ 915,1,48,75 });
//	idle.PushBack({ 1045,1,48,75 });
//	idle.PushBack({ 1175,1,48,75 });
//
//	idle.PushBack({ 6,90,48,75 });
//	idle.PushBack({ 136,90,48,75 });
//	idle.PushBack({ 266,90,48,75 });
//	/*idle.PushBack({ 395,90,48,75 });
//	idle.PushBack({ 527,90,48,75 });
//	idle.PushBack({ 659,90,48,75 });*/
//
//	idle.speed = 0.25f;
//
//	//WALKING
//
//	walking.PushBack({ 5,219,48,75 });
//	walking.PushBack({ 136,219,48,75 });
//	walking.PushBack({ 268,219,48,75 });
//	walking.PushBack({ 397,219,48,75 });
//	walking.PushBack({ 525,219,48,75 });
//	walking.PushBack({ 656,219,48,75 });
//	walking.PushBack({ 785,219,48,75 });
//	walking.PushBack({ 916,219,48,75 });
//	walking.PushBack({ 1047,219,48,75 });
//	walking.PushBack({ 1175,219,48,75 });
//
//	walking.PushBack({ 6,308,48,75 });
//	walking.PushBack({ 137,308,48,75 });
//	walking.PushBack({ 266,308,48,75 });
//
//	walking.speed = 0.3f;
//
//	//RUNNING
//	running.PushBack({ 3,457,48,75 });
//	running.PushBack({ 133,457,48,75 });
//	running.PushBack({ 263,457,48,75 });
//	running.PushBack({ 394,457,48,75 });
//	running.PushBack({ 523,457,48,75 });
//	running.PushBack({ 654,457,48,75 });
//	running.PushBack({ 781,457,48,75 });
//	running.PushBack({ 908,457,48,75 });
//	running.PushBack({ 1041,457,48,75 });
//	running.PushBack({ 1174,457,48,75 });
//
//	running.PushBack({ 3,547,48,75 });
//
//	running.speed = 0.1f;
//
//	//JUMPING
//	jumping.PushBack({ 23,663,48,75 });
//	jumping.PushBack({ 157,663,48,75 });
//	jumping.PushBack({ 287,663,48,75 });
//	jumping.PushBack({ 412,663,48,75 });
//	jumping.PushBack({ 543,663,48,75 });
//	jumping.PushBack({ 659,663,48,75 });
//	jumping.PushBack({ 788,663,48,75 });
//	jumping.PushBack({ 915,663,48,75 });
//	jumping.PushBack({ 1047,663,48,75 });
//	jumping.PushBack({ 1177,663,75 });
//
//	jumping.PushBack({ 6,749,48,75 });
//	jumping.PushBack({ 136,749,48,75 });
//	jumping.PushBack({ 275,749,48,75 });
//	jumping.PushBack({ 411,749,48,75 });
//	jumping.PushBack({ 542,749,48,75 });
//	jumping.PushBack({ 674,749,48,75 });
//
//	jumping.speed = 0.1f;
//
//	//SLIDING
//	sliding.PushBack({ 3,881,76,75 });
//	sliding.PushBack({ 133,881,76,75 });
//	sliding.PushBack({ 264,881,76,75 });
//	sliding.PushBack({ 422,881,76,75 });
//	sliding.PushBack({ 523,881,76,75 });
//	sliding.PushBack({ 651,881,76,75 });
//	sliding.PushBack({ 781,881,76,75 });
//	sliding.PushBack({ 913,881,76,75 });
//	sliding.PushBack({ 1043,881,76,75 });
//	sliding.PushBack({ 1174,881,76,75 });
//
//	sliding.PushBack({ 3,971,76,75 });
//
//	sliding.speed = 0.1f;
//
//	//DYING
//	dying.PushBack({ 6,1086,48,75 });
//	dying.PushBack({ 66,1086,48,75 });
//	dying.PushBack({ 122,1086,48,75 });
//	dying.PushBack({ 175,1086,48,75 });
//	dying.PushBack({ 258,1086,48,75 });
//	dying.PushBack({ 342,1086,48,75 });
//	dying.PushBack({ 426,1086,48,75 });
//	dying.PushBack({ 594,1086,48,75 });
//	dying.PushBack({ 680,1086,83,75 });
//	dying.PushBack({ 760,1086,83,75 });
//
//	dying.PushBack({ 6,1173,83,75 });
//	dying.PushBack({ 66,1173,83,75 });
//	dying.PushBack({ 122,1173,83,75 });
//	dying.PushBack({ 175,1173,83,75 });
//	dying.PushBack({ 225,1173,83,75 });
//	dying.PushBack({ 276,1173,83,75 });
//	dying.PushBack({ 276,1173,83,75 });
//
//	dying.speed = 0.1f;
//
//	God_Mode = false;
//} 
//
//bool j1EntityPlayer::Awake(pugi::xml_node& node)
//{
//	//Player loaded from xml (LOS NOMBRES DE LAS VARIABLES YA ESTÁN BIEN PUESTOS)
//	pugi::xml_node colliders = node.child("player").child("colliders");
//	pugi::xml_node player_stats = node.child("player").child("player_stats");
//
//	Size.x = player_stats.child("charachter_width").attribute("value").as_uint();
//	Size.y = player_stats.child("character_height").attribute("value").as_uint();
//	StartingPosition.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
//	StartingPosition.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
//	CurrentPosition.x = StartingPosition.x;
//	CurrentPosition.y = StartingPosition.y;
//	velocity = player_stats.child("PlayerVel_w").attribute("value").as_uint();
//	PlayerVel_r = player_stats.child("PlayerVel_r").attribute("value").as_uint();
//	Gravity = player_stats.child("Gravity").attribute("value").as_float();
//	falling_velocity = player_stats.child("falling_velocity").attribute("value").as_float();
//	Slide_distance = player_stats.child("slide_distance").attribute("value").as_uint();
//
//	//--- main_Collider creation
//	EntityRect.w = player_stats.child("character_width").attribute("value").as_uint();
//	EntityRect.h = player_stats.child("character_height").attribute("value").as_uint();
//	EntityRect.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
//	EntityRect.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
//	EntityCollider = App->coll->AddCollider(EntityRect, COLLIDER_TYPE::PLAYER);
//
//	//--collider ID's
//	WALL_id = colliders.child("tile_types").child("WALL").attribute("value").as_uint();
//	CLIMB_WALL_id = colliders.child("tile_types").child("CLIMB_WALL").attribute("value").as_uint();
//	BONUS_id = colliders.child("tile_types").child("BONUS").attribute("value").as_uint();
//
//	EntityCollider->callback = this;
//	return true;
//}
//
//bool j1EntityPlayer::Start()
//{
//	LOG("Loading player textures");
//	EntityTexture = App->tex->Load("Spritesheets/Santa.png");
//
//	EntityState = Current_State::ST_IDLE;
//	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
//
//	return true;
//}
//
//bool j1EntityPlayer::PreUpdate()
//{
//	bool ret = true;
//	//SHORTCUTS INPUTS--- 
//	PlayerInput.F1_enabled = App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN;
//	PlayerInput.F2_enabled = App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN;
//	PlayerInput.F3_enabled = App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN;
//	PlayerInput.F5_enabled = App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN;
//	PlayerInput.F6_enabled = App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN;
//	PlayerInput.F7_enabled = App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN;
//	PlayerInput.F8_enabled = App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN;
//
//	//RESET CURRENT LEVEL---
//	if (PlayerInput.F3_enabled)
//	{
//		CurrentPosition.x = StartingPosition.x;
//		CurrentPosition.y = StartingPosition.y;
//		//FALTA CAMERA RESET
//	}
//
//	//GODMODE---
//	if (God_Mode == false && PlayerInput.F8_enabled)
//	{
//		LOG("GOD MODE ACTIVATED");
//		God_Mode = true;
//	}
//	else if (God_Mode == true && PlayerInput.F8_enabled)
//	{
//		LOG("GOD MODE DEACTIVATED");
//		God_Mode = false;
//	}
//	if (God_Mode == false)
//	{
//		PlayerInput.W_enabled = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
//		PlayerInput.A_enabled = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
//		PlayerInput.S_enabled = App->input->keyboard[SDL_SCANCODE_S] == KEY_DOWN;
//		PlayerInput.D_enabled = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
//		PlayerInput.Shift_enabled = App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_REPEAT;
//		PlayerInput.Space_enabled = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_REPEAT;
//	}
//	else
//	{
//		PlayerInput.W_GOD_enabled = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
//		PlayerInput.A_GOD_enabled = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
//		PlayerInput.S_GOD_enabled = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
//		PlayerInput.D_GOD_enabled = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
//	}
//
//	//PLAYER STATES
//	if (God_Mode == false)
//	{
//		CurrentPosition.y += Gravity;
//
//		if (EntityState == Current_State::ST_IDLE)
//		{
//			if (PlayerInput.A_enabled)
//			{
//				LOG("A pressed");
//				EntityState = Current_State::ST_LEFT_W;
//			}
//			if (PlayerInput.D_enabled)
//			{
//				EntityState = Current_State::ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled)
//			{
//				EntityState = Current_State::ST_JUMPING;
//			}
//		}
//		if (EntityState == Current_State::ST_LEFT_W)
//		{
//			if (!PlayerInput.A_enabled)
//			{
//				EntityState = Current_State::ST_IDLE;
//			}
//			if (PlayerInput.Shift_enabled)
//			{
//				EntityState = Current_State::ST_LEFT_R;
//			}
//			if (PlayerInput.D_enabled)
//			{
//				EntityState = Current_State::ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				EntityState = Current_State::ST_JUMPING;
//			}
//		}
//		if (EntityState == Current_State::ST_LEFT_R)
//		{
//			if (!PlayerInput.A_enabled)
//			{
//				EntityState = Current_State::ST_IDLE;
//			}
//			if (!PlayerInput.Shift_enabled)
//			{
//				EntityState = Current_State::ST_LEFT_W;
//			}
//			if (PlayerInput.D_enabled)
//			{
//				EntityState = Current_State::ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				EntityState = Current_State::ST_JUMPING;
//			}
//			if (PlayerInput.S_enabled)
//			{
//				EntityState = Current_State::ST_SLIDING;
//			}
//		}
//		if (EntityState == Current_State::ST_RIGHT_W)
//		{
//			if (!PlayerInput.D_enabled)
//			{
//				EntityState = Current_State::ST_IDLE;
//			}
//			if (PlayerInput.Shift_enabled)
//			{
//				EntityState = Current_State::ST_RIGHT_R;
//			}
//			if (PlayerInput.A_enabled)
//			{
//				EntityState = Current_State::ST_LEFT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				EntityState = Current_State::ST_JUMPING;
//			}
//		}
//		if (EntityState == Current_State::ST_RIGHT_R)
//		{
//			if (!PlayerInput.D_enabled)
//			{
//				EntityState = Current_State::ST_IDLE;
//			}
//			if (!PlayerInput.Shift_enabled)
//			{
//				EntityState = Current_State::ST_RIGHT_W;
//			}
//			if (PlayerInput.A_enabled)
//			{
//				EntityState = Current_State::ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				EntityState = Current_State::ST_JUMPING;
//			}
//			if (PlayerInput.S_enabled)
//			{
//				EntityState = Current_State::ST_SLIDING;
//			}
//		}
//		if (EntityState == Current_State::ST_JUMPING)
//		{
//			if (PlayerInput.W_enabled)
//			{
//				EntityState = Current_State::ST_CLIMBING;
//			}
//		}
//		if (EntityState == Current_State::ST_SLIDING)
//		{
//			if (!PlayerInput.S_enabled)
//			{
//				EntityState = Current_State::ST_IDLE;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				EntityState = Current_State::ST_JUMPING;
//			}
//		}
//		if (EntityState == Current_State::ST_CLIMBING)
//		{
//			if (!PlayerInput.W_enabled)
//			{
//				EntityState = Current_State::ST_IDLE;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				EntityState = Current_State::ST_JUMPING;
//			}
//		}
//		//NOT NEEDED IN THIS VERSION
//		if (EntityState == Current_State::ST_DYING) {}
//	}
//	//GODMODE MOVEMENT
//	else if (God_Mode == true)
//	{
//		if (PlayerInput.W_GOD_enabled)
//		{
//			CurrentPosition.y -= PlayerVel_r;
//		}
//		if (PlayerInput.A_GOD_enabled)
//		{
//			CurrentPosition.x -= PlayerVel_r;
//
//		}
//		if (PlayerInput.S_GOD_enabled)
//		{
//			CurrentPosition.y += PlayerVel_r;
//
//		}
//		if (PlayerInput.D_GOD_enabled)
//		{
//			CurrentPosition.x += PlayerVel_r;
//		}
//	}
//
//	return ret;
//}
//
//bool j1EntityPlayer::Update(float dt, bool doLogic)
//{
//	bool ret = true;
//	
//	//MOVEMENT THROUGH STATES
//	switch (EntityState)
//	{
//	case Current_State::ST_IDLE:
//		LOG("IDLE");
//		current_animation = &idle;
//		break;
//
//	case Current_State::ST_LEFT_W:
//		LOG("WALKING LEFT");
//		flipped = true;
//		CurrentPosition.x -= velocity;
//		current_animation = &walking;
//		break;
//
//	case Current_State::ST_LEFT_R:
//		LOG("RUNNING LEFT");
//		flipped = true;
//		CurrentPosition.x -= PlayerVel_r;
//		current_animation = &running;
//		break;
//
//	case Current_State::ST_RIGHT_W:
//		LOG("WALKING RIGHT");
//		flipped = false;
//		CurrentPosition.x += velocity;
//		current_animation = &walking;
//		break;
//
//	case Current_State::ST_RIGHT_R:
//		LOG("RUNNING RIGHT");
//		flipped = false;
//		CurrentPosition.x += PlayerVel_r;
//		current_animation = &running;
//		break;
//
//	case Current_State::ST_JUMPING:
//		LOG("JUMPING");
//
//		current_animation = &jumping;
//		//FALTA
//		break;
//
//	case Current_State::ST_SLIDING:
//		LOG("SLIDING");
//		current_animation = &sliding;
//		break;
//
//	case Current_State::ST_CLIMBING:
//		LOG("CLIMBING");
//		current_animation = &climbing;
//		break;
//
//	case Current_State::ST_DYING:
//		LOG("DYING");
//		current_animation = &dying;
//		break;
//	}
//
//	//PLAYER
//	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
//	EntityCollider->SetPos(CurrentPosition.x, CurrentPosition.y);
//
//	return true;
//}
//
//bool j1EntityPlayer::Draw()
//{
//	bool ret = true;
//	//ANIMATIONS
//	rotating_animation = current_animation->GetCurrentFrame();
//	if ((ret = App->render->Blit(EntityTexture, CurrentPosition.x, CurrentPosition.y, &rotating_animation, flipped) == 0))
//	{
//		LOG("Blit error in Player");
//	}
//
//	return ret;
//}
//
//void j1EntityPlayer::grounded()
//{
//	jump_available = false;
//	if (in_land == true)
//	{
//		jump_available = true;
//	}
//	else
//	{
//		jump_available = false;
//	}
//}
//
//void j1EntityPlayer::jump()
//{
//	if (mid_air)
//	{
//		falling_velocity -= Gravity;
//
//		if (PlayerInput.A_enabled)
//		{
//			CurrentPosition.x -= velocity;
//		}
//		else if (PlayerInput.A_enabled && PlayerInput.Shift_enabled)
//		{
//			CurrentPosition.x -= PlayerVel_r;
//		}
//		else if (PlayerInput.D_enabled)
//		{
//			CurrentPosition.x += velocity;
//		}
//		else if (PlayerInput.D_enabled && PlayerInput.Shift_enabled)
//		{
//			CurrentPosition.x -= PlayerVel_r;
//		}
//
//		CurrentPosition.y -= Gravity;
//
//	}
//	else if (!mid_air)
//	{
//		falling_velocity += Gravity;
//		if (in_land)
//		{
//			jump_ended = true;
//			EntityState = Current_State::ST_IDLE;
//		}
//		else if (!in_land)
//		{
//			CurrentPosition.y += falling_velocity;
//		}
//	}
//}
//
//void j1EntityPlayer::OnCollision(Collider* c1, Collider* c2)
//{
//
//	return;
//}
//#endif __j1ENTITYPLAYER_CPP__
//
