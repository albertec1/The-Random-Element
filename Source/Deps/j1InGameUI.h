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

struct Unit_Manager_UI {
	j1Element* button_next;
	j1Element* buton_prev;
	j1Element* image;
	j1Element* entity_type_Image;
	j1Element* info;
};

struct In_Game_Basics {
	j1Element* Image;
};


struct Trading_Menu_Selected {
	j1Element* Scroll;
	j1Element* Scroll_1;
	j1Element* Scroll_2;
	j1Element* back;
};

struct CoinCost {
	j1Element* Image;
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

struct Entity_UI {
	j1Element* name;
	j1Element* image;
	j1Element* trade;
	j1Element* button_1 = nullptr;
	j1Element* button_2 = nullptr;
	j1Element* button_3 = nullptr;
	j1Element* button_4 = nullptr;
	j1Element* button_5 = nullptr;
};

struct Information {
	j1Element* Image;
	j1Element* Text;
	j1Element* Health;
	j1Element* Attack;
	j1Element* Max_resource;
	j1Element* Speed;

	char health_text[10];
	char attack_text[10];
	char max_resource_text[10];
	char speed_text[10];

	int health;
	int max_health;
	int attack;
	int speed;
	int max_resource;
	bool in_info = false;
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

	void Add_UI();
	void Deactivate_All_UI();
	void Activate_Necessary_UI();
	void Activate_Menu();

	//WIN
	void Activate_Win_Menu();
	void Deactivate_Win_Menu();

	//DEFEAT
	void Activate_Defeat_Menu();
	void Deactivate_Defeat_Menu();

	//INFORMATION
	void Activate_Information();
	void Deactivate_Information();

	//BAR UPDATES
	void Update_Bar(j1Element* scroll, float resource, float total_resource, Material material);

	void Activate_Manager();
	void Deactivate_Manager();

	void GUI_Event_Manager(GUI_Event type, j1Element* element);

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
	Unit_Manager_UI manager;
	In_Game_Basics basics;
	Win win;
	Defeat defeat;
	GodMode godmode;
	Information information;
	CoinCost coincost;
	
	Entity_UI entity_ui;

	j1Element* Trader_image;
	j1Element* Trader_label;
	j1Element* coin_image;
	int selected_offset;
	int offset_modifier;
	int selected_total;

	bool in_trading = false;
	bool in_trader = false;
	int font_name = -1;
	bool quit = false;

	j1Entity* selected_last_frame;
};

#endif // __j1WINDOW_H__