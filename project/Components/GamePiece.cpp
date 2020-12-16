#include "GamePiece.h"
#include "source/log/GameLog.h"
#include "Ecs.h"

namespace project
{
    GamePiece::GamePiece(nc::Transform* transform)
        : nc::physics::IClickable(transform, 40.0f),
          m_isRegisteredAsClickable{ true },
          m_entityTag{}
    {
        nc::physics::Physics::RegisterClickable(this);
        layers |= nc::physics::Layer::GamePiece;
    }

    GamePiece::~GamePiece()
    {
        if(m_isRegisteredAsClickable)
        {
            nc::physics::Physics::UnregisterClickable(this);
        }
    }

    void GamePiece::OnClick()
    {
        if(m_entityTag == "")
        {
            m_entityTag = nc::Ecs::GetEntity(m_parentHandle)->Tag;
        }
        project::log::GameLog::Log("Clicked: " + m_entityTag);
    }

    void GamePiece::NetworkDispatchTest(uint8_t* data)
    {
        (void)data;
        project::log::GameLog::Log("NetworkDispatchTest()");
    }
}