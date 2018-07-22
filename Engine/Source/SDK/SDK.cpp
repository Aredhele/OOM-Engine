/// \file       SDK.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    SDK
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
#include "CEngine.hpp"

namespace Sdk
{
    // Mouse specific functions
    namespace Mouse
    {
        void SetMousePosition(const glm::vec2 &position) {
            Oom::CEngine::SetMousePosition(position);
        }

        glm::tvec3<double> GetMousePosition() {
            return Oom::CEngine::GetMousePosition();
        }

    }

    // Window specific functions
    namespace Window
    {
        glm::vec2 GetWindowSize() {
            return Oom::CEngine::GetWindowSize();
        }
    }

    // Input specific functions
    namespace Input
    {
        bool IsKeyPressed(int key_code) {
            return Oom::CEngine::IsKeyPressed(key_code);
        }

        bool IsKeyReleased(int key_code) {
            return Oom::CEngine::IsKeyReleased(key_code);
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
}

