#pragma once
  
#define MAX_COLLIDERS 3020
#define MAX_ENTITIES 20
#define DOLOGIC_TIME 10

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "j1Module.h"

class j1Entity;
class MapLayer;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	WALL,
	PLATFORM,
	BONUS,
	PLAYER,
	ENEMY,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	bool active;
	COLLIDER_TYPE type;
	j1Entity* callback = nullptr;

	Collider();
	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Entity* calback = nullptr);

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	void SetSize(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}
	bool CheckCollision(const SDL_Rect& r) const;
};
class j1Collision : public j1Module
{
public:

	j1Collision();
	virtual ~j1Collision();

	bool Awake(pugi::xml_node& node);
	bool PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type,j1Entity* calback = nullptr);
	void DebugDraw();

	//--Check if collision is possible--//
	bool canCollide_right(uint tile_gid);
	bool canCollide_top(uint tile_id);
	bool canCollide_bottom(uint tile_id);
	bool canCollide_left(uint tile_id);

	void deleteAll();
public:
	MapLayer* metadata;

private:
	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = true;
	uint win_width;
	uint win_height;

};
