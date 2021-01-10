#ifndef __j1MAINMENUUI_H__
#define __j1MAINMENUUI_H__

#include "j1Module.h"
#include "SDL/include/SDL_rect.h"
#include <vector>

struct MainMenu {

	j1Element* continueButton;
	j1Element* start;
	j1Element* quit;
	j1Element* audioButton;
	j1Element* fullscreen;
	//j1Element* music_label;
	//j1Element* music;
	//j1Element* fx_label;
	//j1Element* fx;
	//j1Element* audio_image;
	j1Element* link;
	j1Element* instructions;
};


class j1MainMenuUI : public j1Module
{
public:
	j1MainMenuUI();
	~j1MainMenuUI();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void AddUI();
	void ActivateMenu();
	void DeactivateMenu();
	void ActivateAudioOptions();
	void DeactivateAudioOptions();
	void GUIEeventManager(GUIEvent type, j1Element* element);
	MainMenu GetMenu();
	bool clickingUi = false;
	MainMenu menu;
	int sceneNumber = 0;

private:
	bool quit = true;
	bool audioopt = false;

};

#endif // __j1MAINMENUUI_H__