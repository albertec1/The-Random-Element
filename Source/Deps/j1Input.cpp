#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "SDL/include/SDL.h"

j1Input::j1Input() : j1Module()
{
	name.create("input");

	keyboard = new j1KeyState[NUM_KEYS];
	memset(keyboard, (int)j1KeyState::KEY_IDLE, sizeof(j1KeyState) * NUM_KEYS);
	memset(mouse_buttons, (int)j1KeyState::KEY_IDLE, sizeof(j1KeyState) * NUM_MOUSE_BUTTONS);
}

j1Input::~j1Input()
{
	delete[] keyboard;
}

bool j1Input::Awake(pugi::xml_node& config)
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Input::Start()
{
	SDL_StopTextInput();
	return true;
}

bool j1Input::PreUpdate()
{
	static SDL_Event event;

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < NUM_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == j1KeyState::KEY_IDLE)
				keyboard[i] = j1KeyState::KEY_DOWN;
			else
				keyboard[i] = j1KeyState::KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == j1KeyState::KEY_REPEAT || keyboard[i] == j1KeyState::KEY_DOWN)
				keyboard[i] = j1KeyState::KEY_UP;
			else
				keyboard[i] = j1KeyState::KEY_IDLE;
		}

		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				window_events[(int)j1WindowEvent::WE_QUIT] = true;
				break;

			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
					//case SDL_WINDOWEVENT_LEAVE:
					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_FOCUS_LOST:
						window_events[(int)j1WindowEvent::WE_HIDE] = true;
						break;

					//case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
						window_events[(int)j1WindowEvent::WE_SHOW] = true;
						break;

					case SDL_WINDOWEVENT_CLOSE:
						window_events[(int)j1WindowEvent::WE_QUIT] = true;
						break;
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = j1KeyState::KEY_DOWN;
				//LOG("Mouse button %d down", event.button.button-1);
				break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = j1KeyState::KEY_UP;
				//LOG("Mouse button %d up", event.button.button-1);
				break;

			case SDL_MOUSEMOTION:
				int scale = App->win->GetScale();
				mouse_motion_x = event.motion.xrel / scale;
				mouse_motion_y = event.motion.yrel / scale;
				mouse_x = event.motion.x / scale;
				mouse_y = event.motion.y / scale;
				//LOG("Mouse motion x %d y %d", mouse_motion_x, mouse_motion_y);
				break;

			}
		}
	}

	return true;
}

bool j1Input::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool j1Input::GetWindowEvent(j1WindowEvent event)
{
	return window_events[(int)event];
}

void j1Input::GetMousePosition(int& x, int& y)
{
	x = mouse_x;
	y = mouse_y;
}

void j1Input::GetMouseMotion(int& x, int& y)
{
	x = mouse_motion_x;
	y = mouse_motion_y;
}

void j1Input::GetMousePosFloat(float& x, float& y)
{
	x = mouse_x;
	y = mouse_y;
}

fPoint j1Input::GetMouseWorldPosition()
{
	fPoint ret;
	int mx, my;
	GetMousePosition(mx, my);
	ret.x = mx - App->render->camera.x / App->win->GetScale();
	ret.y = my - App->render->camera.y / App->win->GetScale();

	return ret;
}

void j1Input::EnableTextInput()
{
	SDL_StartTextInput();
	text_input = true;
}

void j1Input::DisableTextInput() {

	SDL_StopTextInput();
	text_input = false;
	App->input->text.Clear();
}

p2SString j1Input::GetText() {

	return text;
}

int j1Input::GetCursorPosition() {

	int width = 0;
	int height = 0;

	return width;
}

p2SString j1Input::GetModifiedString()
{

	if (cursor_position != 0) {

		p2SString new_text(text.GetString());
		new_text.Cut(text.Length() - cursor_position);
		return new_text;
	}

	else
		return text;
}