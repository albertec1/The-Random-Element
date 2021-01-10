#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "SDL/include/SDL.h"
#include "j1Window.h"
j1Window::j1Window() : j1Module()
{
	window = NULL;
	screen_surface = NULL;
	name.create("window");
}

j1Window::~j1Window()
{
}

bool j1Window::Awake(pugi::xml_node& config)
{
	LOG("Init SDL window & surface");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		LOG("SDL_VIDEO could not be initialized! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;
		bool fullscreen = config.child("fullscreen").attribute("value").as_bool(false);
		bool borderless = config.child("borderless").attribute("value").as_bool(false);
		bool resizable = config.child("resizable").attribute("value").as_bool(false);
		bool fullscreen_window = config.child("fullscreen_window").attribute("value").as_bool(false);

		width = config.child("resolution").attribute("width").as_int(640);
		height = config.child("resolution").attribute("height").as_int(480);
		scale = config.child("resolution").attribute("scale").as_int();


		if (fullscreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (borderless == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if (fullscreen_window == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(App->GetTitle(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		
		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}	
	}

	return ret;
}

//Called before quitting
bool j1Window::CleanUp()
{
	LOG("Destroying SDL Window and quitting all SDL subsystems");

	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

// Set new window title
void j1Window::SetTitle(const char* new_title)
{
	//title.create(new_title);
	SDL_SetWindowTitle(window, new_title);
}

void j1Window::GetWindowSize(uint& width, uint& height) const
{
	width = this->width;
	height = this->height;
}

int j1Window::GetScale() const
{
	return scale;
}

void j1Window::Fullscreen()
{
	if (fullscreen == false) {
		Uint32 flags = SDL_WINDOW_SHOWN;
		flags |= SDL_WINDOW_FULLSCREEN;
		SDL_SetWindowFullscreen(window, flags);
		fullscreen = true;
	}
	else {
		SDL_SetWindowFullscreen(window, 0);
		fullscreen = false;
	}
}
