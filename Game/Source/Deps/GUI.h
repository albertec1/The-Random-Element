#pragma once
#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "GUIElements.h"
#include <vector>

class j1Entity;
struct SDL_Texture;

class j1GUI : public j1Module
{

public:

	j1GUI();
	~j1GUI();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void Spining_UI();
	void Reset_UI_Pos();

	SDL_Texture* LoadTexture(Texture textureType = Texture::NONE);

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	void UpdatePosition(j1Element* element, fPoint position, fPoint local_position);
	j1Element* AddElement(GUItype type, j1Element* parent, fPoint map_Position, fPoint insidePosition, bool interactable, bool enabled, SDL_Rect section, char* text = nullptr, j1Module* listener = nullptr, bool X_drag = false, bool Y_drag = false, ScrollType scrollType = ScrollType::SCROLL_NONE, bool decor = false, Texture textureType = Texture::NONE);
	p2List<j1Element*>	GUIElements;

public:
	//TEXTURES FOR UI
	SDL_Texture* textureLoad = nullptr;
	bool disableClick;

private:
	//MOVING FUNCTIONS
	void MoveUIElements(float x, float y, j1Element* element = nullptr);
	bool CorrectX(int x);
	bool CorrectY(int y, int y_1);

	float s = 0;
};

#endif //  __j1GUI_H__

