//#include "stdafx.h"
#include "../stdafx.h"
#include "EntityManager.h"


int EntityManager::currentID=0;

EntityManager::EntityManager(void)
{
	
}


EntityManager::~EntityManager(void)
{
}


EntityManager* EntityManager::Instance()
{
	
	static EntityManager instance;

	return &instance;
	

	/*
	if(pEntityManager==NULL)
	{
		pEntityManager=new EntityManager;
	}
	return pEntityManager;
	*/
}

BaseEntity* EntityManager::GetEntityFromID(int id)const
{
	//find the entity
	//TODO
	EntityMap::const_iterator ent=entityMap.find(id);

	//assert...

	return ent->second;
}

void EntityManager::RemoveEntity(BaseEntity* pEntity)
{
	//remove
	entityMap.erase(entityMap.find(pEntity->GetID()));
}

void EntityManager::RegisterEntity(BaseEntity* newEntity)
{
	newEntity->SetID(currentID);
	entityMap.insert(make_pair(newEntity->GetID(),newEntity));
	currentID++;
}