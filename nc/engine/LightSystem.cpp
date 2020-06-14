#include "LightSystem.h"
#include "graphics/Graphics.h"
#include "NCE.h"

namespace nc::engine
{
    LightSystem::LightSystem() {}

    LightSystem::~LightSystem() = default;

    void LightSystem::BindLights()
    {
        auto camMatrixXM = NCE::GetTransform(*NCE::GetMainCamera())->CamGetMatrix();

        ComponentSystem<PointLight>::ForEach([&camMatrixXM](auto & light)
        {
            light.Bind(camMatrixXM);
        });

        // for(auto& light : GetVector())
        // {
        //     light.Bind(camMatrixXM);
        // }
    }
}