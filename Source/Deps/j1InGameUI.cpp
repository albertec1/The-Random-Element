#include "j1App.h"
#include "j1InGameUI.h"
#include "j1Window.h"
#include "GUI.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1EntityManager.h"
#include "j1Entity.h"
#include "j1SceneManager.h"
#include "j1MainMenuUI.h"
//#include "j1TransitionManager.h"
#include "Font.h"
#include <vector>
#include <iostream>

j1InGameUI::j1InGameUI() : j1Module()
{

	name.create("InGameUI");
}

j1InGameUI::~j1InGameUI()
{

}

bool j1InGameUI::Awake(pugi::xml_node& config)
{

	return true;
}

bool j1InGameUI::Start()
{

	type_0 = 0;
	type_1 = 0;
	type_2 = 0;

	MiddleScreenW = App->win->width/2 - 100;
	MiddleScreenH = App->win->height/ 2 - 100;

	width = App->win->width;

	selected_offset = 0;
	selected_total = 0;

	//CREATES UI
	Add_UI();

	return true;
}

bool j1InGameUI::PreUpdate()
{

	return true;
}

bool j1InGameUI::Update(float dt)
{
	selected_last_frame = selected;


	//COST_UPDATE
	if (in_hover == true) {
		sprintf_s(cotton_t, 10, "%7d", cotton);
		sprintf_s(wood_t, 10, "%7d", wood);
		sprintf_s(metal_t, 10, "%7d", metal);
	}

	//COIN COST UPDATE
	if (in_hover_coin_cost == true) {
		sprintf_s(coin_cost_t, 10, "%7d", coin_cost);
	}
	
	sprintf_s(coins_t, 10, "%7d", coins);

	//MENU FROM ESC
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == j1KeyState::KEY_DOWN && App->scene_manager->GetCurrentScene() != 0) {
	//	Activate_Win_Menu();
	//	Activate_Defeat_Menu();
		Activate_Menu();
	}


	//MANAGE COST MENU
	/////////////////////////////////////////////////
	if(in_hover == false)
	Deactivate_Cost_Menu();

	if (in_hover_info == false)
	Deactivate_Information();

	if (in_hover_coin_cost == false)
	Deactivate_Coin_Cost();

	in_hover_coin_cost = false;
	in_hover_info = false;
	in_hover = false;
	////////////////////////////////////////////////////

	//MANAGE GODMODE UI
	if (App->scenemanager->In_Main_Menu == false) {
		if(App->godmode == true){
			godmode.Godmode_Label->enabled = true;
			godmode.Image->enabled = true;
		}
		else {
		godmode.Godmode_Label->enabled = false;
			godmode.Image->enabled = false;
		}
	}
	else {
		godmode.Godmode_Label->enabled = false;
		godmode.Image->enabled = false;
	}
	


	//MANAGE THE INFO BUTTTON 
	//TEMPORAL FIX
	///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
	if (in_trading == true)
		manager.info->enabled = false;
	///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////


	in_townhall = false;

	if (selected != nullptr) {
		if(selected->type != EntityType::CARRIER )
		Deactivate_Carrier_Cap();
	}

	if (selected_total == 0) 
		Deactivate_Carrier_Cap();

	return true;
}

bool j1InGameUI::CleanUp()
{
	selected = nullptr;
	return true;

}

//UI FUNCTIONS
void j1InGameUI::Add_UI()
{
	//MENU
	menu.Menu_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, {width -50,10 }, { 0,0 }, true, true, { 0,0,40,40 }, "", this,false, false, SCROLL_TYPE::SCROLL_NONE,true, TEXTURE::OPTIONS);
	menu.Return_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH-140 }, { 70,30 }, true, false, { 0,0,200,65 }, "RESUME", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Resume_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH -60}, { 74,30 }, true, false, { 0,0,200,65 }, "SAVE", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Exit_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH + 15 }, {60,30 }, true, false, { 0,0,200,65 }, "FULLSCREEN", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Save = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH +90 }, { 70,30 }, true, false, { 0,0,200,65 }, "QUIT", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Load = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH +165}, { 50,30 }, true, false, { 0,0,200,65 }, "MAIN MENU", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { MiddleScreenW - 50,0 }, { 0,0 }, true, false, { 0, 0,350,500 },"", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::IMAGE);

	//UI BASICS ALWAYS ACTIVE
	basics.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, {0,520 }, { 0,0 }, true, true, { 0, 0,1280,200 }, "", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::MAIN_IMAGE);
	
	//WIN
	win.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, {600 - 150,225  }, { 0,0 }, true, false, { 0, 0,350,170 }, "", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::MANAGER_IMAGE);
	win.Label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, {750 - 150, 280 }, { 0,0 }, true, false, { 0,0,40,40 }, "VICTORY!!", this, false, false, SCROLL_TYPE::SCROLL_NONE,true);
	win.Back_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, {680 - 150,315 }, { 65,30 }, true, false, { 0,0,200,65 }, "MAIN MENU", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);

	//DEFEAT
	defeat.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { 600 - 150,225 }, { 0,0 }, true, false, { 0, 0,350,170 }, "", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::MANAGER_IMAGE);
	defeat.Label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, { 750 - 150, 280 }, { 0,0 }, true, false, { 0,0,40,40 }, "DEFEAT", this, false, false, SCROLL_TYPE::SCROLL_NONE, true);
	defeat.Back_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 680 - 150,315 }, { 65,30 }, true, false, { 0,0,200,65 }, "MAIN MENU", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);

	//GODMODE
	godmode.Godmode_Label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, { 425, 18 }, { 0,0 }, true, true, { 0,0,40,40 }, "GOD MODE ACTIVATED!", this, false, false, SCROLL_TYPE::SCROLL_NONE, true);
	godmode.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { 410,03 }, { 0,0 }, true, false, { 0, 0,145,40 }, "", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::GODMODE);
}

void j1InGameUI::Activate_Menu()
{
	menu.Resume_button->enabled = !menu.Resume_button->enabled;
	menu.Return_button->enabled = !menu.Return_button->enabled;
	menu.Exit_button->enabled = !menu.Exit_button->enabled;
	menu.Load->enabled = !menu.Load->enabled;
	menu.Save->enabled = !menu.Save->enabled;
	menu.Image->enabled = !menu.Image->enabled;
	App->game_pause = !App->game_pause;
}

void j1InGameUI::GUI_Event_Manager(GUI_Event type, j1Element* element)
{
	switch (type)
	{

	case GUI_Event::EVENT_ONCLICK:
	{
		//App->audio->PlayFx(App->audio->ui_wood_hit);
		if (element == menu.Return_button) {
			Activate_Menu();
		}
		if (element == menu.Exit_button) {
			App->win->Fullscreen();
		}

		if (element == menu.Save) {
			quit = true;
			App->SaveGame("save_game.xml");
		}
		if (element == menu.Load) {
			App->SaveGame("save_game.xml");
			//App->transitions->LinesAppearing(Black, 0.75f, 2);
		}

		if (element == win.Back_button) {
			pugi::xml_document save_doc;
			pugi::xml_parse_result result = save_doc.load("save_game.xml");
			save_doc.reset();
			pugi::xml_node node = save_doc.append_child("game");
			//App->transitions->LinesAppearing(Black, 0.75f, 2);
		}

		if (element == defeat.Back_button) {
			pugi::xml_document save_doc;
			pugi::xml_parse_result result = save_doc.load("save_game.xml");
			save_doc.reset();
			pugi::xml_node node = save_doc.append_child("game");
			//App->transitions->LinesAppearing(Black, 0.75f, 2);
		}

		if (element == menu.Resume_button) {
			Activate_Menu();
			App->SaveGame("save_game.xml");
		}
		if (element == menu.Menu_button) {
			
			Activate_Menu();
		}

		if (element == manager.button_next) {

			if (selected_total != 0)
			{
				offset_modifier = -1;
			}

		}

		if (element == manager.buton_prev) {

			if (selected_total != 0)
			{
				offset_modifier = 1;
			}

		}

	}
	break;
	case GUI_Event::EVENT_LEFTCLICK:
		
		break;
	case GUI_Event::EVENT_HOVER:
		
		if (element == manager.info) {
			Activate_Information();
		}

	}	
}

bool j1InGameUI::PostUpdate()
{
	bool ret = true;
	if (quit == true) {
		return false;
	}
	return ret;
}

void j1InGameUI::Activate_Win_Menu()
{
	win.Label->enabled = true;
	win.Back_button->enabled = true;
	win.Image->enabled = true;
}

void j1InGameUI::Deactivate_Win_Menu()
{
	if (win.Label != nullptr)
	{
		win.Label->enabled = false;
			win.Back_button->enabled = false;
			win.Image->enabled = false;
	}
}

void j1InGameUI::Activate_Defeat_Menu()
{
	defeat.Back_button->enabled = true;
	defeat.Image->enabled = true;
	defeat.Label->enabled = true;

}

void j1InGameUI::Deactivate_Defeat_Menu()
{ 
	defeat.Back_button->enabled = false;
	defeat.Image->enabled = false;
	defeat.Label->enabled = false;
}

void j1InGameUI::Activate_Information()
{
	information.Image->enabled = true;
	information.Text->enabled = true;
	information.Health->enabled = true;
	information.Attack->enabled = true;
	information.Speed->enabled = true;
	information.Max_resource->enabled = true;
	information.in_info = true;
	in_hover_info = true;
}

void j1InGameUI::Deactivate_Information()
{
	information.Image->enabled = false;
	information.Text->enabled = false;
	information.Health->enabled = false;
	information.Attack->enabled = false;
	information.Speed->enabled = false;
	information.Max_resource->enabled = false;
	information.in_info = false;
	in_hover_info = false;
}


void j1InGameUI::Update_Bar(j1Element* scroll, float resource, float total_resource, Material material)
{
	float percentage = 0;
	percentage = resource / total_resource;

	scroll->Button->inside_position.x = -(235 * percentage);
	switch (material) {
	case Material::COTTON:
		scroll->Button->map_position.x = 126 + (235 * percentage);
		break;
	case Material::WOOD:
		scroll->Button->map_position.x = 126 + (235 * percentage) * 4;
		break;
	case Material::METAL:
		scroll->Button->map_position.x = 126 + (235 * percentage) * 10;
		break;
	}
}

void j1InGameUI::Deactivate_Entity_UI()
{
	entity_ui.image->enabled = false;
	entity_ui.name->enabled = false;
}

void j1InGameUI::Deactivate_Entity_Buttons()
{
	entity_ui.trade->enabled = false;
	
}

void j1InGameUI::Activate_Manager()
{
	if (selected_total > 1)
	{
		manager.button_next->enabled = true;
		manager.buton_prev->enabled = true;
	}
	else
	{
		selected_offset = 0;
	}
	manager.image->enabled = true;
	manager.info->enabled = true;
}

void j1InGameUI::Deactivate_Manager()
{
	manager.button_next->enabled = false;
	manager.buton_prev->enabled = false;
	manager.image->enabled = false;
	manager.info->enabled = false;
}

void j1InGameUI::Deactivate_All_UI()
{
	Deactivate_Manager();
	Deactivate_Resource_Menu();
	Deactivate_Quest_Selector();
	App->quest->Close_Quest_Manager();

	menu.Resume_button->enabled = false;
	menu.Return_button->enabled = false;
	menu.Exit_button->enabled = false;
	menu.Load->enabled = false;
	menu.Save->enabled = false;
	menu.Image->enabled = false;

	in_townhall = false;

	basics.Image->enabled = false;
	menu.Menu_button->enabled = false;
}

void j1InGameUI::Activate_Necessary_UI() {
	basics.Image->enabled = true;
	menu.Menu_button->enabled = true;
	App->quest->Open_Quest_Manager();
}