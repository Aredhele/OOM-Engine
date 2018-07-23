/// \file       SDK.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    SDK
/// \author     Vincent STEHLY--CALISTO

#include <cstdarg>
#include "SDK/SDK.hpp"
#include "CEngine.hpp"

#include "Core/Debug/SLogger.hpp"

namespace Sdk
{
    // Mouse specific functions
    namespace Mouse
    {
        void SetMousePosition(const glm::vec2 &position) {
            CEngine::SetMousePosition(position);
        }

        glm::tvec3<double> GetMousePosition() {
            return CEngine::GetMousePosition();
        }

    }

    // Window specific functions
    namespace Window
    {
        glm::vec2 GetWindowSize() {
            return CEngine::GetWindowSize();
        }
    }

    // Input specific functions
    namespace Input
    {
        bool IsKeyPressed(int key_code) {
            return CEngine::IsKeyPressed(key_code);
        }

        bool IsKeyReleased(int key_code) {
            return CEngine::IsKeyReleased(key_code);
        }
    }

    // GameObject specific functions
    namespace GameObject
    {
        CGameObject* CreateCamera() {
            CGameObject* p_camera_object = CEngine::Instantiate();
            p_camera_object->AddComponent<S_Camera>();

            return p_camera_object;
        }
    }

    namespace Debug
    {
        void LogUser(const char* szFormat, ...) {
            va_list  argList;
                va_start(argList, szFormat);
                SLogger::LogUser(szFormat, argList);
            va_end  (argList);
        }

        void LogInfo(const char* szFormat, ...) {
            va_list  argList;
                va_start(argList, szFormat);
                SLogger::LogInfo(szFormat, argList);
            va_end  (argList);
        }

        void LogWaring(const char* szFormat, ...) {
            va_list  argList;
                va_start(argList, szFormat);
                SLogger::LogWaring(szFormat, argList);
            va_end  (argList);
        }

        void LogError(const char* szFormat, ...) {
            va_list  argList;
                va_start(argList, szFormat);
                SLogger::LogError(szFormat, argList);
            va_end  (argList);
        }
    }
}

