//#ifndef __j1FADETOBLACK_H__
//#define __j1FADETOBLACK_H__
//
//#include "j1Module.h"
//#include "SDL\include\SDL_rect.h"

//
//class j1FadeToBlack : public j1Module
//{
//public:
//	j1FadeToBlack();
//
//	virtual ~j1FadeToBlack();
//
//	// Called before render is available
//	bool Awake(pugi::xml_node&);
//
//	// Called before the first frame
//	bool Start();
//
//	// Called each loop iteration
//	bool Update();
//
//	// Called before quitting
//	bool CleanUp();
//
//	bool Change_Map(const char* nextMap);
//
//	bool Fade_To_Black(const char* map, float time = 1.5f);
//
//
//private:
//	enum fade_step
//	{
//		none,
//		fade_to_black,
//		fade_from_black
//	} current_step = fade_step::none;
//
//	Uint32 start_time = 0;
//	Uint32 total_time = 0;
//	SDL_Rect screen;
//	const char* map_name;
//
//};
//
//#endif // __j1FADETOBLACK_H__