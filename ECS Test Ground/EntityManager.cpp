#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityID EntityManager::CreateEntity()
{
	assert(mEntities.size() < MAX_ENTITIES && "上限オーバー、エンティティ生成不能。");

	if (!mRecycledEntity.empty())
	{
		EntityIndex index = Entity::GetIndex(mRecycledEntity.back());
		EntityVersion version = Entity::GetVersion(mRecycledEntity.back()+1);
		EntityID newID = Entity::CreateEntityID(index, version);
		mRecycledEntity.pop_back();
		mEntities[index].EnyityID = newID;
		return newID;
	}
	
	mEntities.push_back({ Entity::CreateEntityID(EntityIndex(mEntities.size()), 0), ComponentMask() });

	return mEntities.back().EnyityID;
}

void EntityManager::DestroyEntity(EntityID& entity)
{
	assert(entity < MAX_ENTITIES && "インデックスオーバー、削除不能。");

	mComponemtMask[entity].reset();
	mAvailableEntities.push(entity);
	--mLivingEntityCount;
}

void  EntityManager::SetMask(EntityID entity, ComponentMask mask)
{
	assert(entity < MAX_ENTITIES && "インデックスオーバー、サイン生成不能。");

	mComponemtMask[entity] = mask;
}


ComponentMask EntityManager::GetMask(EntityID entity)
{
	assert(entity < MAX_ENTITIES && "インデックス、サインサクセス不能。");

	return mComponemtMask[entity];
}