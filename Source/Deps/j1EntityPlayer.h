#pragma once

#include "p2Point.h"
#include "j1EntityManager.h"
#include "j1Entity.h"
#include "j1MovingEntity.h"

class SDL_Texture;

struct PlayerInput
{
	//TODO://SHORTCUTS //player only
	bool F1_enabled;	//START LEVEL 1 (falta)
	bool F2_enabled;	//START LEVEL 2 (falta)
	bool F3_enabled;	//Restart level (falta)
	bool F5_enabled;	//Save game (falta)
	bool F6_enabled;	//Load game (falta)
	bool F7_enabled;	//Show Colliders (falta)
	bool F8_enabled;	//God Mode (falta)

	//PLAYER //player only
	bool W_enabled;		//Climb
	bool A_enabled;		//Left
	bool S_enabled;		//Slide (has to press a direction in order to slide)
	bool D_enabled;		//Right
	bool K_enabled;		//Special
	bool Space_enabled;	//Jump

	//GODMODE //player only
	bool W_GOD_enabled;		//Up
	bool A_GOD_enabled;		//Left
	bool S_GOD_enabled;		//Down
	bool D_GOD_enabled;		//Right
};

class j1EntityPlayer : public j1MovingEntity
{
public:
	j1EntityPlayer(iPoint pos, ENTITY_TYPE type);

	~j1EntityPlayer();

	bool Start();

	bool Awake(pugi::xml_node& node);

	bool PreUpdate();

	bool Update(float dt, bool doLogic);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	int DoSpecialLeft();

	int DoSpecialRight();

public:

	//PLAYER
	PlayerInput		player_input;
	ENTITY_STATES	player_state;

	//Texture
	SDL_Texture*	graphics = nullptr;

	//SHORTCUTS
	bool god_mode = false;

	bool jump_available = false;
	bool jumping = false;

	uint max_special_range;
	uint special_distance;
	float special_timer;
	bool special_last_frame;
};