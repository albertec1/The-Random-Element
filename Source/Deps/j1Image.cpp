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
	if (textureType == Texture::IMAGE) 
		texture = App->gui->LoadTexture(Texture::IMAGE);

	if (textureType == Texture::MANAGER_IMAGE) 
		texture = App->gui->LoadTexture(Texture::MANAGER_IMAGE);

	if (textureType == Texture::MAIN_IMAGE)
		texture = App->gui->LoadTexture(Texture::MAIN_IMAGE);

	if (textureType == Texture::RESOURCES_IMAGE)
		texture = App->gui->LoadTexture(Texture::RESOURCES_IMAGE);

	if(textureType == Texture::AUDIO_IMAGE)
		texture = App->gui->LoadTexture(Texture::AUDIO_IMAGE);

	if (textureType == Texture::GODMODE)
		texture = App->gui->LoadTexture(Texture::GODMODE);

	if (textureType == Texture::INFO_IMAGE)
		texture = App->gui->LoadTexture(Texture::INFO_IMAGE);

	if (textureType == Texture::EXPLANATION)
		texture = App->gui->LoadTexture(Texture::EXPLANATION);

	return true; 
}

bool j1Image::PreUpdate()
{

	return true;
}

bool j1Image::Update(float dt) {

	if (enabled) {
		if (textureType == Texture::MAIN_IMAGE)
		App->render->Blit(texture, mapPosition.x, mapPosition.y, &rect);
		else if(textureType == Texture::AUDIO_IMAGE)
		App->render->Blit(texture, mapPosition.x, mapPosition.y, &rect);
		else
		App->render->Blit(texture, mapPosition.x, mapPosition.y, &rect);

		if (textureType == Texture::EXPLANATION) {
			App->render->Blit(texture, mapPosition.x, mapPosition.y, &rect);
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

