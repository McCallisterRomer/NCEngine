#ifndef CHARACTER
#define CHARACTER

#include "../../NCE/Common/Common.hpp"
#include "../../NCE/Components/Transform.hpp"
#include "../../NCE/Input/Input.hpp"


using namespace NCE;
using namespace NCE::Common;
using namespace NCE::Components;

class Character : public Component
{
    private:
        std::weak_ptr<Transform> m_transform;
        float _moveSpeed = 20;
    public:
        Character(EntityWeakPtr parent_);

        void OnInitialize() override;
        void OnFrameUpdate() override;
        void OnDestroy() override;

        void OnCollisionEnter(EntityWeakPtr other_) override;
};


#endif