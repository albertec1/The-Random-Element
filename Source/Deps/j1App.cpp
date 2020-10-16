#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "j1App.h"
#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1SceneManager.h"
#include "j1Collision.h"
#include "j1EntityManager.h"

#include "j1Timer.h"

#include "Brofiler/Brofiler/Brofiler.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	dt = 0;
	frames = 0;
	want_to_save = want_to_load = false;
	save_document_full = false;

	//class Objects are created here
	win =			new j1Window();
	input =			new j1Input();
	render =		new j1Render();
	tex =			new j1Textures();
	map =			new j1Map();
	scene_manager =	new j1SceneManager();
	coll =			new j1Collision();
	manager =		new j1EntityManager();
	//-----

	// AddModule() for every Object created before
	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(map);
	AddModule(scene_manager);
	AddModule(coll);
	AddModule(manager);

	// render last to swap buffer
	AddModule(render);
	//-----
}

j1App::~j1App()
{
	//Release modules
	p2List_item<j1Module*>* item = modules.end;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.add(module);
}

bool j1App::Awake()
{
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;

	config = LoadConfig(config_file);

	if (config.empty() == false)
	{
		//self-config
		ret = true;
		app_config = config.child("app");
		title.create(app_config.child("title").child_value());
		organization.create(app_config.child("organization").child_value());
		allow_debug_log = app_config.child("debug_log").attribute("value").as_bool(true);
	}

	if (ret == true)
	{
		p2List_item<j1Module*>* item;
		item = modules.start;
		
		while (item != NULL && ret == true)
		{
			//ret = Awake the current module->(pass the config child node which shares name with the current module)
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;
	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if (result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());

	else
		ret = config_file.child("config");

	return ret;
}

bool j1App::Start()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	return ret;
}
bool j1App::Update()
{BROFILER_CATEGORY("UpdateApp", Profiler::Color::MediumSpringGreen)
	bool ret = true;
	PrepareUpdate();
	
	if (input->GetWindowEvent(j1WindowEvent::WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();
		
	FinishUpdate();
	return ret;
}

void j1App::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Start();
}

bool j1App::PreUpdate()
{BROFILER_CATEGORY("PreUpdateApp", Profiler::Color::DarkRed)
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
			continue;

		ret = item->data->PreUpdate();
	}

	return ret;
}

bool j1App::DoUpdate()
{BROFILER_CATEGORY("DoUpdateApp", Profiler::Color::Blue)
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
			continue;
		
		ret = item->data->Update(dt);
	}

	return ret;
}

bool j1App::PostUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	j1Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

void j1App::FinishUpdate()
{BROFILER_CATEGORY("FinishApp", Profiler::Color::Aqua)

	if (input->GetKey(SDL_SCANCODE_S) == j1KeyState::KEY_DOWN)
		SaveGame();
	if (input->GetKey(SDL_SCANCODE_L) == j1KeyState::KEY_DOWN)
		LoadGame();

	if (want_to_save == true)
		SaveGameNow();

	if (want_to_load == true)
		LoadGameNow();

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;	
	}
}

bool j1App::CleanUp()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();										
		item = item->prev;
	}	

	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

const char* j1App::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

const char* j1App::GetTitle() const
{
	return title.GetString();
}

const char* j1App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save

void j1App::SaveGame() const
{
	want_to_save = true;
}

void j1App::LoadGame()
{
	if (save_document_full == true)
	{
		want_to_load = true;
	}
}

bool j1App::SaveGameNow() const
{
	bool ret = true;

	pugi::xml_document save_doc;
	pugi::xml_parse_result result = save_doc.load("save-doc.xml");
	save_doc.reset();
	pugi::xml_node node = save_doc.append_child("game");
	 
	App->render->Save(node);
	App->manager->Save(node);

	save_doc.save_file("save-doc.xml");
	save_document_full = true;
	want_to_save = false;

	return ret;
}

bool j1App::LoadGameNow()
{
	bool ret = false;

	pugi::xml_document save_doc;
	pugi::xml_parse_result result = save_doc.load_file("save_game.xml");

	pugi::xml_node node = save_doc.child("game");

	App->render->Load(node);
	App->manager->Load(node);

	return ret;
}
