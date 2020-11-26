#include "AutonomousEntity.h"

AutonomousEntity::AutonomousEntity(iPoint pos, ENTITY_TYPE type) : j1MovingEntity(pos, type)
{

}

AutonomousEntity::~AutonomousEntity()
{
}

bool AutonomousEntity::Awake(pugi::xml_node& node)
{
	return true;
}

bool AutonomousEntity::Start()
{
	return false;
}

bool AutonomousEntity::PreUpdate()
{
	return false;
}

bool AutonomousEntity::Update(float dt)
{
	return false;
}

bool AutonomousEntity::PostUpdate()
{
	return false;
}

bool AutonomousEntity::CleanUp()
{
	return false;
}

bool AutonomousEntity::Draw()
{
	return false;
}

void AutonomousEntity::GoTo(fPoint destination, ENTITY_TYPE type)
{
}

void AutonomousEntity::Chase(int range, int enemy)
{
}

void AutonomousEntity::Move(float dt)
{
}

void AutonomousEntity::NextStep()
{
}
