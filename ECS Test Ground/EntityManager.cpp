#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityID EntityManager::CreateEntity()
{
	assert(mEntities.size() < MAX_ENTITIES && "����I�[�o�[�A�G���e�B�e�B�����s�\�B");

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
	assert(entity < MAX_ENTITIES && "�C���f�b�N�X�I�[�o�[�A�폜�s�\�B");

	mComponemtMask[entity].reset();
	mAvailableEntities.push(entity);
	--mLivingEntityCount;
}

void  EntityManager::SetMask(EntityID entity, ComponentMask mask)
{
	assert(entity < MAX_ENTITIES && "�C���f�b�N�X�I�[�o�[�A�T�C�������s�\�B");

	mComponemtMask[entity] = mask;
}


ComponentMask EntityManager::GetMask(EntityID entity)
{
	assert(entity < MAX_ENTITIES && "�C���f�b�N�X�A�T�C���T�N�Z�X�s�\�B");

	return mComponemtMask[entity];
}