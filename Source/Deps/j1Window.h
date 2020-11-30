#pragma once

#include "j1Module.h"

struct SDL_Window;
struct SDL_Surface;

class j1Window : public j1Module
{
public:

	j1Window();
	virtual ~j1Window();

	bool Awake(pugi::xml_node& config);
//	bool Update();
	bool CleanUp();

	void SetTitle(const char* new_title);
	void GetWindowSize(uint& width, uint& height) const;
	int GetScale() const;

public:
	SDL_Window* window;//The window we'll be rendering to
	SDL_Surface* screen_surface;//The surface contained by the window

private:
	p2SString		title;
	uint			width;
	uint			height;
	int			scale;
};