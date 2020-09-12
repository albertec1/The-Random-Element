#pragma once

#include "SDL/include/SDL_rect.h"
#include "j1App.h"

#define MAX_FRAMES 1500

class Animation
{
public:
	p2SString name;
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];


private:
	float current_frame;
	bool end_animation = false;
	int loops = 0;
	int last_frame = 0;

public:

	Animation() {}
	Animation(p2SString name, float speed, bool loop)
	{
		this->name = name;
		this->speed = speed;
		this->loop = loop;
	}

	// Defines the last frame as the rect.
	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	// Returns a rect with current position of the frame.
	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : last_frame - 1;
			end_animation = true;
			loops++;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
		loops = 0;
	}

	// This function sets an ended animation to end. needed?
	void SetAnimation(bool ended) {

		end_animation = ended;
	}

	// This function gets the animation a returns it to end once the last frame is over. needed?
	bool GetAnimation() {

		return end_animation;
	}
};

