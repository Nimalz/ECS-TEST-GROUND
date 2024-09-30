#pragma once

#include "Types.h"
#include <cassert>
#include <vector>


class EntityManager
{
public:
	struct EntityDesc
	{
		EntityID      EnyityID;
		ComponentMask Mask;
	};
public:
	EntityManager()=default;
	EntityID CreateEntity();
	void DestroyEntity(EntityID entity);

	friend class ComponentManager;

private:
	std::vector<EntityIndex> mRecycledEntityIndex{};	//�Ďg�p�\��Entity Index�y��Version����ۑ�
	std::vector<EntityDesc> mEntityDesc;
};
