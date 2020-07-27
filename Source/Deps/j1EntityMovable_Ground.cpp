//#ifndef __j1ENTITYMOVABLE_GROUND_CPP__
//#define __j1ENTITYMOVABLE_GROUND_CPP__
//
//#define cBotMaxPositionError 20
//#define cMaxStuckFrames  20
//
//#include "j1Entity.h"
//#include "J1EntityMovable.h"
//#include "j1EntityMovable_Ground.h"
//#include "j1EntityManager.h"
//#include "p2Point.h"
//#include "p2Log.h"
//#include "j1Module.h"
//#include "Animation.h"
//#include "j1Textures.h"
//#include "j1Collision.h"
//#include "j1Render.h"
//#include "j1Map.h"
//#include "j1Input.h"
//#include "j1Pathfinding.h"
//
//j1EntityMovable_ground::j1EntityMovable_ground(iPoint pos, ENTITY_TYPE type) : j1EntityMovable(pos, type)
//{
//	//create name
//	//TODO: PUSHBACKS
//
//	LOG("Loading EntityMovable_ground textures");
//	//Graphics = App->tex->Load("Spritesheets/Enemies/Bugfly/Idle_Flying.png");
//
//	EntityState = Current_State::ST_IDLE;
//	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
//}
//
//bool j1EntityMovable_ground::Awake(pugi::xml_node& node)
//{
//	//set inputs to false---
//	mInputs[(int)mKeyInput::GoRight] = false;
//	mInputs[(int)mKeyInput::GoLeft] = false;
//	mInputs[(int)mKeyInput::Jump] = false;
//	mInputs[(int)mKeyInput::GoDown] = false;
//	mInputs[(int)mKeyInput::Dying] = false;
//
//	//Player loaded from xml (LOS NOMBRES DE LAS VARIABLES YA ESTÁN BIEN PUESTOS)
//	pugi::xml_node colliders = node.child("player").child("colliders");
//	pugi::xml_node Entity_stats = node.child("enemy").child("enemy_stats");
//	pugi::xml_node player_stats = node.child("player").child("player_stats");
//
//	Size.x = Entity_stats.child("charachter_width").attribute("value").as_uint();
//	Size.y = Entity_stats.child("character_height").attribute("value").as_uint();
//	StartingPosition.x = Entity_stats.child("InitialPos_x").attribute("value").as_uint();
//	StartingPosition.y = Entity_stats.child("InitialPos_y").attribute("value").as_uint();
//	CurrentPosition.x = StartingPosition.x;
//	CurrentPosition.y = StartingPosition.y;
//	velocity = Entity_stats.child("PlayerVel_w").attribute("value").as_uint();
//	Gravity = Entity_stats.child("Gravity").attribute("value").as_float();
//	falling_velocity = Entity_stats.child("falling_velocity").attribute("value").as_float();
//
//	//--- main_Collider creation
//	EntityRect.w = player_stats.child("character_width").attribute("value").as_uint();
//	EntityRect.h = player_stats.child("character_height").attribute("value").as_uint();
//	EntityRect.x = player_stats.child("InitialPos_x").attribute("value").as_uint();
//	EntityRect.y = player_stats.child("InitialPos_y").attribute("value").as_uint();
//	EntityCollider = App->coll->AddCollider(EntityRect, COLLIDER_TYPE::ENEMY);
//
//	EntityCollider->callback = this;
//	return true;
//}
//
//bool j1EntityMovable_ground::PreUpdate()
//{
//	CurrentPosition.y += Gravity;
//	pathCount = pathList.count();
//	//------
//	static iPoint origin;
//	static bool origin_selected = false;
//
//	int x, y;
//	App->input->GetMousePosition(x, y);
//	iPoint p = App->render->ScreenToWorld(x, y);
//	p = App->map->WorldToMap(p.x, p.y);
//	pathPosition = App->map->WorldToMap((CurrentPosition.x + EntityCollider->rect.w * 0.5f),
//		(CurrentPosition.y + EntityCollider->rect.h * 0.6f));
//
//
//	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
//	{
//		if (origin_selected == true)
//		{
//			while (!App->map->isGround(p.x, p.y))
//			{
//				p.y++;	//Here I force the destination to be at the ground
//			}
//			App->pathfinding->CreatePath(pathPosition, p);
//			App->pathfinding->CopyPathList(&pathList);
//			//if path is not null copy the path into another array.
//			if (pathList.count() > 0)
//			{
//				mCurrentNodeId = 1;
//				ChangeState(BotState::MoveTo);
//			}
//			origin_selected = false;
//		}
//		else
//		{
//			origin = pathPosition;
//			origin_selected = true;
//		}
//	}
//
//	if (App->map->isGround(pathPosition.x, pathPosition.y))
//		mOnGround = true;
//	else
//		mOnGround = false;
//
//	
//	return true;
//
//}
//
//bool j1EntityMovable_ground::Update(float dt, bool doLogic)
//{
//	switch (mCurrentBotState)
//	{
//	case BotState::None:
//		break; //no need to do anything
//
//	case BotState::MoveTo:
//
//		if (&pathList[mCurrentNodeId - 1] != nullptr)
//		{
//			prevDest = pathList[mCurrentNodeId - 1];
//		}
//		else
//		{
//			prevDest.x = 0; prevDest.y = 0;
//		}
//
//		currentDest = pathList[mCurrentNodeId];
//		nextDest = pathList[mCurrentNodeId + 1];
//
//		GetContext(prevDest, currentDest, nextDest, destOnGround, reachedX, reachedY);
//
//		if (!mOnGround || (reachedX && !destOnGround) || (mOnGround && destOnGround))
//		{
//			mInputs[(int)mKeyInput::Jump] = true;
//		}
//
//		if (reachedX && reachedY)
//		{
//			mCurrentNodeId++;
//
//			if (mCurrentNodeId >= pathList.count())
//			{
//				mCurrentNodeId = -1;
//				ChangeState(BotState::None);
//			}
//
//		}
//		else if (!reachedX || !reachedY && App->map->isGround(nextDest.x, nextDest.y))
//		{	
//			currentDest = App->map->MapToWorld(currentDest.x, currentDest.y);
//			pathPosition = App->map->MapToWorld(pathPosition.x, pathPosition.y);
//			if (currentDest.x - pathPosition.x > cBotMaxPositionError)
//				mInputs[(int)mKeyInput::GoRight] = true;
//			else if (pathPosition.x - currentDest.x > cBotMaxPositionError)
//				mInputs[(int)mKeyInput::GoLeft] = true;
//		}
//
//
//		if (pathPosition == currentDest)
//		{
//			++mStuckFrames;
//			if (mStuckFrames > cMaxStuckFrames)
//				(pathList[pathCount - 1]);
//		}
//		else
//			mStuckFrames = 0;
//		break;
//
//	}
//	CharacterUpdate();
//	return true;
//}
//
//void j1EntityMovable_ground::OnCollision(Collider* c1, Collider* c2)
//{
//	// TODO: Launch dead animation if hit from top
//	// TODO: Go a few tiles backwards after hitting the player before trying to attack again 
//	LOG("collision");
//}
//
//void j1EntityMovable_ground::CharacterUpdate()
//{
//	bool ret = true;
//
//	//MOVEMENT THROUGH STATES
//
//	if (mCurrentBotState == BotState::None)
//	{
//		LOG("IDLE");
//		current_animation = &idle;
//	}
//
//	if (mInputs[(int)mKeyInput::GoLeft] == true)
//	{
//		LOG("WALKING LEFT");
//		flipped = true;
//		CurrentPosition.x -= velocity;
//		current_animation = &walking;
//	}
//
//	if (mInputs[(int)mKeyInput::GoRight] == true)
//	{
//		LOG("WALKING RIGHT");
//		flipped = false;
//		CurrentPosition.x += velocity;
//		current_animation = &walking;
//	}
//
//	if (mInputs[(int)mKeyInput::Jump] == true)
//	{
//		LOG("JUMPING");
//		current_animation = &jumping;
//		//FALTA
//	}
//
//	if (mInputs[(int)mKeyInput::Dying] == true)
//	{
//		LOG("DYING");
//		current_animation = &dying;
//	}
//
//	//PLAYER
//	EntityRect = { CurrentPosition.x, CurrentPosition.y, Size.x, Size.y };
//	EntityCollider->SetPos(CurrentPosition.x, CurrentPosition.y);
//}
//
//void j1EntityMovable_ground::ChangeState(BotState newState)
//{
//	mCurrentBotState = newState;
//}
//
//void j1EntityMovable_ground::GetContext(iPoint prevDest, iPoint currentDest, iPoint nextDest, bool destOnGround, bool reachedX, bool reachedY)
//{
//	if (App->map->isGround(pathPosition.x, pathPosition.y))
//		mOnGround = true;
//	else
//		mOnGround = false;
//	//set inputs to false---
//	mInputs[(int)mKeyInput::GoRight] = false;
//	mInputs[(int)mKeyInput::GoLeft] = false;
//	mInputs[(int)mKeyInput::Jump] = false;
//	mInputs[(int)mKeyInput::GoDown] = false;
//	mInputs[(int)mKeyInput::Dying] = false;
//
//	//calculate the x and y coincidence of the current position with the next destination coordinates---
//	prevDest = App->map->MapToWorld(prevDest.x, prevDest.y);
//	currentDest = App->map->MapToWorld(currentDest.x, currentDest.y);
//
//	if (pathCount > mCurrentNodeId + 1)
//	{
//		nextDest = App->map->MapToWorld(nextDest.x, nextDest.y);
//	}
//	reachedX = ReachedNodeOnXAxis(pathPosition, prevDest, currentDest);
//	
//	reachedY = ReachedNodeOnYAxis(pathPosition, prevDest, currentDest);
//
//	if (destOnGround && !mOnGround)
//	{
//		reachedY = false;
//	}
//
//}
////int j1EntityMovable_ground::GetJumpFramesForNode(int prevNodeId)
////{
////	if (pathList[mCurrentNodeId].y - pathList[prevNodeId].y > 0 && mOnGround)
////	{
////		int jumpHeight = 1;
////
////		for (int i = mCurrentNodeId; i < pathList.count; ++i)
////		{
////			if (pathList[i].y - pathList[prevNodeId].y >= jumpHeight && App->map->isGround(pathList[i].x, pathList[i].y - 1))
////		}	
////	}
////}
//bool j1EntityMovable_ground::ReachedNodeOnXAxis(iPoint pathPosition, iPoint prevDest, iPoint currentDest)
//{
//	uint absX = 0;
//	if ((pathPosition.x - currentDest.x) < 0)
//		absX = (pathPosition.x - currentDest.x) * (-1);
//	else
//		absX = (pathPosition.x - currentDest.x);
//
//	return (prevDest.x <= currentDest.x && pathPosition.x >= currentDest.x)
//		|| (prevDest.x >= currentDest.x && pathPosition.x <= currentDest.x)
//		|| absX <= cBotMaxPositionError;
//}
//
//bool j1EntityMovable_ground::ReachedNodeOnYAxis(iPoint pathPosition, iPoint prevDest, iPoint currentDest)
//{
//	uint absY = 0;
//	if ((pathPosition.y - currentDest.y) < 0)
//		absY = (pathPosition.y - currentDest.y) * (-1);
//	else
//		absY = (pathPosition.y - currentDest.y);
//
//	return (prevDest.y <= currentDest.y && pathPosition.y >= currentDest.y)
//		|| (prevDest.y >= currentDest.y && pathPosition.y <= currentDest.y)
//		|| (absY <= cBotMaxPositionError);
//}
//
//void j1EntityMovable_ground::MoveTo(iPoint destination)
//{
//	mStuckFrames = 0;
//
//	App->pathfinding->CreatePath(pathPosition, destination);
//	App->pathfinding->CopyPathList(&pathList);
//}
//#endif __j1ENTITYMOVABLE_GROUND_CPP__