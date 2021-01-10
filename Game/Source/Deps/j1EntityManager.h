#pragma once

#define MAX_VELOCITY 15

#include "j1Entity.h"
#include "j1EntityPlayer.h"
#include "p2List.h"
#include "j1MovingEntity.h"

struct SDL_Rect;
struct Collider;
struct SDL_Texture;
struct j1EntityPlayer;
struct AutonomousEntity;


class j1EntityManager : public j1Module
{
public:
	j1EntityManager();

	~j1EntityManager();

	bool Awake(pugi::xml_node&);

	bool AwakeAgain();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool DrawEntity();

	bool CleanUp();

	bool Save(pugi::xml_node& data);

	bool Load(pugi::xml_node& data);

public:
	j1Entity* CreateEntity(ENTITY_TYPE type, fPoint initPos, EntityStates state = EntityStates::ST_IDLE);
	bool DestroyEntity(j1Entity* entity);
	bool DestroyAllEntities();
	void OnCollision(Collider* c1, Collider* c2);
	void resetEntities();
	bool godMode = false;

public:
	p2List<j1Entity*>		entities;
	j1EntityPlayer*			player;
	AutonomousEntity*		airEnemy;
	AutonomousEntity*		groundEnemy;

private:
	bool doLogic;
	float logicTimer;
	pugi::xml_node awakeNode;

};
 