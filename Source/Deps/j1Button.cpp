#include "j1App.h"
#include "GUIElements.h"

#include "j1Input.h"
#include "GUI.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1EntityPlayer.h"


j1Button::j1Button() {
	this->type = GUItype::GUI_BUTTON;
}

j1Button::~j1Button() {

}

bool j1Button::Start()
{
	if (textureType == Texture::BUTON) {
		texture = App->gui->LoadTexture(Texture::BUTON);
		textureHover = App->gui->LoadTexture(Texture::BUTON_HOVER);
	}

	if (textureType == Texture::OPTIONS)
		texture = App->gui->LoadTexture(Texture::OPTIONS);

	if (textureType == Texture::NEXT)
		texture = App->gui->LoadTexture(Texture::NEXT);

	if (textureType == Texture::PREV)
		texture = App->gui->LoadTexture(Texture::PREV);

	if (textureType == Texture::SCROLL)
		texture = App->gui->LoadTexture(Texture::SCROLL);

	if (textureType == Texture::LINK)
		texture = App->gui->LoadTexture(Texture::LINK);
	
	if (textureType == Texture::BOTON_SCROLL)
		texture = App->gui->LoadTexture(Texture::BOTON_SCROLL);
	
	if (textureType == Texture::INFO)
		texture = App->gui->LoadTexture(Texture::INFO);
	
	if (textureType == Texture::LVLUP)
		texture = App->gui->LoadTexture(Texture::LVLUP);

	if (text != nullptr)
		label = App->gui->AddElement(GUItype::GUI_LABEL, this, mapPosition, insidePosition, true, true, { 0,0,0,0 }, text);

	return true;
}

bool j1Button::PreUpdate()
{
	if (label != nullptr)
		label->enabled = enabled;

	above = OnAbove();

	return true;
}

bool j1Button::Update(float dt)

{
	if (interactable)
	{
		if (above)
		{
			App->gui->disableClick = true;
			if (App->input->GetMouseButton(1) == j1KeyState::KEY_DOWN)
				OnClick();

			if (App->input->GetMouseButton(3) == j1KeyState::KEY_DOWN)
				OnLeftClick();

			if (App->input->GetMouseButton(1) == j1KeyState::KEY_REPEAT)
			{
				if (X_drag || Y_drag)
					dragging = true;

				if(textureType != Texture::BUTON && textureType != Texture::OPTIONS && textureType != Texture::BOTON_SCROLL)
				App->render->Blit(textureClick, mapPosition.x, mapPosition.y, &rect);

				iPoint mouseClick = { 0,0 };
				App->input->GetMousePosition(mouseClick.x, mouseClick.y);
				drag = { mouseClick.x - ((int)this->mapPosition.x), mouseClick.y - ((int)this->mapPosition.y) };

			}

		}

		if (dragging) 
		{

			if (App->input->GetMouseButton(1) == j1KeyState::KEY_IDLE || App->input->GetMouseButton(1) == j1KeyState::KEY_UP)
				dragging = false;
			else
			{
				Dragging();
				MovingIt(dt);
			}
		}
	}

	if (enabled) 
	{
		if (textureType == Texture::BUTON) 
		{
			if (above && interactable)
			{
				SDL_Rect temp = { 0,0,220,72 };
				App->render->Blit(textureHover, mapPosition.x - 10, mapPosition.y -3, &temp);
			}
			else {
				App->render->Blit(texture, mapPosition.x, mapPosition.y, &rect);
			}
		}

		else if (textureType == Texture::BOTON_SCROLL) 
		{

			//LIMITING THE SCROLL BAR BUTTON VISUALY
			if (insidePosition.x > 0) {
				App->render->Blit(texture, mapPosition.x + insidePosition.x, mapPosition.y, &rect);
			}
			else if (insidePosition.x < -235) {
				App->render->Blit(texture, mapPosition.x + insidePosition.x + 235, mapPosition.y, &rect);
			}
			else 
				App->render->Blit(texture, mapPosition.x , mapPosition.y, &rect);
		}
		else
		{
			App->render->Blit(texture, mapPosition.x, mapPosition.y, &rect);

		}

		if (above && textureType != Texture::BUTON && textureType != Texture::OPTIONS && textureType != Texture::BOTON_SCROLL && App->input->GetMouseButton(1) != j1KeyState::KEY_REPEAT) {
			App->render->Blit(textureHover2, mapPosition.x, mapPosition.y, &rect);
		}

	}

	return true;
}

bool j1Button::PostUpdate()
{
	if(label != nullptr)
	label->mapPosition = mapPosition;

	return true;
}

bool j1Button::CleanUp()
{
	return true;
}

void j1Button::Dragging()
{

}

void j1Button::MovingIt(float dt)
{

	iPoint mouse_pos = { 0,0 };
	App->input->GetMousePosition(mouse_pos.x, mouse_pos.y);

	fPoint currentPos = this->mapPosition;


	if (X_drag)
		this->mapPosition.x += ((mouse_pos.x - this->mapPosition.x) - drag.x);

	if (Y_drag)
		this->mapPosition.y += ((mouse_pos.y - this->mapPosition.y) - drag.y);


	if (parent != nullptr)
	{
		if (X_drag)
			this->insidePosition.x += currentPos.x - this->mapPosition.x;

		if (Y_drag)
			this->insidePosition.y += currentPos.y - this->mapPosition.y;

		if (X_drag)
			this->mapPosition.x = parent->mapPosition.x - insidePosition.x;

		if (Y_drag)
			this->mapPosition.y = parent->mapPosition.y - insidePosition.y;
	}

}

void j1Button::OnRelease()
{

}
