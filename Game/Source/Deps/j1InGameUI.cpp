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

	uint tempWidth = 0;
	uint tempHeight = 0;
	App->win->GetWindowSize(tempWidth, tempHeight);

	MiddleScreenW = tempWidth /2 - 100;
	MiddleScreenH = tempHeight / 2 - 100;

	width = tempWidth;

	selected_offset = 0;
	selected_total = 0;

	//CREATES UI
	AddUI();

	return true;
}

bool j1InGameUI::PreUpdate()
{

	return true;
}

bool j1InGameUI::Update(float dt)
{
	selected_last_frame = selected;

	sprintf_s(coins_t, 10, "%7d", coins);

	//MENU FROM ESC
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == j1KeyState::KEY_DOWN && App->sceneManager->GetCurrentScene() != 0) {
	//	Activate_Win_Menu();
	//	Activate_Defeat_Menu();
		ActivateMenu();
	}
	////////////////////////////////////////////////////

	//MANAGE GODMODE UI
	if (App->sceneManager->GetCurrentScene() != 0) {
		if(App->manager->godMode == true){
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

	return true;
}

bool j1InGameUI::CleanUp()
{
	selected = nullptr;
	return true;

}

//UI FUNCTIONS
void j1InGameUI::AddUI()
{
	//MENU
	//menu.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { MiddleScreenW - 50,0 }, { 0,0 }, true, false, { 0, 0,350,500 },"", this, false, false, ScrollType::SCROLL_NONE, true, Texture::IMAGE);
	////menu.Menu_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, {width -50,10 }, { 0,0 }, true, true, { 0,0,40,40 }, "", this,false, false, ScrollType::SCROLL_NONE,true, Texture::OPTIONS);
	//menu.Return_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH-140 }, { 70,30 }, true, false, { 0,0,200,65 }, "RESUME", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	//menu.Resume_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH}, { 74,30 }, true, false, { 0,0,200,65 }, "SAVE", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	//menu.Exit_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH + 15 }, {60,30 }, true, false, { 0,0,200,65 }, "FULLSCREEN", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	//menu.Save = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH +90 }, { 70,30 }, true, false, { 0,0,200,65 }, "QUIT", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	//menu.Load = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH +165}, { 50,30 }, true, false, { 0,0,200,65 }, "MAIN MENU", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);

	//WIN
	win.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, {600 - 150,225  }, { 0,0 }, true, false, { 0, 0,350,170 }, "", this, false, false, ScrollType::SCROLL_NONE, true, Texture::MANAGER_IMAGE);
	win.Label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, {750 - 150, 280 }, { 0,0 }, true, false, { 0,0,40,40 }, "VICTORY!!", this, false, false, ScrollType::SCROLL_NONE,true);
	win.Back_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, {680 - 150,315 }, { 65,30 }, true, false, { 0,0,200,65 }, "MAIN MENU", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);

	//DEFEAT
	defeat.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { 600 - 150,225 }, { 0,0 }, true, false, { 0, 0,350,170 }, "", this, false, false, ScrollType::SCROLL_NONE, true, Texture::MANAGER_IMAGE);
	defeat.Label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, { 750 - 150, 280 }, { 0,0 }, true, false, { 0,0,40,40 }, "DEFEAT", this, false, false, ScrollType::SCROLL_NONE, true);
	defeat.Back_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 680 - 150,315 }, { 65,30 }, true, false, { 0,0,200,65 }, "MAIN MENU", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);

	//GODMODE
	godmode.Godmode_Label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, { 425, 18 }, { 0,0 }, true, true, { 0,0,40,40 }, "GOD MODE ACTIVATED!", this, false, false, ScrollType::SCROLL_NONE, true);
	godmode.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { 410,03 }, { 0,0 }, true, false, { 0, 0,145,40 }, "", this, false, false, ScrollType::SCROLL_NONE, true, Texture::GODMODE);
}

void j1InGameUI::ActivateMenu()
{
	/*menu.Resume_button->enabled = !menu.Resume_button->enabled;
	
	menu.Return_button->enabled = !menu.Return_button->enabled;
	menu.Exit_button->enabled = !menu.Exit_button->enabled;
	menu.Load->enabled = !menu.Load->enabled;
	menu.Save->enabled = !menu.Save->enabled;

	menu.Image->enabled = !menu.Image->enabled;
	menu.Image->mapPosition = {(float)App->render->camera.x, (float)App->render->camera.y };

	App->gamePause = !App->gamePause;*/
}

void j1InGameUI::GUIEeventManager(GUIEvent type, j1Element* element)
{
	switch (type)
	{

	case GUIEvent::EVENT_ONCLICK:
	{
		//App->audio->PlayFx(App->audio->ui_wood_hit);
		if (element == menu.Return_button) {
			ActivateMenu();
		}
		if (element == menu.Exit_button) {
			App->win->Fullscreen();
		}

		if (element == menu.Save) {
			quit = true;
			App->SaveGame();
		}
		if (element == menu.Load) {
			App->SaveGame();
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
			ActivateMenu();
			App->SaveGame();
		}
		if (element == menu.Menu_button) {
			
			ActivateMenu();
		}

	}
	break;
	case GUIEvent::EVENT_LEFTCLICK:
		
		break;

	case GUIEvent::EVENT_HOVER:
		break;
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

}

void j1InGameUI::Deactivate_Information()
{

}


void j1InGameUI::Deactivate_All_UI()
{
	menu.Resume_button->enabled = false;
	menu.Return_button->enabled = false;
	menu.Exit_button->enabled = false;
	menu.Load->enabled = false;
	menu.Save->enabled = false;
	menu.Image->enabled = false;

	menu.Menu_button->enabled = false;
}

void j1InGameUI::Activate_Necessary_UI() {
	menu.Menu_button->enabled = true;
}