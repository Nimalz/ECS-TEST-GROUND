#include "EntityManager.h"

EntityID EntityManager::CreateEntity()
{
	assert(mEntityDesc.size() < MAX_ENTITIES && "上限オーバー、エンティティ生成不能。");

	//再利用可能のインデクスある場合
	if (!mRecycledEntityIndex.empty())
	{
		EntityIndex index = mRecycledEntityIndex.back();
		EntityVersion version = Entity::GetVersion(mEntityDesc[index].EnyityID);
		EntityID newID = Entity::CreateEntityID(index, version);
		mRecycledEntityIndex.pop_back();
		mEntityDesc[index].EnyityID = newID;
		return newID;
	}
	
	mEntityDesc.push_back({ Entity::CreateEntityID(EntityIndex(mEntityDesc.size()), 0), ComponentMask() });

	return mEntityDesc.back().EnyityID;
}

void EntityManager::DestroyEntity(EntityID entity)
{
	assert(entity < MAX_ENTITIES && "インデックスオーバー、削除不能。");

	EntityID newID = Entity::CreateEntityID(EntityIndex(-1), Entity::GetVersion(entity) + 1);//Index部を-1にセット、Versionを更新
	EntityIndex index = Entity::GetIndex(entity);

	mEntityDesc[index].EnyityID = newID;
	mEntityDesc[index].Mask.reset();		//不正アクセスを防ぐため、マスクをリセット
	mRecycledEntityIndex.push_back(index);
}

