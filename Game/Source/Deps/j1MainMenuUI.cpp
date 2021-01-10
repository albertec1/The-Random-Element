#include "j1App.h"
#include "j1MainMenuUI.h"
#include "j1Window.h"
#include "GUI.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1EntityManager.h"
#include "j1SceneManager.h"
//#include "TransitionManager.h"
//#include "Audio.h"
#include <vector>
#include <iostream>

#include "j1Scene.h"


j1MainMenuUI::j1MainMenuUI() : j1Module()
{
	name.create("InGameUI");
}


j1MainMenuUI ::~j1MainMenuUI()
{

}

bool j1MainMenuUI::Awake(pugi::xml_node& config)
{

	return true;
}


bool j1MainMenuUI::Start()
{
	AddUI();

	//SETTING AUDIO IN THE CORRECT STARTING VOLUME
	/*menu.music->Button->map_position.x = 830 + 186;
	menu.music->Button->inside_position.x = -186;
	menu.fx->Button->map_position.x = 830 + 186;
	menu.fx->Button->inside_position.x = -186;*/
	
	return true;
}

bool j1MainMenuUI::PreUpdate()
{

	return true;
}

bool j1MainMenuUI::Update(float dt)
{	
	App->sceneManager->DrawBackground();
	App->gui->Spining_UI();
	return true;
}

//UI FUNCTIONS
void j1MainMenuUI::AddUI()
{
	//MENU
	menu.start = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 550,215 }, { 25,10 }, true, false, { 0,0,200,65 }, "START", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	menu.continueButton = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 550,300 }, { 25,10 }, true, false, { 0,0,200,65 }, "CONTINUE", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	//menu.audio_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 550, 385}, { 25,10 }, true, false, { 0,0,200,65 }, "AUDIO OP.", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.fullscreen = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 550,385 }, { 25,10 }, true, false, { 0,0,200,65 }, "F. SCREEN", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	menu.instructions = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 550,470 }, { 25,10 }, true, false, { 0,0,200,65 }, "INSTRUC.", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	menu.quit = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 550,555 }, { 25,10 }, true, false, { 0,0,200,65 }, "QUIT", this, false, false, ScrollType::SCROLL_NONE, true, Texture::BUTON);
	//menu.link = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { 1220,660 }, { 0,0 }, true, false, { 0,0,60,60 }, "REPOSI", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::LINK);
	//AUDIO OPTIONS
	//menu.music = App->gui->AddElement(GUItype::GUI_SCROLLBAR, nullptr, { 820, 330 }, { 0,0 }, false, false, { 0, 0, 260, 7 }, nullptr, this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::SCROLL);
	//menu.music_label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, { 850,300 }, { 0,0 }, true, false, { 0,0,40,40 }, "MUSIC", this, false, false, SCROLL_TYPE::SCROLL_NONE, true);
	//menu.fx = App->gui->AddElement(GUItype::GUI_SCROLLBAR, nullptr, { 820, 410 }, { 0,0 }, false, false, { 0, 0, 260, 7 }, nullptr, this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::SCROLL);
	//menu.fx_label = App->gui->AddElement(GUItype::GUI_LABEL, nullptr, { 850,380 }, { 0,0 }, true, false, { 0,0,40,40 }, "EFFECTS", this, false, false, SCROLL_TYPE::SCROLL_NONE, true);
	//menu.audio_image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, {  800,270 }, { 0,0 }, true, false, { 0, 0,300,200 }, "", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::AUDIO_IMAGE);
}

void j1MainMenuUI::ActivateMenu()
{
	menu.continueButton->enabled = true;
	menu.start->enabled = true;
	//menu.audio_button->enabled = true;
	menu.quit->enabled = true;
	menu.fullscreen->enabled = true;
	//menu.link->enabled = true;
	menu.instructions->enabled = true;
}

void j1MainMenuUI::DeactivateMenu()
{
	menu.continueButton->enabled = false;
	menu.start->enabled = false;
	//menu.audio_button->enabled = false;
	menu.quit->enabled = false;
	menu.fullscreen->enabled = false;
	//menu.link->enabled = false;
	menu.instructions->enabled = false;
}

void j1MainMenuUI::ActivateAudioOptions()
{
	//menu.music->enabled = true;
	//menu.music_label->enabled = true;
	//menu.fx->enabled = true;
	//menu.fx_label->enabled = true;
	//menu.audio_image->enabled = true;
	//audioopt = true;
}

void j1MainMenuUI::DeactivateAudioOptions()
{
	//menu.music->enabled = false;
	//menu.music_label->enabled = false;
	//menu.fx->enabled = false;
	//menu.fx_label->enabled = false;
	//menu.audio_image->enabled = false;
	//audioopt = false;
}

void j1MainMenuUI::GUIEeventManager(GUIEvent type, j1Element* element)
{
	clickingUi = true;
	switch (type)
	{
	case GUIEvent::EVENT_ONCLICK:
	{
		//App->audio->PlayFx(App->audio->ui_wood_hit);
		if (element == menu.continueButton)
		{
			//If previous saved game 
			//pugi::xml_document save_doc;
			//pugi::xml_parse_result result = save_doc.load_file("save_game.xml");
			//if (save_doc.child("game").child("entity_manager").child("entity") != NULL)
			//{
			//	//App->audio->PlayFx(App->audio->start, 0);
			//	//App->transitions->LinesAppearing(Black, 0.75f, 1);
			//	//App->scene->start = true;
			//	//Deactivate_Audio_Options();
			//	App->game_pause = false;
			//	//App->restart = false;
			//}
		}

		if (element == menu.start) 
		{
			//App->audio->PlayFx(App->audio->start, 0);
			//App->transitions->LinesAppearing(Black, 0.75f, 1);
			DeactivateAudioOptions();
			App->gamePause = false;
			App->sceneManager->exitMenu = true;
			//App->restart = true;
		}
			
		if (element == menu.audioButton) 
		{
			if (audioopt == false)
				ActivateAudioOptions();
			else
				DeactivateAudioOptions();
		}

		if (element == menu.fullscreen)
		{
			App->win->Fullscreen();
		}

		if (element == menu.quit) 
		{
			DeactivateAudioOptions();
			quit = false;
		}
		if (element == menu.link)
		{
			ShellExecuteA(NULL, "open", "https://github.com/albertec1/The-random-element", NULL, NULL, SW_SHOWNORMAL);
		}
		if (element == menu.instructions)
		{
			ShellExecuteA(NULL, "open", "https://github.com/albertec1/The-random-element/blob/master/README.md", NULL, NULL, SW_SHOWNORMAL);
		}
	}
	}
}

bool j1MainMenuUI::PostUpdate()
{
	return quit;
}

MainMenu j1MainMenuUI::GetMenu()
{
	return menu;
}