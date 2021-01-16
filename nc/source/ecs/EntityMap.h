#pragma once
#include "ecs/Entity.h"
#include <unordered_map>

namespace nc::ecs
{
    using EntityMap = std::unordered_map<EntityHandle, Entity, EntityHandle::Hash>;
}