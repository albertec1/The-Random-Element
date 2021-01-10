#include <stdlib.h>

#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"

//Brofiler
#include "External/Brofiler/Brofiler/Brofiler.h"
#pragma comment( lib, "Brofiler/Brofiler/ProfilerCore32.lib")

// This is needed here because SDL redefines main function
// do not add any other libraries here, instead put them in their modules
#include "External/SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum class MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

j1App* App = NULL;

int main(int argc, char* args[])
{
	LOG("Engine strarting ... %d");

	MainState state = MainState::CREATE;
	int result = EXIT_FAILURE;

	while (state != MainState::EXIT)
	{BROFILER_FRAME("Main_thread")
		switch (state)
		{
			//Allocte the engine ---------------------------------------
		case MainState::CREATE:
			LOG("CREATION PHASE =======================================");

			App = new j1App(argc, args);

			if (App != NULL)
				state = MainState::AWAKE;
			else
				state = MainState::FAIL;

			break;

			//Awake all modules------------------------------------------
		case MainState::AWAKE:
			LOG("AWAKE PHASE ============================================");
			if (App->Awake() == true)
				state = MainState::START;
			else
			{
				LOG("ERROR: Awake failed");
				state = MainState::FAIL;
			}

			break;

			// Call all moules before first frame --------------------------
		case MainState::START:
			LOG("START PHASE ===========================================");
			if (App->Start() == true)
			{
				state = MainState::LOOP;
				LOG("UPDATE PHASE ===========================================");
			}
			else
			{
				LOG("ERROR: Start Failed");
				state = MainState::FAIL;
			}

			// Loop all modules until we are asked to leave -----------------
		case MainState::LOOP:
			if (App->Update() == false)
				state = MainState::CLEAN;
			break;

			// Clean up allocated memory -------------------------------------
		case MainState::CLEAN:
			LOG("CLEANUP PHASE ===========================================");
			if (App->CleanUp() == true)
			{
				RELEASE(App);
				result = EXIT_SUCCESS;
				state = MainState::EXIT;
			}
			else
				state = MainState::FAIL;

			break;

			// Exit with errors ---------------------------------------------
		case MainState::FAIL:
			LOG("Exiting with errors =====================================");
			result = EXIT_FAILURE;
			state = MainState::EXIT;
			break;
		}
	}

	LOG("... Bye! :)\n");
	
	//Dump memory leaks
	return result;
}