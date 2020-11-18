#pragma once

#include "nc/source/math/Vector2.h"

namespace nc::window
{
    class IOnResizeReceiver
    {
        public:
            virtual void OnResize(Vector2 dimensions) = 0;
    };
}