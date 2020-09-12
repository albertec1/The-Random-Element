#pragma once

#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1Timer.h"

// Forward declaration of every module
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Map;
class j1SceneManager;
class j1Collision;
class j1EntityManager;
//---

class j1App
{
public:

	j1App(int argc, char* args[]);
	virtual ~j1App();

	bool Awake();
	bool Start();
	bool Update();
	bool CleanUp();

	// Add a new module 
	void AddModule(j1Module* module);

	// Expose some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	//Save andl load methods
	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void GetSaveGames(p2List<p2SString>& list_to_fill) const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SaveGameNow() const;

public:

	//Modules:
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Map*				map;
	j1SceneManager*		scene_manager;
	j1Collision*		coll;
	j1EntityManager*	manager;
	//-----
private:

	p2List<j1Module*>	modules;
	uint				frames;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	p2SString			load_game;
	mutable p2SString	save_game;

	//Timer----
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint				last_sec_frame_count = 0;
	uint				prev_last_sec_frame_count = 0;

public: 

	float				frame_count;
	float				dt;
	bool				allow_debug_log;
};

extern j1App* App;