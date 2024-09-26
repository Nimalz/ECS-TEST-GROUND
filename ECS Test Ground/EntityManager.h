#pragma once

#include "Types.h"
#include <array>
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
	EntityManager();
	EntityID CreateEntity();
	void DestroyEntity(EntityID& entity);
	void SetMask(EntityID entity, ComponentMask signature);
	ComponentMask GetMask(EntityID entity);
private:
	std::vector<EntityID> mRecycledEntity{};	//Äg—p‰Â”\‚ÌEntity Index‹y‚ÑVersionî•ñ‚ğ•Û‘¶
	std::vector<EntityDesc> mEntities;
};
