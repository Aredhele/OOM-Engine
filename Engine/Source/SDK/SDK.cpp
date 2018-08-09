/// \file       SDK.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    SDK
/// \author     Vincent STEHLY--CALISTO

#include <cstdarg>
#include "SDK/SDK.hpp"
#include "Engine/CEngine.hpp"
#include "Render/CRenderer.hpp"
#include "Physics/CPhysicWorld.hpp"

// Import
#include "Import/CMeshImporter.hpp"
#include "Import/CTextureImporter.hpp"

// Debug
#include "Core/Debug/SLogger.hpp"

// Gizmos
#include "Render/Gizmos/CGizmosRay.hpp"
#include "Render/Gizmos/CGizmosBox.hpp"
#include "Render/Gizmos/CGizmosLine.hpp"
#include "Render/Gizmos/CGizmosCone.hpp"
#include "Render/Gizmos/CGizmosCollider.hpp"
#include "Render/Gizmos/CGizmosTransform.hpp"
#include "Render/Gizmos/CGizmosPointLight.hpp"
#include "Render/Gizmos/CGizmosAudioSource.hpp"
#include "Render/Gizmos/CGizmosDirectionalLight.hpp"

namespace Sdk
{
    // Mouse specific functions
    namespace Mouse
    {
	    void ShowMouse() {
			CEngine::ShowMouse();
	    }

	    void HideMouse() {
			CEngine::HideMouse();
	    }

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

	    bool IsMouseButtonPressed(int button) {
			return CEngine::IsMouseButtonPressed(button);
	    }

	    bool IsMouseButtonReleased(int button) {
			return CEngine::IsMouseButtonReleased(button);
	    }
    }

    // GameObject specific functions
    namespace GameObject
    {
        CGameObject* CreateEmpty() {
            return CEngine::Instantiate();
        }

        CGameObject* CreateCamera() {

            bool b_first_camera = (CEngine::FindWithTag("MainCamera") == nullptr);

            CGameObject* p_camera_object = CEngine::Instantiate();
            p_camera_object->AddComponent<S_Camera>();
            p_camera_object->SetTag(b_first_camera ? "MainCamera" : "");

            return p_camera_object;
        }

        CGameObject* CreateFreeCamera() {

            CGameObject* p_camera = CreateCamera();
			p_camera->AddComponent<CAudioListener3D>();
            p_camera->AddComponent<S_CameraController>();
			
            return p_camera;
        }

        CGameObject* CreateCube() {
            return CEngine::Instantiate();
        }

        CGameObject* CreateParticleSystem() {
            return CEngine::Instantiate();
        }

        CGameObject* CreateDirectionalLight() {
            CGameObject* p_light_object = CEngine::Instantiate();
            p_light_object->AddComponent<S_DirectionalLight>();

            return p_light_object;
        }

        CGameObject* CreatePointLight() {
            CGameObject* p_light_object = CEngine::Instantiate();
            p_light_object->AddComponent<S_PointLight>();

            return p_light_object;
        }

        CGameObject* CreateUIText() {
			CGameObject* p_text_object = CEngine::Instantiate();

			auto* p_renderer    = p_text_object->AddComponent<CTextRenderer>();
			auto* p_mesh_filter = p_text_object->AddComponent<CMeshFilter>();
			auto* p_material    = p_text_object->AddComponent<CMaterial>();
			auto* p_script      = p_text_object->AddComponent<S_Text>();

			p_material->SetShader(EShaderType::Text);
			p_material->SetTexture(CTextureImporter::ImportTexture("Resources/Texture/Font.png"));

			return p_text_object;
        }

		CGameObject* CreateAudioListener3D() {
			CGameObject* p_listener = CEngine::Instantiate();
			p_listener->AddComponent<CAudioListener3D>();

			return p_listener;
        }

		CGameObject* CreateAudioSource3D()   {
			CGameObject* p_source = CEngine::Instantiate();
			p_source->AddComponent<CAudioSource3D>();

			return p_source;
        }

	    CGameObject* CreateUISprite() {
			CGameObject* p_sprite_object = CEngine::Instantiate();
			p_sprite_object->AddComponent<CUISpriteRenderer>();

			auto* p_filter   = p_sprite_object->AddComponent<CMeshFilter>();
			auto* p_material = p_sprite_object->AddComponent<CMaterial>();
			p_material->SetShader(EShaderType::UISprite);

			static float sprite_quad[18] =
			{
				-0.5f,  0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				 0.5f,  0.5f, 0.0f,

				 0.5f,  0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
			 	 0.5f, -0.5f, 0.0f
			};

			static float sprite_uv[12] =
			{
				 0.0f,  1.0f,
				 0.0f,  0.0f,	
				 1.0f,  1.0f,

				 1.0f,  1.0f, 
				 0.0f,  0.0f,
				 1.0f,  0.0f
			};

			p_filter->GetMesh().SetVertices(sprite_quad, 18);
			p_filter->GetMesh().SetUVs     (sprite_uv,   12);

			return p_sprite_object;
	    }

	    void AddMesh(CGameObject* p_game_object, const char* p_mesh) {
			CMeshImporter::AddMeshToGameObject(p_game_object, p_mesh);
	    }

	    CGameObject* CreateGameObjectFromMesh(const char* p_mesh) {
			return CMeshImporter::CreateObjectFromMesh(p_mesh);
	    }

	    std::vector<CGameObject*> CreateGameObjectsFromMeshes(const char* p_file) {
			return CMeshImporter::CreateObjectsFromFile(p_file);
	    }
    }

	namespace Render
    {
		void EnablePostProcessing() {
			CRenderer::EnablePostProcessing();
		}

		void DisablePostProcessing() {
			CRenderer::DisablePostProcessing();
		}

		void EnablePostEffect(EPostEffect effect) {
			CRenderer::GetPostProcessingStack()->SetEffectActive(effect, true);
		}

		void DisablePostEffect(EPostEffect effect) {
			CRenderer::GetPostProcessingStack()->SetEffectActive(effect, false);
		}

		CPostProcessingStack* GetPostProcessingStack() {
			return CRenderer::GetPostProcessingStack();
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

	    void EnableGizmo(EGizmo type) {
			CGizmosManager::EnableGizmo(type);
	    }

	    void DisableGizmo(EGizmo type) {
			CGizmosManager::DisableGizmo(type);
	    }

	    void DrawRay(glm::vec3 const& start, glm::vec3 const& dir, glm::vec3 const& color) {
			Oom::DrawRay(start, dir, color);
	    }

	    void DrawBox(glm::vec3 const& center, float width, float height, glm::vec3 const& color) {
			Oom::DrawBox(center, width, height, color);
	    }

	    void DrawLine(glm::vec3 const& start, glm::vec3 const& end, glm::vec3 const& color) {
			Oom::DrawLine(start, end, color);
	    }

	    void DrawCone(glm::vec3 const& position, float radius, float topRadius, float lenght, glm::vec3 const& color) {
			Oom::DrawCone(position, radius, topRadius, lenght, color);
	    }

	    void DrawCollider(CBoxCollider& collider) {

			auto* p_go   = collider.GetGameObject();
			auto* p_body = p_go->GetComponent<CRigidBody>();

			Oom::DrawCollider(
				p_go->GetTransform().GetPosition(), 
				collider.GetExtent(), p_go->GetTransform().GetRotationMatrix(), glm::vec3(0.1f, 0.1f, 0.9f));
	    }

	    void DrawTransform(const CTransform& transform) {
			Oom::DrawTransform(transform.GetPosition(), transform.GetUp(), transform.GetRight(), transform.GetForward());
	    }

	    void DrawTransform(glm::vec3 const& position, const glm::vec3& up, const glm::vec3& right, const glm::vec3& forward)  {
			Oom::DrawTransform(position, up, right, forward);
	    }

	    void DrawPointLight(glm::vec3 const& position, glm::vec3 const& color, int resolution, float range, float scale) {
			Oom::DrawPointLight(position, color, resolution, range, scale);
	    }

	    void DrawAudioSource(glm::vec3 const& position, float distance_min, float distance_max, int resolution, float scale) {
			Oom::DrawAudioSource(position, distance_min, distance_max, resolution, scale);
	    }

	    void DrawDirectionalLight(glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& color, float scale) {
			Oom::DrawDirectionalLight(position, direction, color, scale);
	    }
    }

    namespace Import
    {
        GLuint ImportTexture(const char* p_path) {
            return CTextureImporter::ImportTexture(p_path);
        }

        void ImportMesh(const char* p_path) {
			CMeshImporter::ImportFromObj(p_path);
        }
    }

	namespace Physic
    {
		CRayCast RayCast(const glm::vec3& start, const glm::vec3& dir) {
			CRayCast ray_cast(start, dir);
			CPhysicWorld::RayCast(&ray_cast, &ray_cast.GetRayCastData());

			return ray_cast;
		}
    }
}

