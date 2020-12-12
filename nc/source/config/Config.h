#pragma once
#include <string>

namespace nc::config
{
    struct Config
    {
        Config();

        void Save() const;

        struct
        {
            std::string projectName;
            std::string logFilePath;
        } project;
        
        struct
        {
            bool useNativeResolution;
            bool launchInFullscreen;
            unsigned int screenWidth;
            unsigned int screenHeight;
            unsigned int targetFPS;
            double nearClip;
            double farClip;
            double frameUpdateInterval;
            std::string shadersPath;
        } graphics;

        struct
        {
            double fixedUpdateInterval;
        } physics;

        private:
            bool Validate() const;
    };
}