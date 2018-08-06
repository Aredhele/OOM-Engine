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

// Tim
#include "CTime.hpp"

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

// Physics
#include "Physics/CCollision.hpp"
#include "Physics/CRigidBody.hpp"
#include "Physics/CBoxCollider.hpp"

// Resources
#include "Resource/CMesh.hpp"
#include "Audio/CAudioBuffer.hpp"

// Built-in
// Test
#include "Built-in/Script/S_Scale.hpp"
#include "Built-in/Script/S_Rotate.hpp"
#include "Built-in/Script/S_Translate.hpp"
#include "Built-in/Script/S_Collision.hpp"

// User
#include "Built-in/Script/S_Text.hpp"
#include "Built-in/Script/S_Camera.hpp"
#include "Built-in/Script/S_LookAt.hpp"
#include "Built-in/Script/S_PointLight.hpp"
#include "Built-in/Script/S_CameraRotator.hpp"
#include "Built-in/Script/S_DirectionalLight.hpp"
#include "Built-in/Script/S_CameraController.hpp"

// Misc
#include "Render/Gizmos/CGizmosManager.hpp"
#include "Render/PostProcessing/IPostEffect.hpp"
#include "Render/PostProcessing/CPostProcessingStack.hpp"
#include "Physics/CRayCast.hpp"
#include "Core/Debug/SLogger.hpp"

// Namespace
using namespace Oom;

// Shorcuts
using EGizmo      = CGizmosManager::EGizmo;
using EPostEffect = IPostEffect::EType;

namespace Sdk
{

    namespace Mouse
    {
		void			   ShowMouse();
		void			   HideMouse();
        void               SetMousePosition(const glm::vec2& position);
        glm::tvec3<double> GetMousePosition();
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
        CGameObject* CreateEmpty			();
        CGameObject* CreateCamera			();
        CGameObject* CreateFreeCamera		();
        CGameObject* CreateCube				();
        CGameObject* CreateParticleSystem	();
        CGameObject* CreateDirectionalLight	();
        CGameObject* CreatePointLight		();
        CGameObject* CreateText				();
		CGameObject* CreateAudioListener3D	();
		CGameObject* CreateAudioSource3D	();
    }

	namespace Physic
    {
		CRayCast RayCast(const glm::vec3& start, const glm::vec3& dir);
    }

	namespace Render
    {
		void					EnablePostProcessing	();
		void					DisablePostProcessing	();
		void					EnablePostEffect        (EPostEffect effect);
		void					DisablePostEffect       (EPostEffect effect);
		CPostProcessingStack*	GetPostProcessingStack	();
    }

    namespace Debug
    {
        void LogUser  (const char * szFormat, ...);
        void LogInfo  (const char * szFormat, ...);
        void LogWaring(const char * szFormat, ...);
        void LogError (const char * szFormat, ...);

		void EnableGizmo  (EGizmo type);
		void DisableGizmo (EGizmo type);

		void DrawRay			 (glm::vec3 const& start,    glm::vec3 const& dir, glm::vec3 const& color);
		void DrawBox			 (glm::vec3 const& center,   float width, float height, glm::vec3 const& color);
		void DrawLine			 (glm::vec3 const& start,    glm::vec3 const& end, glm::vec3 const& color);
		void DrawCone			 (glm::vec3 const& position, float radius, float topRadius, float lenght, glm::vec3 const& color);
		void DrawPointLight		 (glm::vec3 const& position, glm::vec3 const& color, int resolution, float range, float scale);
		void DrawAudioSource     (glm::vec3 const& position, float distance_min, float distance_max, int resolution, float scale);
		void DrawDirectionalLight(glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& color, float scale);
    }

    namespace Import
    {
        GLuint ImportTexture(const char* p_path);
        std::vector<CGameObject*> ImportMesh(const char* p_path);
    }
}

#endif // !OOM_ENGINE_SDK_HPP__