#pragma once

namespace nc::graphics
{
    class Graphics;
    class Model;
    class Step;

    class Job
    {
        public:
            Job(const Step* pStep, const Model* pModel);
            void Execute(Graphics* gfx) const;

        private:
            const Step* m_pStep;
            const Model* m_pModel;
    };
}