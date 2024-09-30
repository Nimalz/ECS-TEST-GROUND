#include "EntityManager.h"

EntityID EntityManager::CreateEntity()
{
	assert(mEntityDesc.size() < MAX_ENTITIES && "����I�[�o�[�A�G���e�B�e�B�����s�\�B");

	//�ė��p�\�̃C���f�N�X����ꍇ
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
	assert(entity < MAX_ENTITIES && "�C���f�b�N�X�I�[�o�[�A�폜�s�\�B");

	EntityID newID = Entity::CreateEntityID(EntityIndex(-1), Entity::GetVersion(entity) + 1);//Index����-1�ɃZ�b�g�AVersion���X�V
	EntityIndex index = Entity::GetIndex(entity);

	mEntityDesc[index].EnyityID = newID;
	mEntityDesc[index].Mask.reset();		//�s���A�N�Z�X��h�����߁A�}�X�N�����Z�b�g
	mRecycledEntityIndex.push_back(index);
}

