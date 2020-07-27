//#ifndef _j1PLAYER_H_
//#define _j1PLAYER_H_
//
//#include "j1Module.h"
//#include "j1Input.h"
//#include "j1Render.h"
//#include "p2Point.h"
//#include "Animation.h"
//
//struct SDL_Texture;
//struct Animation;
//struct Collider;
//
//struct Player_Input
//{
//	//SHORTCUTS //player only
//	bool F1_enabled;	//START LEVEL 1 (falta)
//	bool F2_enabled;	//START LEVEL 2 (falta)
//	bool F3_enabled;	//Restart level (falta)
//	bool F5_enabled;	//Save game (falta)
//	bool F6_enabled;	//Load game (falta)
//	bool F7_enabled;	//Show Colliders (falta)
//	bool F8_enabled;	//God Mode (falta)
//
//	//PLAYER //player only
//	bool W_enabled;		//Climb
//	bool A_enabled;		//Left
//	bool S_enabled;		//Slide (has to press a direction in order to slide)
//	bool D_enabled;		//Right
//	bool Shift_enabled;	//Run
//	bool Space_enabled;	//Jump
//
//	//GODMODE //player only
//	bool W_GOD_enabled;		//Up
//	bool A_GOD_enabled;		//Left
//	bool S_GOD_enabled;		//Down
//	bool D_GOD_enabled;		//Right
//};
//enum Current_State
//{
//	ST_UNKNOWN,
//	ST_IDLE,
//	ST_LEFT_W,
//	ST_LEFT_R,
//	ST_RIGHT_W,
//	ST_RIGHT_R,
//	ST_JUMPING,
//	ST_SLIDING,
//	ST_CLIMBING,
//	ST_DYING,
//};
//
//class j1Player : public j1Module
//{
//private:
//
//	iPoint Initial_Pos; //player exclusive
//
//public:
//
//	//SHORTCUTS
//	bool God_Mode = false; // player only
//
//	//TESTING - TEMPORAL
//	float Floor = CurrentPosition.y; //Movement
//
//	j1Player();
//
//	virtual ~j1Player();
//
//	bool Awake(pugi::xml_node& config);
//
//	bool Start();
//
//	bool PreUpdate();
//	bool Update(float dt);
//	bool PostUpdate();
//	bool CleanUp();
//
//	
//	// Callback ---
//	void OnCollision(Collider* c1, Collider*c2);
//	
//
//	//PLAYER
//	iPoint			Size;
//	SDL_Rect		PlayerRect;
//	Player_Input	PlayerInput;
//	Current_State	PlayerState;
//
//
//
//	//POSITION
//	iPoint			CurrentPosition;
//	iPoint			StartingPosition;
//	iPoint			ActualizedPosition;
//	float			PlayerVel_w;
//	float			PlayerVel_r;
//	SDL_Texture*	Graphics = nullptr;
//
//
//	//ANIMATION
//	//Draw diferents animations
//	Animation*		current_animation;
//	SDL_Rect		rotating_animation;
//	bool			flipped = false;
//	//Idle
//	Animation		idle;
//
//	//Walking
//	Animation		walking;
//
//	//Running
//	Animation		running;
//
//	//Jumping
//	Animation		jumping;
//	float			Gravity;
//	float			falling_velocity;
//	bool			in_land;
//	bool			falling;
//	bool			jump_available;
//	bool			mid_air;
//	bool			jump_ended;
//	void			grounded();
//	void			jump();
//
//	//Sliding
//	Animation		sliding;
//	float			Slide_distance;
//
//	//Climbing
//	Animation		climbing;
//
//	//Dying
//	Animation		dying;
//
//
//public:
//
//	//--- Colliders
//	Collider*		PlayerCollider;
//
//	bool lateral_collision_left = false;
//	bool lateral_collision_right = false;
//	bool top_collision = false;
//	bool bottom_collision = false;
//
//	uint WALL_id;
//	uint CLIMB_WALL_id;
//	uint BONUS_id;
//};
//
//#endif