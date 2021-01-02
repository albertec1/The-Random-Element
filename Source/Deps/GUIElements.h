#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "p2Log.h"
#include "j1Font.h"
#include "SDL/include/SDL_render.h"

#include "SDL\include\SDL_pixels.h"

struct SDL_Texture;

enum class GUItype
{
	GUI_ERROR,
	GUI_BUTTON,
	GUI_INPUTBOX,
	GUI_SCROLLBAR,
	GUI_LABEL,
	GUI_IMAGE,
	GUI_TEXT
};

enum class SCROLL_TYPE
{
	SCROLL_NONE,
	SCROLL_MUSIC,
	SCROLL_RESOURCES,
	SCROLL_COTTON,
	SCROLL_WOOD,
	SCROLL_METAL
};

enum class TEXTURE
{
	BUTON,
	BUTON_HOVER,
	OPTIONS,
	NEXT,
	PREV,
	SCROLL,
	MANAGER_IMAGE,
	IMAGE,
	MAIN_IMAGE,
	RESOURCES_IMAGE,
	BUILDING_IMAGE,
	BOAT_IMAGE,
	TRADE,
	HARVESTER,
	BOTON_SCROLL,
	AUDIO_IMAGE,
	LINK,
	TRADER_DERECHA,
	TRADER_IZQUIERDA,
	COTTON,
	WOOD,
	METAL,
	TOWNHALL,
	STORAGE,
	COST,
	GODMODE,
	INFO,
	INFO_IMAGE,
	QUEST_IMAGE_CLOSE,
	QUEST_IMAGE_OPEN,
	QUEST_CLOSE,
	COIN,
	AUTOMATIC,
	LVLUP,
	COIN_COST,
	EXPLANATION,
	DIALOG,
	SHIP,
	BALLOON,
	QUEST,
	INFORMATION_IMAGE,
	CARRIER,
	TURRET_ICON,
	CARRIER_IN,
	CARRIER_OUT,
	CARRIER_CAP,
	NONE
};

class j1Element
{

public:

	j1Element() { };
	~j1Element();

	virtual bool Start();
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };

	virtual bool CleanUp() { return true; };

	bool OnAbove();
	virtual bool ChangeLabel(names name = names::NO_NAME);
	virtual void OnClick();
	virtual void OnLeftClick();
	virtual void OnRelease();
	virtual void Dragging();
	void Draw();

public:

	j1Element* parent = nullptr;
	j1Module* listener = nullptr;
	GUItype type = GUItype::GUI_ERROR;
	TEXTURE textureType = TEXTURE::NONE;
	fPoint map_position = { 0,0 };
	fPoint inside_position = { 0,0 };

	j1Element* Button = nullptr;

	SDL_Color color = { 255,255,255 };
	char* text = nullptr;
	bool enabled = false;
	bool interactable = false;

	bool X_drag = false;
	bool Y_drag = false;

	bool above = false;
	bool focus = false;

	bool decorative = false;

	SDL_Rect rect = { 0,0,0,0 };

	int Value;
	float Float_Value;

	SDL_Texture* texture = nullptr;
	SDL_Texture* texture_hover = nullptr;
	SDL_Texture* texture_hover_2 = nullptr;
	SDL_Texture* texture_click = nullptr;
};
///////////////////////////////////////////////////////////////////
class j1Button : public j1Element
{
public:

	j1Button();
	~j1Button();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void Dragging();
	void MovingIt(float dt);
	void OnRelease();

private:

	j1Element* label = nullptr;
	iPoint drag = { 0,0 };

	bool dragging;
	bool options_button = false;
};
/////////////////////////////////////////////////////////////////////
class j1Image : public j1Element
{
public:

	j1Image();
	~j1Image();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

};
////////////////////////////////////////////////////////////////
class j1InputBox : public j1Element
{
public:

	j1InputBox(char* text);
	~j1InputBox();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void OnClick();
	void OnRelease();
private:

	j1Element* string = nullptr;
	j1Element* background = nullptr;
};

class j1Label : public j1Element
{
public:

	j1Label();
	~j1Label();

	bool ChangeLabel(names name = names::NO_NAME);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:

	int font_name = -1;
};
////////////////////////////////////////////////////////////////
class j1ScrollBar : public j1Element
{
public:

	j1ScrollBar(SCROLL_TYPE type);
	~j1ScrollBar();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void ScrollLimits();

	SCROLL_TYPE Type = SCROLL_TYPE::SCROLL_NONE;

};

