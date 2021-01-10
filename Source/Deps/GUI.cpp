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
	p2List_item<j1Element*>* tmp = GUI_ELEMENTS.start;
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
	p2List_item<j1Element*>* tmp = GUI_ELEMENTS.start;
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

	p2List_item<j1Element*>* tmp = GUI_ELEMENTS.start;
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

	for (p2List_item<j1Element*>* item = GUI_ELEMENTS.start; item; item = item->next)
	{
		item->data->CleanUp();
	}
	GUI_ELEMENTS.clear();
	return true;
}

void j1GUI::Move_Ui_Element(float x, float y, j1Element* element)
{
	element->map_position.x = element->map_position.x + x;
	element->map_position.y = element->map_position.y + y;
}

bool j1GUI::Correct_x(int x)
{
	if (x <= 540)
		return false;
	else
		return true;
}

bool j1GUI::Correct_y(int y, int y_1)
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

SDL_Texture* j1GUI::Load_Texture(TEXTURE textureType)
{
	switch (textureType)
	{
	case TEXTURE::BUTON:
		texture_load = App->tex->Load("textures/ui/button.png");
		break;
	case TEXTURE::IMAGE:
		texture_load = App->tex->Load("textures/ui/image.png");
		break;
	case TEXTURE::MANAGER_IMAGE:
		texture_load = App->tex->Load("textures/ui/manager-image.png");
		break;
	case TEXTURE::NEXT:
		texture_load = App->tex->Load("textures/ui/next.png");
		break;
	case TEXTURE::PREV:
		texture_load = App->tex->Load("textures/ui/prev.png");
		break;
	case TEXTURE::OPTIONS:
		texture_load = App->tex->Load("textures/ui/options.png");
		break;
	case TEXTURE::BUTON_HOVER:
		texture_load = App->tex->Load("textures/ui/button-1.png");
		break;
	case TEXTURE::MAIN_IMAGE:
		texture_load = App->tex->Load("textures/ui/ui-image.png");
		break;
	case TEXTURE::RESOURCES_IMAGE:
		texture_load = App->tex->Load("textures/ui/resources.png");
		break;
	case TEXTURE::SCROLL:
		texture_load = App->tex->Load("textures/ui/scroll.png");
		break;
	case TEXTURE::BOTON_SCROLL:
		texture_load = App->tex->Load("textures/ui/scroll-button.png");
		break;
	case TEXTURE::AUDIO_IMAGE:
		texture_load = App->tex->Load("textures/ui/audio-image.png");
		break;
	case TEXTURE::GODMODE:
		texture_load = App->tex->Load("textures/ui/godmode.png");
		break;
	case TEXTURE::INFO:
		texture_load = App->tex->Load("textures/ui/info.png");
		break;
	case TEXTURE::INFO_IMAGE:
		texture_load = App->tex->Load("textures/ui/info-image.png");
		break;
	case TEXTURE::COIN:
		texture_load = App->tex->Load("textures/ui/coin.png");
		break;
	case TEXTURE::EXPLANATION:
		texture_load = App->tex->Load("textures/ui/explanation.png");
		break;
	}
	return texture_load;
}

j1Element* j1GUI::AddElement(GUItype type, j1Element* parent, fPoint map_position, fPoint inside_position, bool interactable, bool enabled, SDL_Rect section, char* text, j1Module* listener, bool X_drag, bool Y_drag, SCROLL_TYPE scrollType, bool decor, TEXTURE textureType)
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
		temp->map_position = map_position;
		temp->inside_position = inside_position;
		temp->listener = listener;
		temp->interactable = interactable;
		temp->X_drag = X_drag;
		temp->Y_drag = Y_drag;
		temp->decorative = decor;
		temp->enabled = enabled;
		temp->rect = section;
		temp->text = text;
		temp->textureType = textureType;

                                                                                                                                                                                                    		GUI_ELEMENTS.add(temp)->data->Start();
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
	element->map_position = position;
	element->inside_position = localPosition;
}