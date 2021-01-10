#include "GUIElements.h"
#include "GUI.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Input.h"
//#include "j1Audio.h"


j1ScrollBar::j1ScrollBar(ScrollType TypeInput) {

	this->type = GUItype::GUI_SCROLLBAR;
	type = TypeInput;
}

j1ScrollBar::~j1ScrollBar() {

}

bool j1ScrollBar::Start()
{
	button = App->gui->AddElement(GUItype::GUI_BUTTON, this, mapPosition, insidePosition, true, true, { 0, 0, 25 , 25 }, nullptr, this->listener, true, false, ScrollType::SCROLL_NONE, true, Texture::BOTON_SCROLL);
	
	button->mapPosition.y = mapPosition.y - button->rect.h / 2 + this->rect.h / 2;
	value = 0;

	if (textureType == Texture::SCROLL)
		texture = App->gui->LoadTexture(Texture::SCROLL);

	return true;
}

bool j1ScrollBar::PreUpdate()
{

	button->enabled = enabled;
	above = OnAbove();

	return true;
}

bool j1ScrollBar::Update(float dt)
{
	if (interactable) {
		if (above)
		{
			if (App->input->GetMouseButton(1) == j1KeyState::KEY_DOWN)
				OnClick();
		}
		
	}
	if (enabled == true)
		App->render->Blit(texture, mapPosition.x, mapPosition.y, &rect);	

	floatValue = -((float(-button->insidePosition.x) / (float(-this->rect.w) + float(button->rect.w))) * 100);
	value = -((float(-button->insidePosition.x) / (float(-this->rect.w) + float(button->rect.w)))*100);
	return true;
}

bool j1ScrollBar::PostUpdate()
{
	ScrollLimits();
	return true;
}

bool j1ScrollBar::CleanUp()
{
	return true;
}

void j1ScrollBar::ScrollLimits() 
{

	if (button->insidePosition.x > 0)
	{
		button->insidePosition.x = 0;

		button->mapPosition.x = button->parent->mapPosition.x + button->insidePosition.x;

	}
	else if (button->insidePosition.x < (-this->rect.w + button->rect.w))
	{
		button->insidePosition.x = -this->rect.w + button->rect.w;

		button->mapPosition.x = button->parent->mapPosition.x - button->insidePosition.x;

	}
}
