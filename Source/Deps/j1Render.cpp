#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1EntityManager.h"
#include "j1EntityPlayer.h"
#include "j1Window.h"
#include "j1Render.h"

j1Render::j1Render() : j1Module()
{
	name.create("renderer");
	background.r = 50;
	background.g = 100;
	background.b = 150;
	background.a = 0;
}
j1Render::~j1Render()
{}

bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if (config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = App->win->screen_surface->w / App->win->GetScale();
		camera.h = App->win->screen_surface->h / App->win->GetScale();
		camera.x = 0;
		camera.y = 0;
	}
	
	return ret;
}
bool j1Render::Start()
{
	LOG("Render Start"); 
	camera.x = -App->manager->player->GetCurrentPosition().x + camera.w * 0.3;
	camera.y = -App->manager->player->GetCurrentPosition().y + camera.h * 0.66;
	camera_boundaries.w = camera.w * 0.25;
	camera_boundaries.h = camera.h * 0.33;
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}
bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	camera_boundaries.x = -camera.x + camera.w * 0.33;
	camera_boundaries.y = -camera.y + camera.h * 0.40;

	//DrawQuad(camera_boundaries, 20, 50, 90);
	return true;
}
bool j1Render::Update(float dt)
{
	return true;
}
bool j1Render::PostUpdate()
{
	//camera things
	iPoint player_position = App->manager->player->GetCurrentPosition();
	if (camera_boundaries.x > (player_position.x / App->win->GetScale()))
		camera.x  += (camera_boundaries.x - (player_position.x / App->win->GetScale()));

	if ((camera_boundaries.x + camera_boundaries.w) < ((player_position.x / App->win->GetScale()) + 32))
		camera.x -= (((player_position.x / App->win->GetScale()) + 32)-(camera_boundaries.x + camera_boundaries.w));

	if (camera_boundaries.y > player_position.y / (App->win->GetScale()))
		camera.y += (camera_boundaries.y - (player_position.y / App->win->GetScale()));

	if ((camera_boundaries.y + camera_boundaries.h) < ((player_position.y / App->win->GetScale()) + 32))
		camera.y -= (((player_position.y / App->win->GetScale()) + 32) - (camera_boundaries.y + camera_boundaries.h));

	/*Is it needed every frame??*/SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}
bool j1Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

//Load / Save
bool j1Render::Load(pugi::xml_node& data)
{
	if (App->save_document_full == true)
	{
		pugi::xml_node node = data.child("render").child("camera");

		camera.x = node.attribute("x").as_int();
		camera.y = node.attribute("y").as_int();
	}
	return true;
}
bool j1Render::Save(pugi::xml_node& data) const
{
	pugi::xml_node node = data.append_child("render");
	pugi::xml_node cam_node = node.append_child("camera");

	cam_node.append_attribute("x").set_value(camera.x);
	cam_node.append_attribute("y").set_value(camera.y);

	return true;
}

//Blit
void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}
void j1Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}
bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, bool flip, float speed, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_Rect sprites;
	if (flip)
	{
		sprites.x = (int)(camera.x * speed) + x * scale + 40;
		sprites.y = (int)(camera.y * speed) + y * scale;
	}
	else
	{
		sprites.x = (int)(camera.x * speed) + x * scale;
		sprites.y = (int)(camera.y * speed) + y * scale;
	}

	if (section != NULL)
	{
		if (flip)
		{
			sprites.w = -section->w;
			sprites.h = section->h;
		}
		else
		{
			sprites.w = section->w;
			sprites.h = section->h;
		}
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &sprites.w, &sprites.h);
	}

	sprites.w *= scale;
	sprites.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if (pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	if (SDL_RenderCopyEx(renderer, texture, section, &sprites, angle, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if (use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for (uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
iPoint j1Render::ScreenToWorld(int x, int y) const
{
	iPoint ret;
	int scale = App->win->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}
void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}