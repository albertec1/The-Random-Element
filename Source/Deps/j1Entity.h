#ifndef __J1ENTITY__
#define __J1ENTITY__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

struct Collider;
struct SDL_Texture;

enum class ENTITY_TYPE
{
	PLAYER,
	FLYING_ENEMY,
	WALKING_ENEMY,
	CASH_BAG,
	UNKNOWN_TYPE
};
class j1Entity : public j1Module
{
public:
	j1Entity(iPoint pos, ENTITY_TYPE type);

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update(float dt, bool doLogic);

	virtual bool PostUpdate();

	virtual bool CleanUp();

	//save?

	//load?

	virtual bool Draw();

	virtual void OnCollision(Collider* c1, Collider* c2);

	virtual const Collider* GetCollider()
	{
		return EntityCollider;
	}

	virtual const iPoint GetPosition()
	{
		return StartingPosition;
	}

	virtual void SetTexture(SDL_Texture* texture)
	{
		EntityTexture = texture;
	}

protected:
	ENTITY_TYPE		Type;
	Collider*		EntityCollider;
	iPoint			StartingPosition;
	SDL_Texture*	EntityTexture;
	SDL_Rect		EntityRect;
	iPoint			sprite_size;
	bool			flipped;

	friend class j1EntityManager;
};

#endif __J1ENTITY__
