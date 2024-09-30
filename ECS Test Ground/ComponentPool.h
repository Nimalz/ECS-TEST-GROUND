#pragma once
#pragma once

#include "Types.h"
#include <cassert>

//ComponentManagerが異なる型のComponentPoolを操作するためのインターフェース
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