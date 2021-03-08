#include "ColliderSystem.h"
#include "config/Config.h"

namespace nc::physics
{
    ColliderSystem::ColliderSystem(uint32_t maxColliders)
        : ComponentSystem<Collider>{maxColliders},
          m_dynamicSoA{maxColliders},
          m_staticTree{},
          m_maxColliders{maxColliders}
    {
    }

    ColliderSystem::~ColliderSystem() = default;

    ColliderTree* ColliderSystem::GetStaticTree()
    {
        return &m_staticTree;
    }

    ColliderSoA* ColliderSystem::GetDynamicSOA()
    {
        return &m_dynamicSoA;
    }

    Collider* ColliderSystem::Add(EntityHandle handle, const ColliderInfo& info)
    {
        // need to handle maxColliders
        if(GetEntity(handle)->IsStatic)
            m_staticTree.Add(handle, info);
        else
            m_dynamicSoA.Add(handle, info);

        return ComponentSystem<Collider>::Add(handle, info);
    }

    bool ColliderSystem::Remove(EntityHandle handle)
    {
        if(!ComponentSystem<Collider>::Remove(handle))
            return false;

        if(GetEntity(handle)->IsStatic)
            m_staticTree.Remove(handle);
        else
            m_dynamicSoA.Remove(handle);

        return true;
    }

    void ColliderSystem::Clear()
    {
        ComponentSystem::Clear();
        m_dynamicSoA.Clear();
        m_staticTree.Clear();
    }
} // namespace nc::physics