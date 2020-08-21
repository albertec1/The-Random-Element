#pragma once

#include "j1Module.h"

#define NUM_KEYS 352	
#define NUM_MOUSE_BUTTONS 5
#define LAST_KEYS_PASSED_BUFFER 50

struct SDL_Rect;

enum class j1WindowEvent
{
	WE_QUIT = 0, 
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum class j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class j1Input : public j1Module
{
public:

	j1Input();
	virtual ~j1Input();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool CleanUp();
	
	// Gather relevant win events
	bool GetWindowEvent(j1WindowEvent event);

	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButton(int id) const
	{
		return mouse_buttons[id - 1]; 
	}

	// Check id a certain window event happened
	bool GetWindowEvent(int code);

	// Get Mouse / Axis position
	void GetMousePosition(int& x, int& y);
	void GetMouseMotion(int& x, int& y);
	j1KeyState* keyboard;

private:
	bool		window_events[(int)j1WindowEvent::WE_COUNT];
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;
};