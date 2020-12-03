#pragma once

#include "ecs/Entity.h"
#include "component/PointLight.h"
#include "component/NetworkDispatcher.h"
#include "component/Renderer.h"
#include "component/Transform.h"
#include "DebugUtils.h"

#include <concepts>
#include <string>

namespace nc
{
    namespace ecs { class EcsImpl; }

    class Ecs
    {
        public:
            static void RegisterImpl(ecs::EcsImpl* impl);

            static EntityHandle CreateEntity(std::string tag);
            static EntityHandle CreateEntity(Vector3 pos, Vector3 rot, Vector3 scale, std::string tag);
            static bool DestroyEntity(EntityHandle handle);
            [[nodiscard]] static Entity* GetEntity(EntityHandle handle);
            [[nodiscard]] static Entity* GetEntity(std::string tag);

            template<class T, class ...Args> requires std::derived_from<T, Component>
            static T* AddComponent(EntityHandle handle, Args&& ... args);
            
            template<class T> requires std::derived_from<T, Component>
            static bool RemoveComponent(EntityHandle handle);
            
            template<class T> requires std::derived_from<T, Component>
            [[nodiscard]] static T* GetComponent(EntityHandle handle);
            
            template<class T> requires std::derived_from<T, Component>
            [[nodiscard]] static bool HasComponent(EntityHandle handle);

        private:
            static ecs::EcsImpl* m_impl;
    };

    template<> PointLight* Ecs::AddComponent<PointLight>(EntityHandle handle);
    template<> bool Ecs::RemoveComponent<PointLight>(EntityHandle handle);
    template<> PointLight* Ecs::GetComponent<PointLight>(EntityHandle handle);
    template<> bool Ecs::HasComponent<PointLight>(EntityHandle handle);

    template<> Renderer* Ecs::AddComponent<Renderer>(EntityHandle handle, graphics::Mesh& mesh, graphics::Material& material);
    template<> bool Ecs::RemoveComponent<Renderer>(EntityHandle handle);
    template<> Renderer* Ecs::GetComponent<Renderer>(EntityHandle handle);
    template<> bool Ecs::HasComponent<Renderer>(EntityHandle handle);

    template<> NetworkDispatcher* Ecs::AddComponent<NetworkDispatcher>(EntityHandle handle);
    template<> bool Ecs::RemoveComponent<NetworkDispatcher>(EntityHandle handle);
    template<> NetworkDispatcher* Ecs::GetComponent<NetworkDispatcher>(EntityHandle handle);
    template<> bool Ecs::HasComponent<NetworkDispatcher>(EntityHandle handle);

    template<> Transform* Ecs::GetComponent<Transform>(EntityHandle handle);

    template<class T, class ... Args> requires std::derived_from<T, Component>
    T * Ecs::AddComponent(const EntityHandle handle, Args&& ... args)
    {
        auto ptr = GetEntity(handle);
        IF_THROW(ptr == nullptr, "Bad handle");
        return ptr->AddUserComponent<T>(std::forward<Args>(args)...);
    }

    template<class T> requires std::derived_from<T, Component>
    bool Ecs::RemoveComponent(const EntityHandle handle)
    {
        auto ptr = GetEntity(handle);
        IF_THROW(ptr == nullptr, "Bad handle");
        return ptr->RemoveUserComponent<T>();
    }

    template<class T> requires std::derived_from<T, Component>
    T * Ecs::GetComponent(const EntityHandle handle)
    {
        auto ptr = GetEntity(handle);
        IF_THROW(ptr == nullptr, "Bad handle");
        return ptr->GetUserComponent<T>();
    }

    template<class T> requires std::derived_from<T, Component>
    bool Ecs::HasComponent(const EntityHandle handle)
    {
        auto ptr = GetEntity(handle);
        IF_THROW(ptr == nullptr, "Bad handle");
        return ptr->HasUserComponent<T>();
    }
} // end namespace nc