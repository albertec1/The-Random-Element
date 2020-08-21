#pragma once
#include "j1Entity.h"
#include "p2List.h"

struct SDL_Rect;
struct Collider;
struct SDL_Texture;

class j1EntityManager : public j1Module
{
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
	p2List<j1Entity*>		entities;
};