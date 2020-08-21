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
	bool Shift_enabled;	//Run
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

	enum class CurrentState
	{
		ST_UNKNOWN,
		ST_IDLE,
		ST_LEFT_W,
		ST_LEFT_R,
		ST_RIGHT_W,
		ST_RIGHT_R,
		ST_JUMPING,
		ST_SLIDING,
		ST_CLIMBING,
		ST_DYING,
	};

public:
	j1EntityPlayer(iPoint pos, ENTITY_TYPE type);

	~j1EntityPlayer();

	bool Awake(pugi::xml_node& node);

	bool PreUpdate();

	bool Update(float dt, bool doLogic);

	bool Start();

	bool Draw();

	void OnCollision(Collider* c1, Collider* c2);

public:

	//PLAYER
	iPoint			size;
	PlayerInput		player_input;
	CurrentState	player_state;

	//Texture
	SDL_Texture* Graphics = nullptr;

	//ANIMATION
	//Draw diferents animations
	//Animation*	current_animation;		
	//SDL_Rect		rotating_animation;		
	//bool			flipped = false;		
	//Idle---
	//Animation		idle;					
	//Running---
	//Animation		running;
	//Dying---
	//Animation		dying;
	//Jumping---
	//Animation		jumping;

	void			grounded();
	void			jump();

	//SHORTCUTS
	bool God_Mode = false;

	bool lateral_collision_left = false;
	bool lateral_collision_right = false;
	bool top_collision = false;
	bool bottom_collision = false;

	uint WALL_id;
	uint CLIMB_WALL_id;
	uint BONUS_id;
};