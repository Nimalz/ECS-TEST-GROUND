#pragma once
#pragma once

#include "Types.h"
#include <cassert>

//ComponentManager���قȂ�^��ComponentPool�𑀍삷�邽�߂̃C���^�[�t�F�[�X
class IComponentPool
{
public:
	virtual ~IComponentPool() = default;
};


template<typename T>
class ComponentPool : public IComponentPool
{
public:
	ComponentPool()
	{
		mPData = new char[sizeof(T) * MAX_ENTITIES];

	}

	~ComponentPool()
	{
		delete[] mPData;
	}

	inline T* GetPtr(EntityID id)
	{

		return static_cast<T*>(mPData + Entity::GetIndex(id) * mSize);
	}


private:
	char* mPData{ nullptr };
};