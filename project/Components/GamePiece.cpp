#include "GamePiece.h"
#include "source/log/GameLog.h"
#include "Ecs.h"

using namespace nc;

namespace project
{
    GamePiece::GamePiece(ComponentHandle handle, EntityHandle parentHandle, nc::Transform* transform)
        : Component(handle, parentHandle),
          physics::IClickable(transform, 40.0f),
          m_isRegisteredAsClickable{ true },
          m_entityTag{Ecs::GetEntity(m_parentHandle)->Tag}
    {
        physics::Physics::RegisterClickable(this);
        layers |= physics::Layer::GamePiece;
    }

    GamePiece::~GamePiece()
    {
        if(m_isRegisteredAsClickable)
        {
            physics::Physics::UnregisterClickable(this);
        }
    }

    void GamePiece::OnClick()
    {
        project::log::GameLog::Log("Clicked: " + m_entityTag);
    }

    void GamePiece::NetworkDispatchTest(uint8_t* data)
    {
        (void)data;
        project::log::GameLog::Log("NetworkDispatchTest()");
    }
}