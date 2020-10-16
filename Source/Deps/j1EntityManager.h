#pragma once

#define MAX_VELOCITY 15

#include "j1Entity.h"
#include "p2List.h"

struct SDL_Rect;
struct Collider;
struct SDL_Texture;
struct j1EntityPlayer;

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

	bool Save(pugi::xml_node& data);

	bool Load(pugi::xml_node& data);

public:

	j1Entity* CreateEntity(ENTITY_TYPE type, iPoint initPos);
	bool DestroyEntity(j1Entity* entity);
	bool DestroyAllEntities();
	void OnCollision(Collider* c1, Collider* c2);

public:
	p2List<j1Entity*>		entities;
	j1EntityPlayer*			player;
};