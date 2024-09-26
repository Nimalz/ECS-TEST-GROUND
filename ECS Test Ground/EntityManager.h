#pragma once

#include "Types.h"
#include <array>
#include <cassert>
#include <queue>


class EntityManager
{
public:
	EntityManager();
	Entity CreateEntity();
	void DestroyEntity(Entity& entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity entity);
private:
	//–¢Žg—pEntity‚Ìqueue
	std::queue<Entity> mAvailableEntities{};
	//
	std::array<Signature, MAX_ENTITIES> mSignatures{};
	uint32_t mLivingEntityCount{};
};
