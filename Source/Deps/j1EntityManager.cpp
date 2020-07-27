//#ifndef __j1ENTITYMANAGER_CPP__
//#define __j1ENTITYMANAGER_CPP__include 
//
//#include "j1EntityManager.h"
//#include "p2Log.h" 
//#include "j1Entity.h"
//#include "j1EntityPlayer.h"
//#include "j1Map.h"
//#include "j1Collision.h"
//#include "j1Scene.h"
//
//j1EntityManager::j1EntityManager()
//{
//	name.create("entityManager");
//}
//
//j1EntityManager::~j1EntityManager()
//{
//	return;
//}
//
//bool j1EntityManager::Awake(pugi::xml_node& node)
//{
//	Player = (j1EntityPlayer*)App->manager->CreateEntity(ENTITY_TYPE::PLAYER, App->manager->Init_playerPos);
//
//	TestEnemy = (j1EntityMovable_ground*)App->manager->CreateEntity(ENTITY_TYPE::WALKING_ENEMY, App->manager->Init_playerPos);
//	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
//	{
//		item->data->Awake(node);
//	}
//	
//	return true;
//}
//
//bool j1EntityManager::Start()
//{
//	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
//	{
//		item->data->Start();
//	}
//
//	return true;
//}
//
//bool j1EntityManager::PreUpdate()
//{
//	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
//	{
//		item->data->PreUpdate();
//	}
//
//	return true;
//}
//
//bool j1EntityManager::Update(float dt) 
//{
//	bool ret = true;
//
//	accumulated_time += dt;
//	if (accumulated_time >= udate_ms_cycle)
//	{
//		doLogic = true;
//	}
//
//	for (p2List_item<j1Entity*>* EntityIterator = entities.start; EntityIterator != nullptr; EntityIterator = EntityIterator->next)
//	{
//		ret = EntityIterator->data->Update(dt, doLogic);
//		if (ret == false)
//		{
//			LOG("Entity update error");
//		}
//	}
//
//	if (doLogic == true)
//	{
//		accumulated_time = 0.0f;
//		doLogic = false;
//	}
//	return true;
//}
//
//bool j1EntityManager::PostUpdate() 
//{
//	for (p2List_item<j1Entity*>* EntityIterator = entities.start; EntityIterator != nullptr; EntityIterator = EntityIterator->next)
//	{
//		EntityIterator->data->PostUpdate();
//	}
//	DrawEntity();
//	return true;
//}
//
//bool j1EntityManager::DrawEntity()
//{
//	for (p2List_item<j1Entity*>* EntityIterator = entities.start; EntityIterator != nullptr; EntityIterator = EntityIterator->next)
//	{
//		EntityIterator->data->Draw();
//	}
//	return true;
//}
//
//bool j1EntityManager::CleanUp()
//{
//	for (p2List_item<j1Entity*>* item = entities.start; item != nullptr; item = item->next)
//	{
//		entities.del(item);
//	}
//	return true;
//}
//
//j1Entity* j1EntityManager::CreateEntity(ENTITY_TYPE type, iPoint initPos)
//{
//	static_assert((INT)ENTITY_TYPE::UNKNOWN_TYPE == 4, "CODE NEEDS UPDATE");
//	j1Entity* ret = nullptr;
//	switch (type)
//	{
//	case ENTITY_TYPE::PLAYER:			ret = new j1EntityPlayer(initPos, type); break;
//	case ENTITY_TYPE::WALKING_ENEMY:	ret = new j1EntityMovable_ground(initPos, type); break;
//	case ENTITY_TYPE::CASH_BAG:			ret = new j1Entity(initPos, type); break;
//	case ENTITY_TYPE::UNKNOWN_TYPE:		ret = nullptr; break;
//	}
//
//	if (ret == nullptr)
//	{
//		LOG("Entity type WAS UNKNOWN_TYPE");
//		return false;
//	}
//
//	entities.add(ret);
//	return ret;
//}
//
//bool j1EntityManager::DestroyEntity(j1Entity* entity) 
//{
//	p2List_item<j1Entity*>* item = nullptr; item->data = entity;
//	entities.del(item);
//
//	entity = nullptr;
//
//	return true;
//}
//
//void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
//{
//	{
//		/*
//		En vista de que esta función ha sido un fracaso, voy a seguir los siguientes pasos para mejorarla:
//
//		1. Crear una función en el modulo de colidiones para cada lado de un collider, por ejemplo:
//			bool canCollide_right(uint tile_gid)
//			{
//			bool ret = false;
//				if (tiene una tile en la derecha en la capa de colliders &&
//				esta es un collider de tipo WALL o CLIMB_WALL)
//				{
//					ret = true;
//				}
//				return ret;
//			}
//		*/
//		if (c1->type == PLAYER || c1->type == ENEMY)
//		{
//			iPoint wall_position = App->map->WorldToMap(c2->rect.x, c2->rect.y);
//			uint tileid = App->map->Metadata->GetLayerPositon(wall_position.x, wall_position.y);
//
//			if (c1->rect.y < (c2->rect.y + c2->rect.h) && c1->rect.y < c2->rect.y
//				&& (c1->rect.y + c1->rect.h) >= c2->rect.y && (c1->rect.y + c1->rect.h) < (c2->rect.y + c2->rect.h)) //Collision from top
//			{
//				if (App->coll->canCollide_top(tileid))
//				{
//					if(c2->type == WALL || c2->type == CLIMB_WALL)
//					{
//						j1EntityMovable* callback = (j1EntityMovable*)c1->callback;
//						callback->CurrentPosition.y = c2->rect.y - c1->rect.h;						
//					}
//
//					if(c2->type == BONUS)
//					{
//						//buscar entre el array de entities cual es la que coincide
//						//en posición x e y de collider y activar su OnCollision
//					}
//
//					if(c2->type == ENEMY)
//					{
//						//buscar entre el array de entities cual es la que coincide
//						//en posición x e y de collider y activar su OnCollision
//						//EN ESTA COLISIÓN EL ENEMIGO MUERE (CREAR UN BOOL PARA ESTE CASO)
//					}
//				}
//			}
//
//			else if (c1->rect.y > c2->rect.y && c1->rect.y < (c2->rect.y + c2->rect.h) &&
//				(c1->rect.y + c1->rect.h)>(c2->rect.y + c2->rect.h) && (c1->rect.y + c1->rect.h) > c2->rect.y)//collision from bottom
//			{
//				if (App->coll->canCollide_bottom(tileid))
//				{
//					if (c2->type == WALL || c2->type == CLIMB_WALL)
//					{
//						j1EntityMovable* callback = (j1EntityMovable*)c1->callback;
//						callback->CurrentPosition.y = c2->rect.y + c2->rect.h;
//					}
//
//					if (c2->type == BONUS)
//					{
//						//buscar entre el array de entities cual es la que coincide
//						//en posición x e y de collider y activar su OnCollision
//					}
//
//					if (c2->type == ENEMY)
//					{
//						//buscar entre el array de entities cual es la que coincide
//						//en posición x e y de collider y activar su OnCollision
//						//EN ESTA COLISIÓN EL ENEMIGO MUERE (CREAR UN BOOL PARA ESTE CASO)
//					}
//					
//				}
//			}
//
//			else if (c1->rect.x > c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) &&
//				(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) > (c2->rect.x + c2->rect.w)) //collision from right side
//			{
//				if (App->coll->canCollide_right(tileid))
//				{
//					j1EntityMovable* callback = (j1EntityMovable*)c1->callback;
//					callback->CurrentPosition.x = c2->rect.x + c2->rect.w;
//				}
//			}
//
//			else if (c1->rect.x < c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) &&
//				(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) < (c2->rect.x + c2->rect.w))//collision from left side
//			{
//				if (App->coll->canCollide_left(tileid))
//				{
//					j1EntityMovable* callback = (j1EntityMovable*)c1->callback;
//					callback->CurrentPosition.x = c2->rect.x - c1->rect.w;
//				}
//			}
//		}
//
//		if (c2->type == PLAYER || c2->type == ENEMY)
//		{
//			iPoint wall_position = App->map->WorldToMap(c2->rect.x, c2->rect.y);
//			uint tileid = App->map->Metadata->GetLayerPositon(wall_position.x, wall_position.y);
//
//			if (c2->rect.y < (c1->rect.y + c1->rect.h) && c2->rect.y < c1->rect.y &&
//				(c2->rect.y + c2->rect.h) >= c1->rect.y && (c2->rect.y + c2->rect.h) < (c1->rect.y + c1->rect.h)) //Collision from top
//			{
//				if (App->coll->canCollide_top(tileid))
//				{
//					j1EntityMovable* callback = (j1EntityMovable*)c2->callback;
//					callback->CurrentPosition.y = c1->rect.y - c2->rect.h;
//				}
//			}
//
//			else if (c2->rect.y > c1->rect.y && c2->rect.y < (c1->rect.y + c1->rect.h) &&
//				(c2->rect.y + c2->rect.h)>(c1->rect.y + c1->rect.h) && (c2->rect.y + c2->rect.h) > c1->rect.y)//collison from bottom
//			{
//				if (App->coll->canCollide_bottom(tileid))
//				{
//					j1EntityMovable* callback = (j1EntityMovable*)c2->callback;
//					callback->CurrentPosition.y = c1->rect.y + c1->rect.h;
//				}
//			}
//
//			else if (c2->rect.x > c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
//				(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) > (c1->rect.x + c1->rect.w)) //collision from right side
//			{
//				if (App->coll->canCollide_right(tileid))
//				{
//					j1EntityMovable* callback = (j1EntityMovable*)c2->callback;
//					callback->CurrentPosition.x = c1->rect.x + c1->rect.w;
//				}
//			}
//
//			else if (c2->rect.x < c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
//				(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) < (c1->rect.x + c1->rect.w))//collision from left side
//			{
//				if (App->coll->canCollide_left(tileid))
//				{
//					j1EntityMovable* callback = (j1EntityMovable*)c2->callback;					
//					callback->CurrentPosition.x = c1->rect.x - c2->rect.w;
//				}
//			}
//		}
//	}
//
//}

//void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
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
//				Player->CurrentPosition.x = c2->rect.y - c1->rect.h;
//				//switch (c2->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.x = c2->rect.y - c1->rect.h;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c2->rect.y - c1->rect.h;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;	
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	//EN ESTA COLISIÓN EL ENEMIGO MUERE (CREAR UN BOOL PARA ESTE CASO)
//				//	break;
//				//}
//			}
//		}
//		else if(c1->rect.y > c2->rect.y && c1->rect.y < (c2->rect.y + c2->rect.h) &&
//			(c1->rect.y + c1->rect.h)>(c2->rect.y + c2->rect.h) && (c1->rect.y + c1->rect.h) > c2->rect.y)//collision from bottom
//		{
//			if (App->coll->canCollide_bottom(tileid))
//			{
//				Player->CurrentPosition.y = c2->rect.y + c2->rect.h;
//				//switch (c2->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.x = c2->rect.y + c2->rect.h;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c2->rect.y + c2->rect.h;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//				//}
//			}
//		}
//	
//		else if (c1->rect.x > c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) && 
//			(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) > (c2->rect.x + c2->rect.w)) //collision from right side
//		{
//			if (App->coll->canCollide_right(tileid))
//			{
//				Player->CurrentPosition.x = c2->rect.x + c2->rect.w;
//				//switch (c2->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.y = c2->rect.x + c2->rect.w;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c2->rect.x + c2->rect.w;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//				//}
//			}
//		}
//	
//		else if (c1->rect.x < c2->rect.x && c1->rect.x < (c2->rect.x + c2->rect.w) &&
//			(c1->rect.x + c1->rect.w) > c2->rect.x && (c1->rect.x + c1->rect.w) < (c2->rect.x + c2->rect.w))//collision from left side
//		{
//			if (App->coll->canCollide_left(tileid))
//			{
//				Player->CurrentPosition.x = c2->rect.x - c1->rect.w;
//				//switch (c2->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.y = c2->rect.x - c1->rect.w;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c2->rect.x - c1->rect.w;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//				//}
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
//				Player->CurrentPosition.y = c1->rect.y - c2->rect.h;
//				//switch (c1->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.y - c2->rect.h;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.y - c2->rect.h;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	//EN ESTA COLISIÓN EL ENEMIGO MUERE (CREAR UN BOOL PARA ESTE CASO)
//				//	break;
//				//}
//			}
//		}
//	
//		else if (c2->rect.y > c1->rect.y && c2->rect.y < (c1->rect.y + c1->rect.h) &&
//			(c2->rect.y + c2->rect.h)>(c1->rect.y + c1->rect.h) && (c2->rect.y + c2->rect.h) > c1->rect.y)//collison from bottom
//		{
//			if (App->coll->canCollide_bottom(tileid))
//			{
//				Player->CurrentPosition.y = c1->rect.y + c1->rect.h;
//				//switch (c1->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.y + c1->rect.h;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.y + c1->rect.h;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	//EN ESTA COLISIÓN EL ENEMIGO MUERE (CREAR UN BOOL PARA ESTE CASO)
//				//	break;
//				//}
//			}
//		}
//	
//		else if (c2->rect.x > c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
//			(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) > (c1->rect.x + c1->rect.w)) //collision from right side
//		{
//			if (App->coll->canCollide_right(tileid))
//			{
//				Player->CurrentPosition.x = c1->rect.x + c1->rect.w;
//				//switch (c1->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.x + c1->rect.w;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.x + c1->rect.w;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	//EN ESTA COLISIÓN EL ENEMIGO MUERE (CREAR UN BOOL PARA ESTE CASO)
//				//	break;
//				//}
//			}
//		}
//	
//		else if (c2->rect.x < c1->rect.x && c2->rect.x < (c1->rect.x + c1->rect.w) &&
//			(c2->rect.x + c2->rect.w) > c1->rect.x && (c2->rect.x + c2->rect.w) < (c1->rect.x + c1->rect.w))//collision from left side
//		{
//			if (App->coll->canCollide_left(tileid))
//			{
//				Player->CurrentPosition.x = c1->rect.x - c2->rect.w;
//				//switch (c1->type)
//				//{
//				//case WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.x - c2->rect.w;
//				//	break;
//
//				//case CLIMB_WALL:
//				//	App->manager->Player->CurrentPosition.y = c1->rect.x - c2->rect.w;
//				//	break;
//
//				//case BONUS:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	break;
//
//				//case ENEMY:
//				//	//buscar entre el array de entities cual es la que coincide
//				//	//en posición x e y de collider y activar su OnCollision
//				//	//EN ESTA COLISIÓN EL ENEMIGO MUERE (CREAR UN BOOL PARA ESTE CASO)
//				//	break;
//				//}
//			}
//		}
//	}
//}

//#endif __j1ENTITYMANAGER_CPP__

