#pragma once

#include "component/Component.h"
#include "component/EngineComponentGroup.h"

#include <concepts>
#include <memory>
#include <string>
#include <vector>

namespace nc
{
    class Transform;

    class Entity
    {
        public:
            Entity(const EntityHandle handle, const ComponentHandle transformHandle, const std::string& tag = "") noexcept;
            Entity(const Entity& other) = delete;
            Entity& operator=(const Entity&) = delete;
            Entity(Entity&& other);
            Entity& operator=(Entity&& other);
            ~Entity();

            mutable EntityHandle Handle;
            mutable std::string Tag;
            EngineComponentHandleGroup Handles;
            
            void SendFrameUpdate(float dt) noexcept;
            void SendFixedUpdate() noexcept;
            void SendOnDestroy() noexcept;
            void SendOnCollisionEnter(const EntityHandle other) noexcept;
            void SendOnCollisionStay() noexcept;
            void SendOnCollisionExit() noexcept;

            template<class T> requires std::derived_from<T, Component>
            bool HasUserComponent() const noexcept;

            template<class T, class ... Args> requires std::derived_from<T, Component>
            T * AddUserComponent(Args&& ... args) noexcept;

            template<class T> requires std::derived_from<T, Component>
            bool RemoveUserComponent() noexcept;

            template<class T> requires std::derived_from<T, Component>
            T * GetUserComponent() const noexcept; 

            const std::vector<std::unique_ptr<Component>> & GetUserComponents() const noexcept;
        
        private:
            std::vector<std::unique_ptr<Component>> m_userComponents;
    };

    template<class T> requires std::derived_from<T, Component>
    bool Entity::HasUserComponent() const noexcept
    {
        const std::type_info &targetType(typeid(T));
        for(auto& item : m_userComponents)
        {
            if (typeid(*item) == targetType) 
                return true;
        }
        return false;
    }

    template<class T, class ... Args> requires std::derived_from<T, Component>
    T * Entity::AddUserComponent(Args&& ... args) noexcept
    {
        if (HasUserComponent<T>())
        {
            return nullptr;
        }
        m_userComponents.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        Component * ptr = m_userComponents.back().get();
        ptr->Register(0, Handle);
        return dynamic_cast<T*>(ptr);
    }

    template<class T> requires std::derived_from<T, Component>
    bool Entity::RemoveUserComponent() noexcept
    {
        const std::type_info &targetType(typeid(T));
        for(std::vector<Component>::size_type i = 0; i < m_userComponents.size(); ++i)
        {
            if (typeid(*m_userComponents.at(i)) == targetType)
            {
                m_userComponents.at(i) = std::move(m_userComponents.at(m_userComponents.size() - 1));
                m_userComponents.pop_back();
                return true;
            }
        }
        return false;
    }

    template<class T> requires std::derived_from<T, Component>
    T * Entity::GetUserComponent() const noexcept
    {
        const std::type_info &targetType(typeid(T));
        for(auto& item : m_userComponents)
        {
            if (typeid(*item) == targetType)
                return dynamic_cast<T*>(item.get());
        }

        return nullptr;
    }
} //end namespace nc