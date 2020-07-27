//#include "p2Point.h"
//#include "p2Log.h"
//#include "j1Module.h"
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
//
//
//j1Player::j1Player() : j1Module()
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
//}
//
//j1Player::~j1Player()
//{
//
//}
//
//bool j1Player::Awake(pugi::xml_node& node)
//{
//	bool ret = true;
//
//	pugi::xml_node colliders = node.child("colliders");
//	pugi::xml_node player_stats = node.child("player_stats");
//
//	
//	//MAGIC NUMBERS -- config is set up to be filled with them
//	Size.x = player_stats.child("charachter_width").attribute("value").as_uint();
//	Size.y = player_stats.child("character_height").attribute("value").as_uint();
//	Initial_Pos.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
//	Initial_Pos.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
//	CurrentPosition.x = Initial_Pos.x;
//	CurrentPosition.y = Initial_Pos.y;
//	PlayerVel_w = player_stats.child("PlayerVel_w").attribute("value").as_uint();
//	PlayerVel_r = player_stats.child("PlayerVel_r").attribute("value").as_uint();
//	Gravity = player_stats.child("Gravity").attribute("value").as_float();
//	falling_velocity = player_stats.child("falling_velocity").attribute("value").as_float();
//	Slide_distance = player_stats.child("slide_distance").attribute("value").as_uint();
//	//--- main_Collider creation
//	PlayerRect.w = player_stats.child("character_width").attribute("value").as_uint();
//	PlayerRect.h = player_stats.child("character_height").attribute("value").as_uint();
//	PlayerRect.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
//	PlayerRect.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
//	PlayerCollider = App->coll->AddCollider(PlayerRect, COLLIDER_TYPE::PLAYER);
//
//	//--collider ID's
//	WALL_id = colliders.child("tile_types").child("WALL").attribute("value").as_uint();
//	CLIMB_WALL_id = colliders.child("tile_types").child("CLIMB_WALL").attribute("value").as_uint();
//	BONUS_id = colliders.child("tile_types").child("BONUS").attribute("value").as_uint();
//
//	return ret;
//}
//
//bool  j1Player::Start()
//{
//	LOG("Loading player textures");
//	Graphics = App->tex->Load("Spritesheets/Santa.png");
//
//	PlayerState = ST_IDLE;
//	PlayerRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
//
//	God_Mode = false;
//	return true;
//}
//
//bool j1Player::PreUpdate()
//{
//	bool ret = true;
//	//SHORTCUTS INPUTS
//	PlayerInput.F1_enabled = App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN;
//	PlayerInput.F2_enabled = App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN;
//	PlayerInput.F3_enabled = App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN;
//	PlayerInput.F5_enabled = App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN;
//	PlayerInput.F6_enabled = App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN;
//	PlayerInput.F7_enabled = App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN;
//	PlayerInput.F8_enabled = App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN;
//
//
//	//RESET CURRENT LEVEL
//	if (PlayerInput.F3_enabled)
//	{
//		CurrentPosition.x = StartingPosition.x;
//		CurrentPosition.y = StartingPosition.y;
//		//FALTA CAMERA RESET
//	}
//
//
//	//GODMODE
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
//		if (PlayerState == ST_IDLE)
//		{
//			if (PlayerInput.A_enabled)
//			{
//				LOG("A pressed");
//				PlayerState = ST_LEFT_W;
//			}
//			if (PlayerInput.D_enabled)
//			{
//				PlayerState = ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled)
//			{
//				PlayerState = ST_JUMPING;
//			}
//		}
//		if (PlayerState == ST_LEFT_W)
//		{
//			if (!PlayerInput.A_enabled)
//			{
//				PlayerState = ST_IDLE;
//			}
//			if (PlayerInput.Shift_enabled)
//			{
//				PlayerState = ST_LEFT_R;
//			}
//			if (PlayerInput.D_enabled)
//			{
//				PlayerState = ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				PlayerState = ST_JUMPING;
//			}
//		}
//		if (PlayerState == ST_LEFT_R)
//		{
//			if (!PlayerInput.A_enabled)
//			{
//				PlayerState = ST_IDLE;
//			}
//			if (!PlayerInput.Shift_enabled)
//			{
//				PlayerState = ST_LEFT_W;
//			}
//			if (PlayerInput.D_enabled)
//			{
//				PlayerState = ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				PlayerState = ST_JUMPING;
//			}
//			if (PlayerInput.S_enabled)
//			{
//				PlayerState = ST_SLIDING;
//			}
//		}
//		if (PlayerState == ST_RIGHT_W)
//		{
//			if (!PlayerInput.D_enabled)
//			{
//				PlayerState = ST_IDLE;
//			}
//			if (PlayerInput.Shift_enabled)
//			{
//				PlayerState = ST_RIGHT_R;
//			}
//			if (PlayerInput.A_enabled)
//			{
//				PlayerState = ST_LEFT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				PlayerState = ST_JUMPING;
//			}
//		}
//		if (PlayerState == ST_RIGHT_R)
//		{
//			if (!PlayerInput.D_enabled)
//			{
//				PlayerState = ST_IDLE;
//			}
//			if (!PlayerInput.Shift_enabled)
//			{
//				PlayerState = ST_RIGHT_W;
//			}
//			if (PlayerInput.A_enabled)
//			{
//				PlayerState = ST_RIGHT_W;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				PlayerState = ST_JUMPING;
//			}
//			if (PlayerInput.S_enabled)
//			{
//				PlayerState = ST_SLIDING;
//			}
//		}
//		if (PlayerState == ST_JUMPING)
//		{
//			if (PlayerInput.W_enabled)
//			{
//				PlayerState = ST_CLIMBING;
//			}
//		}
//		if (PlayerState == ST_SLIDING)
//		{
//			if (!PlayerInput.S_enabled)
//			{
//				PlayerState = ST_IDLE;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				PlayerState = ST_JUMPING;
//			}
//		}
//		if (PlayerState == ST_CLIMBING)
//		{
//			if (!PlayerInput.W_enabled)
//			{
//				PlayerState = ST_IDLE;
//			}
//			if (PlayerInput.Space_enabled && jump_available)
//			{
//				PlayerState = ST_JUMPING;
//			}
//		}
//		//NOT NEEDED IN THIS VERSION
//		if(PlayerState == ST_DYING){}
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
//
//bool j1Player::Update(float dt)
//{
//	bool ret = true;
//	ActualizedPosition = CurrentPosition;
//
//	//MOVEMENT THROUGH STATES
//	switch (PlayerState)
//	{
//	case ST_IDLE:
//		LOG("IDLE");
//		current_animation = &idle; 
//		break;
//
//	case ST_LEFT_W:
//		LOG("WALKING LEFT");
//		flipped = true;
//		CurrentPosition.x -= PlayerVel_w;
//		current_animation = &walking;
//		break;
//
//	case ST_LEFT_R:
//		LOG("RUNNING LEFT");
//		flipped = true;
//		CurrentPosition.x -= PlayerVel_r;
//		current_animation = &running;
//		break;
//
//	case ST_RIGHT_W:
//		LOG("WALKING RIGHT");
//		flipped = false;
//		CurrentPosition.x += PlayerVel_w;
//		current_animation = &walking;
//		break;
//
//	case ST_RIGHT_R:
//		LOG("RUNNING RIGHT");
//		flipped = false;
//		CurrentPosition.x += PlayerVel_r;   
//		current_animation = &running;
//		break;
//
//	case ST_JUMPING:
//		LOG("JUMPING");
//
//		current_animation = &jumping;
//		//FALTA
//		break;
//
//	case ST_SLIDING:
//		LOG("SLIDING");
//		current_animation = &sliding;
//		break;
//
//	case ST_CLIMBING:
//		LOG("CLIMBING");
//		current_animation = &climbing;
//		break;
//
//	case ST_DYING:
//		LOG("DYING");
//		current_animation = &dying;
//		break;
//	}
//
//	//PLAYER
//	PlayerRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
//	PlayerCollider->SetPos(CurrentPosition.x, CurrentPosition.y);
//
//
//	//ANIMATIONS
//	rotating_animation = current_animation->GetCurrentFrame();
//	App->render->Blit(Graphics, CurrentPosition.x, CurrentPosition.y, &rotating_animation, flipped);
//
//
//	return true;
//}
//
//
//bool j1Player::PostUpdate()
//{
//
//
//	return true;
//}
//
//
//bool j1Player::CleanUp()
//{
//
//	LOG("Unloading Player");
//
//	App->tex->UnLoad(Graphics);
//
//	return true;
//}
//
//void j1Player::grounded()
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
//void j1Player::jump()
//{
//	if (mid_air)
//	{
//		falling_velocity -= Gravity;
//
//		if (PlayerInput.A_enabled)
//		{
//			CurrentPosition.x -= PlayerVel_w;
//		}
//		else if (PlayerInput.A_enabled && PlayerInput.Shift_enabled)
//		{
//			CurrentPosition.x -= PlayerVel_r;
//		}
//		else if (PlayerInput.D_enabled)
//		{
//			CurrentPosition.x += PlayerVel_w;
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
//			PlayerState = ST_IDLE;
//		}
//		else if (!in_land)
//		{
//			CurrentPosition.y += falling_velocity;
//		}
//	}
//}
//
//void j1Player::OnCollision(Collider* c1, Collider* c2)
//{
//	/*
//	En vista de que esta función ha sido un fracaso, voy a seguir los siguientes pasos para mejorarla:
//
//	1. Crear una función en el modulo de colidiones para cada lado de un collider, por ejemplo:
//		bool canCollide_right(uint tile_gid)
//		{
//		bool ret = false;
//			if (tiene una tile en la derecha en la capa de colliders &&
//			esta es un collider de tipo WALL o CLIMB_WALL)
//			{
//				ret = true;
//			}
//			return ret;
//		}
//	*/
//	if (c1->type == PLAYER)
//	{
//		iPoint wall_position = App->map->WorldToMap(c2->rect.x, c2->rect.y);
//		uint tileid = App->map->Metadata->GetLayerPositon(wall_position.x, wall_position.y);
//
//		if (c1->rect.y < (c2->rect.y + c2->rect.h) && c1->rect.y < c2->rect.y
//			&& (c1->rect.y + c1->rect.h) >= c2->rect.y && (c1->rect.y + c1->rect.h) < (c2->rect.y + c2->rect.h)) //Collision from top
//		{
//			if (App->coll->canCollide_top(tileid))
//			{
//				CurrentPosition.y = c2->rect.y - c1->rect.h;
//			}
//		}
//
//		else if (c1->rect.y > c2->rect.y && c1->rect.y < (c2->rect.y + c2->rect.h) &&
//			(c1->rect.y + c1->rect.h)>(c2->rect.y + c2->rect.h) && (c1->rect.y + c1->rect.h) > c2->rect.y)//collision from bottom
//		{
//			if (App->coll->canCollide_bottom(tileid))
//			{
//				CurrentPosition.y = c2->rect.y + c2->rect.h;
//			}
//		}
//
//		else if (c1->rect.x > c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) && 
//			(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) > (c2->rect.x + c2->rect.w)) //collision from right side
//		{
//			if (App->coll->canCollide_right(tileid))
//			{
//				CurrentPosition.x = c2->rect.x + c2->rect.w;
//			}
//		}
//
//		else if (c1->rect.x < c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) &&
//			(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) < (c2->rect.x + c2->rect.w))//collision from left side
//		{
//			if (App->coll->canCollide_left(tileid))
//			{
//				CurrentPosition.x = c2->rect.x - c1->rect.w;
//			}
//		}
//	}
//
//	if (c2->type == PLAYER)
//	{
//		iPoint wall_position = App->map->WorldToMap(c2->rect.x, c2->rect.y);
//		uint tileid = App->map->Metadata->GetLayerPositon(wall_position.x, wall_position.y);
//
//		if (c2->rect.y < (c1->rect.y + c1->rect.h) && c2->rect.y < c1->rect.y &&
//			(c2->rect.y + c2->rect.h) >= c1->rect.y && (c2->rect.y + c2->rect.h) < (c1->rect.y + c1->rect.h)) //Collision from top
//		{
//			if (App->coll->canCollide_top(tileid))
//			{
//				CurrentPosition.y = c1->rect.y - c2->rect.h;
//			}
//		}
//
//		else if (c2->rect.y > c1->rect.y && c2->rect.y < (c1->rect.y + c1->rect.h) &&
//			(c2->rect.y + c2->rect.h)>(c1->rect.y + c1->rect.h) && (c2->rect.y + c2->rect.h) > c1->rect.y)//collison from bottom
//		{
//			if (App->coll->canCollide_bottom(tileid))
//			{
//				CurrentPosition.y = c1->rect.y + c1->rect.h;
//			}
//		}
//
//		else if (c2->rect.x > c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
//			(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) > (c1->rect.x + c1->rect.w)) //collision from right side
//		{
//			if (App->coll->canCollide_right(tileid))
//			{
//				CurrentPosition.x = c1->rect.x + c1->rect.w;
//			}
//		}
//
//		else if (c2->rect.x < c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
//			(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) < (c1->rect.x + c1->rect.w))//collision from left side
//		{
//			if (App->coll->canCollide_left(tileid))
//			{
//				CurrentPosition.x = c1->rect.x - c2->rect.w;
//			}
//		}
//	}
//}
//
