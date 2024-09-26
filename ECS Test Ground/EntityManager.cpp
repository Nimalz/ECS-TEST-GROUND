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
	assert(mLivingEntityCount < MAX_ENTITIES && "����I�[�o�[�A�G���e�B�e�B�����s�\�B");

	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop();
	++mLivingEntityCount;

	return id;
}

void EntityManager::DestroyEntity(Entity& entity)
{
	assert(entity < MAX_ENTITIES && "�C���f�b�N�X�I�[�o�[�A�폜�s�\�B");

	mSignatures[entity].reset();
	mAvailableEntities.push(entity);
	--mLivingEntityCount;
}

void  EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "�C���f�b�N�X�I�[�o�[�A�T�C�������s�\�B");

	mSignatures[entity] = signature;
}


Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "�C���f�b�N�X�A�T�C���T�N�Z�X�s�\�B");

	return mSignatures[entity];
}