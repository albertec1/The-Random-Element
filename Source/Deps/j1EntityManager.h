#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "p2List.h"
#include "j1EntityPlayer.h"

struct SDL_Rect;
struct Collider;
struct SDL_Texture;

class j1EntityManager : public j1Module
{
public: 
	j1EntityManager();

	~j1EntityManager();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool DrawEntity();

	bool CleanUp();

public:

	j1Entity* CreateEntity(ENTITY_TYPE type, iPoint initPos);
	bool DestroyEntity(j1Entity* entity);
	void OnCollision(Collider* c1, Collider* c2);
	
public:
	//SDL_Texture					PlayerTexture;
	//Entity list
	p2List<j1Entity*>			entities;
	j1EntityPlayer*				Player;
	j1EntityMovable_ground*		TestEnemy;

	//Entities Initial position
	iPoint						Init_playerPos;			
	iPoint						Init_groundEnemyPos;
	iPoint						Init_flyingEnemyPos;
		
	//Time management/logic---
	float						udate_ms_cycle = 10.0f; //just to put some temporary value here 
	float						accumulated_time = 0;
	bool						doLogic = false;

	//config file---
	pugi::xml_node				config;



};
#endif __j1ENTITYMANAGER_H__