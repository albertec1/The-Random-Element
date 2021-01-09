#include "GUIElements.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "GUI.h"


j1Image::j1Image() 
{

	this->type = GUItype::GUI_IMAGE;
}

j1Image::~j1Image() 
{

}

bool j1Image::Start()
{
	if (textureType == TEXTURE::IMAGE) 
		texture = App->gui->Load_Texture(TEXTURE::IMAGE);

	if (textureType == TEXTURE::MANAGER_IMAGE) 
		texture = App->gui->Load_Texture(TEXTURE::MANAGER_IMAGE);

	if (textureType == TEXTURE::MAIN_IMAGE)
		texture = App->gui->Load_Texture(TEXTURE::MAIN_IMAGE);

	if (textureType == TEXTURE::RESOURCES_IMAGE)
		texture = App->gui->Load_Texture(TEXTURE::RESOURCES_IMAGE);

	if(textureType == TEXTURE::AUDIO_IMAGE)
		texture = App->gui->Load_Texture(TEXTURE::AUDIO_IMAGE);

	if (textureType == TEXTURE::GODMODE)
		texture = App->gui->Load_Texture(TEXTURE::GODMODE);

	if (textureType == TEXTURE::INFO_IMAGE)
		texture = App->gui->Load_Texture(TEXTURE::INFO_IMAGE);

	if (textureType == TEXTURE::EXPLANATION)
		texture = App->gui->Load_Texture(TEXTURE::EXPLANATION);

	if (textureType == TEXTURE::INFORMATION_IMAGE)
		texture = App->gui->Load_Texture(TEXTURE::INFORMATION_IMAGE);

	return true; 
}

bool j1Image::PreUpdate()
{

	return true;
}

bool j1Image::Update(float dt) {


	if (enabled) {
		if (textureType == TEXTURE::MAIN_IMAGE)
		App->render->AddBlitEvent(3, texture, map_position.x, map_position.y, rect, false,true, 0, 0, 0, 255, true);
		else if(textureType == TEXTURE::AUDIO_IMAGE)
		App->render->AddBlitEvent(3, texture, map_position.x, map_position.y, rect, false, true, 0, 0, 0, 255, true);
		else
		App->render->AddBlitEvent(4, texture, map_position.x, map_position.y, rect, false, true, 0, 0, 0, 255, true);



		if (textureType == TEXTURE::EXPLANATION) {
			App->render->AddBlitEvent(5, texture, map_position.x, map_position.y, rect, false, true, 0, 0, 0, 255, true);
		}
	}
	return true; 
}

bool j1Image::PostUpdate()
{
	if (enabled)
		Draw();

	return true;
}

bool j1Image::CleanUp()
{
	return true;
}

