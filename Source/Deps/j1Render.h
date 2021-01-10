#pragma once

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h" 

class j1Render : public j1Module
{
public:

	j1Render();
	virtual ~j1Render();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	//Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	//Blit
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, bool flip = false, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	iPoint ScreenToWorld(int x, int y) const;

	//Camera
	void CheckCamera(iPoint player_position);
	SDL_Rect camera_boundaries;

	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer* renderer;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;

private:
	bool camera_follows_player;
};