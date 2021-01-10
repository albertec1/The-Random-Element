#include "GUIElements.h"
#include "GUI.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Window.h"

j1InputBox::j1InputBox(char* text)
{
	this->type = GUItype::GUI_INPUTBOX;

}

j1InputBox::~j1InputBox() {

}

bool j1InputBox::Start()
{
	string = App->gui->AddElement(GUItype::GUI_LABEL, this, mapPosition, { 0,3 }, true, enabled, { (int)insidePosition.x, (int)insidePosition.y, 50, 0 }, text);
	return true;
}


bool j1InputBox::PreUpdate()
{
	string->enabled = enabled;

	if (focus)
	{
		App->input->EnableTextInput();
	}

	else if (!focus)
		App->input->DisableTextInput();

	above = OnAbove();

	return true;
}

bool j1InputBox::Update(float dt)
{

	if (above)
	{
		if (App->input->GetMouseButton(1) == j1KeyState::KEY_DOWN)
			OnClick();
	}
	else {
		if (App->input->GetMouseButton(1) == j1KeyState::KEY_DOWN)
			focus = false;
	}


	return true;
}

bool j1InputBox::PostUpdate()
{
	if (enabled) {
		Draw();

		if (focus)
		{
			SDL_Rect rect = { (string->mapPosition.x + string->rect.w) * App->win->GetScale() , (string->mapPosition.y + insidePosition.y) * App->win->GetScale(), 2,  string->rect.h + 10 };
			App->render->DrawQuad(rect, 255, 255, 255, 255, true, false);
		}
	}


	return true;
}

bool j1InputBox::CleanUp()
{
	return true;
}

void j1InputBox::OnClick()
{
	focus = true;

}

void j1InputBox::OnRelease()
{

}


