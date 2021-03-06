#pragma once

#include <concepts>
#include <memory>
#include <vector>

namespace nc::graphics
{
    namespace d3dresource
    {
        class GraphicsResource;
        class IndexBuffer;
    }

    class ResourceGroup 
    {
        public:
            template<std::derived_from<d3dresource::GraphicsResource> T>
            T * QueryGraphicsResource() noexcept;
            void Bind() const;
            void AddGraphicsResource(d3dresource::GraphicsResource* res);

        protected:
            std::vector<d3dresource::GraphicsResource*> m_resources;
    };

    template<std::derived_from<d3dresource::GraphicsResource> T>
    T* ResourceGroup::QueryGraphicsResource() noexcept
    {
        for(auto& res : m_resources)
        {
            if(auto pt = dynamic_cast<T*>(res))
            {
                return pt;
            }
        }
        return nullptr;
    }
}