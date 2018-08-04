/// \file       SDK.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    SDK
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_SDK_HPP__
#define OOM_ENGINE_SDK_HPP__

// Always include the config first
// To avoid including GL before GLEW
#include <Render/Config.hpp>

// Third party
#include <GLM/glm.hpp>

// Standard types
#include "Core/Standard/CString.hpp"

// Components
// Generic
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"
#include "Composite/Component/CTransform.hpp"

// Graphic
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"
#include "Render/Renderer/CMeshRenderer.hpp"
#include "Render/Renderer/CTextRenderer.hpp"

// Audio
#include "Audio/CAudioSource3D.hpp"
#include "Audio/CAudioListener3D.hpp"

// Resources
#include "Resource/CMesh.hpp"
#include "Audio/CAudioBuffer.hpp"

// Built-in
#include "Built-in/Script/S_Text.hpp"
#include "Built-in/Script/S_Camera.hpp"
#include "Built-in/Script/S_PointLight.hpp"
#include "Built-in/Script/S_DirectionalLight.hpp"
#include "Built-in/Script/S_CameraController.hpp"

// Misc
#include "Render/Gizmos/CGizmosManager.hpp"

// Namespace
using namespace Oom;

// Shorcuts
using EGizmo = CGizmosManager::EGizmo;

namespace Sdk
{

    namespace Mouse
    {
        void               SetMousePosition(const glm::vec2& position);
        glm::tvec3<double> GetMousePosition();
        // TODO : Hide / show window
    }

    namespace Window
    {
        glm::vec2 GetWindowSize();
    }

    namespace Input
    {
        bool IsKeyPressed  (int key_code);
        bool IsKeyReleased (int key_code);
    }

    namespace GameObject
    {
        CGameObject* CreateEmpty();
        CGameObject* CreateCamera();
        CGameObject* CreateFreeCamera();
        CGameObject* CreateCube();
        CGameObject* CreateParticleSystem();
        CGameObject* CreateDirectionalLight();
        CGameObject* CreatePointLight();
        CGameObject* CreateText();
		CGameObject* CreateAudioListener3D();
		CGameObject* CreateAudioSource3D();
    }

    namespace Debug
    {
        void LogUser  (const char * szFormat, ...);
        void LogInfo  (const char * szFormat, ...);
        void LogWaring(const char * szFormat, ...);
        void LogError (const char * szFormat, ...);

		void EnableGizmo  (EGizmo type);
		void DisableGizmo (EGizmo type);
    }

    namespace Import
    {
        GLuint ImportTexture(const char* p_path);
        std::vector<CGameObject*> ImportMesh(const char* p_path);
    }
}

#endif // !OOM_ENGINE_SDK_HPP__