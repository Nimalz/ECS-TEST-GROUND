#pragma once
#include "Types.h"
#include "ComponentPool.h"
#include <vector>
#include <memory>

class ComponentManager
{
public:
	ComponentManager()=default;
    
    template<typename T>
    bool HasComponent(EntityID id)
    {
        EntityIndex index = Entity::GetIndex(id);
        ComponentType componentID = Component::GetID<T>();

        return mEntityDesc[index].Mask.test(componentID);
    }

    template<typename T>
    void RegisterComponent(ComponentType id)
    {
        
        if (mComponentPools.size() <= id)
            mComponentPools.resize(id + 1, nullptr);
        if (mComponentPools[id] == nullptr)
            mComponentPools[id] = std::static_pointer_cast<IComponentPool>(std::make_shared<ComponentPool<T>>());
    }

    template<typename T>
    void AddComponent(EntityID id)
    {
        EntityIndex index = Entity::GetIndex(id);
        //versionˆá‚¢‚Å’†Ž~
        if (mEntityDesc[index].EnyityID != id)
            return;

        ComponentType componentID = Component::GetID<T>();
        RegisterComponent(componentID);
        mEntityDesc[index].Mask.set(componentID);

    }

    template<typename T>
    void RemoveComponent(EntityID id)
    {
        EntityIndex index = Entity::GetIndex(id);

        //versionˆá‚¢‚Å’†Ž~
        if (mEntityDesc[index].EnyityID != id)
            return;
        ComponentType componentID = Component::TypeID<T>();
        mEntityDesc[index].Mask.reset(componentID);
    }

    template<typename T>
    T* GetComponent(EntityID id)
    {
        EntityIndex index = Entity::GetIndex(id);
        ComponentType componentID = Component::GetID<T>();

        if (!mEntityDesc[index].Mask.test(componentID))
            return nullptr;

        T* component = GetPoolPtr()->GetPtr(index);
        return component;
    }

private:
	std::vector <std::shared_ptr<IComponentPool>> mComponentPools;

	template<typename T>
	std::shared_ptr<ComponentPool<T>> GetPoolPtr()
	{
		ComponentType ComponentID = Component::GetID();
		return std::static_pointer_cast<ComponentPool<T>>(mComponentPools[ComponentID]);
	}
};