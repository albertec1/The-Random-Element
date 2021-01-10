#ifndef __j1INGAMEUI_H__
#define __j1INGAMEUI_H__

#include "j1Module.h"
#include "j1Entity.h"
#include "SDL/include/SDL_rect.h"
#include <vector>

struct Game_Menu {
	j1Element* Menu_button;
	j1Element* Title;
	j1Element* Image;
	j1Element* Exit_button;
	j1Element* Return_button;
	j1Element* Resume_button;
	j1Element* Save;
	j1Element* Load;
};

struct Win {
	j1Element* Label;
	j1Element* Image;
	j1Element* Back_button;
};

struct Defeat {
	j1Element* Label;
	j1Element* Image;
	j1Element* Back_button;
};

struct GodMode {
	j1Element* Godmode_Label;
	j1Element* Image;
};

struct SDL_Texture;
class j1Entity;

class j1InGameUI : public j1Module
{
public:

	j1InGameUI();
	~j1InGameUI();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void AddUI();
	void Deactivate_All_UI();
	void Activate_Necessary_UI();
	void ActivateMenu();

	//WIN
	void Activate_Win_Menu();
	void Deactivate_Win_Menu();

	//DEFEAT
	void Activate_Defeat_Menu();
	void Deactivate_Defeat_Menu();

	//INFORMATION
	void Activate_Information();
	void Deactivate_Information();

	void GUIEeventManager(GUIEvent type, j1Element* element);

	//COINS
	int coins = 0;
	char coins_t[10];

	j1Entity* selected = nullptr;

private:
	//positions
	float MiddleScreenW;
	float MiddleScreenH;
	int tradepos_x = 0;
	int tradepos_y = 0;
	float width;
	
	//RESOURCES 
	int type_0 = 0;
	int type_1 = 0;
	int type_2 = 0;

	char wood_resource[10];
	char cotton_resource[10];
	char metal_resource[10];

	char text_max[10];
	char text_type_0[10];
	char text_type_1[10];
	char text_type_2[10];

	//COST
	int wood = 0;
	int cotton = 0;
	int metal = 0;
	
	char wood_t[10];
	char cotton_t[10];
	char metal_t[10];

	int coin_cost = 0;
	char coin_cost_t[10];

	bool in_hover = false;
	bool in_hover_info = false;
	bool in_hover_coin_cost = false;
	bool in_townhall = false;
	bool in_quest_manager = false;
	//menu ui
	Game_Menu menu;

	Win win;
	Defeat defeat;
	GodMode godmode;


	j1Element* Trader_image;
	j1Element* Trader_label;
	j1Element* coin_image;
	int selected_offset;
	int offset_modifier;
	int selected_total;

	bool in_trading = false;
	bool in_trader = false;
	int fontName = -1;
	bool quit = false;

	j1Entity* selected_last_frame;
};

#endif // __j1WINDOW_H__