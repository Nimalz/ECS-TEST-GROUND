#include "EntityManager.h"

EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		mAvailableEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(mLivingEntityCount < MAX_ENTITIES && "上限オーバー、エンティティ生成不能。");

	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop();
	++mLivingEntityCount;

	return id;
}

void EntityManager::DestroyEntity(Entity& entity)
{
	assert(entity < MAX_ENTITIES && "インデックスオーバー、削除不能。");

	mSignatures[entity].reset();
	mAvailableEntities.push(entity);
	--mLivingEntityCount;
}

void  EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "インデックスオーバー、サイン生成不能。");

	mSignatures[entity] = signature;
}


Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "インデックス、サインサクセス不能。");

	return mSignatures[entity];
}