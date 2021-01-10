#include "GUI.h"
#include "GUIElements.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Textures.h"
#include "Font.h"


j1Element::~j1Element()
{

}

bool j1Element::Start()
{


	return true;
}

void j1Element::Draw()
{


}

//returns true if the mouse is above the element
bool j1Element::OnAbove()
{
	bool ret = false;

	SDL_Point mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	SDL_Rect intersect = { mapPosition.x / App->win->scale, mapPosition.y / App->win->scale, rect.w / App->win->scale, rect.h / App->win->scale };

	if (SDL_PointInRect(&mouse, &intersect) && this->enabled && this->interactable) 
	{
		App->clickingUI = true;
		if (listener != nullptr)
		{
			this->listener->GUIEeventManager(GUIEvent::EVENT_HOVER, this);
		}
		ret = true;
	}

	return ret;
}

bool j1Element::ChangeLabel(names name)
{
	return false;
}

void j1Element::OnClick()
{
	if (listener != nullptr)
	{
		this->listener->GUIEeventManager(GUIEvent::EVENT_ONCLICK, this);
	}
}

void j1Element::OnLeftClick()
{
	if (listener != nullptr)
	{
		this->listener->GUIEeventManager(GUIEvent::EVENT_LEFTCLICK, this);
	}

}

void j1Element::OnRelease()
{

}

void j1Element::Dragging()
{

}
