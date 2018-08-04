/// \file       SDK.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    SDK
/// \author     Vincent STEHLY--CALISTO

#include <cstdarg>
#include "SDK/SDK.hpp"
#include "CEngine.hpp"
#include "Render/CRenderer.hpp"

// Import
#include "Import/CMeshImporter"
#include "Import/CTextureImporter.hpp"

// Debug
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

        CGameObject* CreateText() {
            CGameObject* p_text_object = CEngine::Instantiate();

            p_text_object->AddComponent<S_Text>();
            p_text_object->AddComponent<CMeshFilter>();
            p_text_object->AddComponent<CTextRenderer>();

            auto* p_material = p_text_object->AddComponent<CMaterial>();
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
    }

    namespace Import
    {
        GLuint ImportTexture(const char* p_path) {
            return CTextureImporter::ImportTexture(p_path);
        }

        std::vector<CGameObject*> ImportMesh(const char* p_path) {
            return CMeshImporter::ImportFromObj(p_path);
        }
    }
}

