#include "j1App.h"
#include "GUI.h"

#include "j1Render.h"
#include "j1Textures.h"
#include "Font.h"
#include "j1Input.h"
//#include "j1MainMenuUI.h"

j1GUI::j1GUI() : j1Module()
{
	name.create("gui");
}

// Destructor
j1GUI::~j1GUI()
{}

bool j1GUI::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}

bool j1GUI::Start()
{
	return true;
}

bool j1GUI::PreUpdate()
{
	bool ret = true;
	p2List_item<j1Element*>* tmp = GUIElements.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->PreUpdate();
		tmp = tmp->next;
	}

	return ret;
}

bool j1GUI::Update(float dt)
{
	s = s + 0.010;

	bool ret = true;
	p2List_item<j1Element*>* tmp = GUIElements.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->Update(dt);
		tmp = tmp->next;
	}

	return ret;
}

bool j1GUI::PostUpdate()
{
	bool ret = true;

	p2List_item<j1Element*>* tmp = GUIElements.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->PostUpdate();
		tmp = tmp->next;
	}
	return ret;

}

bool j1GUI::CleanUp()
{
	LOG("Freeing GUI");

	for (p2List_item<j1Element*>* item = GUIElements.start; item; item = item->next)
	{
		item->data->CleanUp();
	}
	GUIElements.clear();
	return true;
}

void j1GUI::MoveUIElements(float x, float y, j1Element* element)
{
	element->mapPosition.x = element->mapPosition.x + x;
	element->mapPosition.y = element->mapPosition.y + y;
}

bool j1GUI::CorrectX(int x)
{
	if (x <= 540)
		return false;
	else
		return true;
}

bool j1GUI::CorrectY(int y, int y_1)
{
	if (y < y_1)
		return false;
	else
		return true;
}

void j1GUI::Spining_UI()
{
	//if (!Correct_x(App->mainmenu->menu.continue_button->map_position.x))
	//{
	//	Move_Ui_Element(4 - s, 0, App->mainmenu->menu.continue_button);
	//}

	//if (!Correct_x(App->mainmenu->menu.start->map_position.x))
	//{
	//	Move_Ui_Element(4 - s, 0, App->mainmenu->menu.start);
	//}

	//if (!Correct_x(App->mainmenu->menu.audio_button->map_position.x))
	//{
	//	Move_Ui_Element(4 - s, 0, App->mainmenu->menu.audio_button);
	//}

	//if (!Correct_x(App->mainmenu->menu.fullscreen->map_position.x))
	//{
	//	Move_Ui_Element(4 - s, 0, App->mainmenu->menu.fullscreen);
	//}

	//if (!Correct_x(App->mainmenu->menu.instructions->map_position.x))
	//{
	//	Move_Ui_Element(4 - s, 0, App->mainmenu->menu.instructions);
	//}

	//if (!Correct_x(App->mainmenu->menu.quit->map_position.x))
	//{
	//	Move_Ui_Element(4 - s, 0, App->mainmenu->menu.quit);
	//}

	//if (!Correct_y(App->mainmenu->menu.continue_button->map_position.y, 215))
	//	Move_Ui_Element(0, 4 - s, App->mainmenu->menu.continue_button);

	//if (!Correct_y(App->mainmenu->menu.start->map_position.y, 300))
	//	Move_Ui_Element(0, 4 - s, App->mainmenu->menu.start);

	//if (!Correct_y(App->mainmenu->menu.audio_button->map_position.y, 385))
	//	Move_Ui_Element(0, 4 - s, App->mainmenu->menu.audio_button);

	//if (!Correct_y(App->mainmenu->menu.fullscreen->map_position.y, 470))
	//	Move_Ui_Element(0, 4 - s, App->mainmenu->menu.fullscreen);

	//if (!Correct_y(App->mainmenu->menu.instructions->map_position.y, 550))
	//	Move_Ui_Element(0, 4 - s, App->mainmenu->menu.instructions);

	//if (!Correct_y(App->mainmenu->menu.quit->map_position.y, 640))
	//	Move_Ui_Element(0, 4 - s, App->mainmenu->menu.quit);
}

void j1GUI::Reset_UI_Pos()
{
	s = 0;
	/*App->mainmenu->menu.continue_button->map_position.x = 0;
	App->mainmenu->menu.start->map_position.x = 0;
	App->mainmenu->menu.quit->map_position.x = 0;
	App->mainmenu->menu.audio_button->map_position.x = 0;
	App->mainmenu->menu.fullscreen->map_position.x = 0;
	App->mainmenu->menu.instructions->map_position.x = 0;

	App->mainmenu->menu.continue_button->map_position.y = 0;
	App->mainmenu->menu.start->map_position.y = 0;
	App->mainmenu->menu.quit->map_position.y = 0;
	App->mainmenu->menu.audio_button->map_position.y = 0;
	App->mainmenu->menu.fullscreen->map_position.y = 0;
	App->mainmenu->menu.instructions->map_position.y = 0;*/
}

SDL_Texture* j1GUI::LoadTexture(Texture textureType)
{
	switch (textureType)
	{
	case Texture::BUTON:
		textureLoad = App->tex->Load("Assets/textures/ui/button.png");
		break;
	case Texture::IMAGE:
		textureLoad = App->tex->Load("Assets/textures/ui/image.png");
		break;
	case Texture::MANAGER_IMAGE:
		textureLoad = App->tex->Load("Assets/textures/ui/manager_image.png");
		break;
	case Texture::NEXT:
		textureLoad = App->tex->Load("Assets/textures/ui/next.png");
		break;
	case Texture::PREV:
		textureLoad = App->tex->Load("Assets/textures/ui/prev.png");
		break;
	case Texture::OPTIONS:
		textureLoad = App->tex->Load("Assets/textures/ui/options.png");
		break;
	case Texture::BUTON_HOVER:
		textureLoad = App->tex->Load("Assets/textures/ui/button_1.png");
		break;
	case Texture::MAIN_IMAGE:
		textureLoad = App->tex->Load("Assets/textures/ui/ui_image.png");
		break;
	case Texture::RESOURCES_IMAGE:
		textureLoad = App->tex->Load("Assets/textures/ui/resources.png");
		break;
	case Texture::SCROLL:
		textureLoad = App->tex->Load("Assets/textures/ui/scroll.png");
		break;
	case Texture::BOTON_SCROLL:
		textureLoad = App->tex->Load("Assets/textures/ui/scroll_button.png");
		break;
	case Texture::AUDIO_IMAGE:
		textureLoad = App->tex->Load("Assets/textures/ui/audio-image.png");
		break;
	case Texture::GODMODE:
		textureLoad = App->tex->Load("Assets/textures/ui/godmode.png");
		break;
	case Texture::INFO:
		textureLoad = App->tex->Load("Assets/textures/ui/info.png");
		break;
	case Texture::INFO_IMAGE:
		textureLoad = App->tex->Load("Assets/textures/ui/info_image.png");
		break;
	case Texture::COIN:
		textureLoad = App->tex->Load("Assets/textures/ui/coin.png");
		break;
	case Texture::EXPLANATION:
		textureLoad = App->tex->Load("Assets/textures/ui/explanation.png");
		break;
	}
	return textureLoad;
}

j1Element* j1GUI::AddElement(GUItype type, j1Element* parent, fPoint mapPosition, fPoint insidePosition, bool interactable, bool enabled, SDL_Rect section, char* text, j1Module* listener, bool X_drag, bool Y_drag, ScrollType scrollType, bool decor, Texture textureType)
{
	j1Element* temp = nullptr;

	switch (type)
	{
	case GUItype::GUI_BUTTON:
		temp = new j1Button();
		break;
	case GUItype::GUI_INPUTBOX:
		temp = new j1InputBox(text);
		break;
	case GUItype::GUI_LABEL:
		temp = new j1Label();
		break;
	case GUItype::GUI_IMAGE:
		temp = new j1Image();
		break;
	case GUItype::GUI_SCROLLBAR:
		temp = new j1ScrollBar(scrollType);
		break;
	}

	if (temp)
	{
		temp->parent = parent;
		temp->mapPosition = mapPosition;
		temp->insidePosition = insidePosition;
		temp->listener = listener;
		temp->interactable = interactable;
		temp->X_drag = X_drag;
		temp->Y_drag = Y_drag;
		temp->decorative = decor;
		temp->enabled = enabled;
		temp->rect = section;
		temp->text = text;
		temp->textureType = textureType;

                                                                                                                                                                                                    		GUIElements.add(temp)->data->Start();
	}
	return temp;
}

bool j1GUI::Save(pugi::xml_node& file) const {

	return true;
}

bool j1GUI::Load(pugi::xml_node& file) {

	return true;
}

void j1GUI::UpdatePosition(j1Element* element, fPoint position, fPoint localPosition) {
	element->mapPosition = position;
	element->insidePosition = localPosition;
}