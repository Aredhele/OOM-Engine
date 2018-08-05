/// \file       CEngine.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "CEngine.hpp"
#include "Core/Debug/SLogger.hpp"
#include "Render/Shader/SShaderCompiler.hpp"
#include <Glm/glm.hpp>
#include <Glm/ext.hpp>
#include "Resource/CMesh.hpp"
#include "QU3E/q3.h"

// Keep
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"
#include "Composite/Component/CTransform.hpp"
#include "Built-in/Script/S_Camera.hpp"
#include "Built-in/Script/S_CameraController.hpp"
#include "Render/Mesh/CMeshFilter.hpp"

// Keep²
#include "Render/CWindow.hpp"
#include "Render/CRenderer.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Renderer/CMeshRenderer.hpp"
#include "Render/Shader/SShaderManager.hpp"
#include "Render/Material/CMaterial.hpp"
#include "Physics/CPhysicWorld.hpp"
#include "Audio/CAudioEngine.hpp"
#include "Scene/Hook.hpp"

namespace Oom
{

/* static */ CEngine* CEngine::sp_instance = nullptr;

bool CEngine::Initialize()
{
    SLogger::LogInfo("Oom-Engine initialization.");

    mp_renderer = new CRenderer();
    mp_renderer->Initialize();

    // TODO : Delta time customisable ?
    mp_physic_world = new CPhysicWorld();
    mp_physic_world->Initialize(1.0f / 60.0f);

    mp_audio_engine = new CAudioEngine();
    mp_audio_engine->Initialize();


    // Static instance initialization
    sp_instance = this;

    SLogger::LogInfo("Oom-Engine initialized.");
    return true;
}

void CEngine::Release()
{
    SLogger::LogInfo("Releasing Oom-Engine");

    mp_renderer->Release();
    delete mp_renderer;

    mp_renderer = nullptr;
    sp_instance = nullptr;

    SLogger::LogInfo("Oom-Engine released.");
}

void CEngine::Run()
{
    // Getting GLFW window
    GLFWwindow* p_handle = mp_renderer->GetWindow()->GetHandle();

    double lag        = 0.0;
    double previous   = glfwGetTime();
    double delta_time = 1.0 / 60.0;

    // Setting up the scene
    LoadScene();

    while (glfwWindowShouldClose(p_handle) == 0 &&
           glfwGetKey(p_handle, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous       = current;

        lag += elapsed;

        // Processing events
        glfwPollEvents();

        // Fixed granularity
        while(lag >= delta_time)
        {
            BehaviorUpdate  (p_handle, static_cast<float>(delta_time));
            GameObjectUpdate(p_handle, static_cast<float>(delta_time));

            lag -= delta_time;
        }

		mp_audio_engine->Update(delta_time);
        mp_renderer->Render();
    }
}

void CEngine::BehaviorUpdate(GLFWwindow* p_window, float delta_time)
{
    // Behavior updates
    auto behavior_count = static_cast<uint32_t>(m_behaviors.size());
    for(uint32_t i = 0; i < behavior_count; ++i)
    {
        CBehavior* p_behavior = m_behaviors[i];
		CGameObject* p_go     = p_behavior->GetGameObject();

        // We can update the behavior
        if(p_behavior->m_is_enabled && p_go->IsActive())
        {
            if(p_behavior->m_first_update)
                p_behavior->__Start();

            p_behavior->__Update();
			p_behavior->OnDrawGizmos();
        }
    }
}

void CEngine::GameObjectUpdate(GLFWwindow* p_window, float delta_time)
{
    // Game objects life cycle check
    auto go_count = static_cast<uint32_t>(m_game_objects.size());
    for(uint32_t n_go = 0; n_go < go_count; /* no increment */)
    {
        CGameObject* p_game_object = m_game_objects[n_go];

        // The go is being destroyed
        if(p_game_object->m_is_destroyed &&
           p_game_object->m_destroy_delay != 0.0f)
        {
            p_game_object->m_destroy_elapsed += delta_time;
            if(p_game_object->m_destroy_elapsed >=
               p_game_object->m_destroy_delay)
            {
                p_game_object->m_destroy_delay = 0.0f;
            }
        }

        // The go is destroyed
        if(p_game_object->m_is_destroyed &&
           p_game_object->m_destroy_delay == 0.0f)
        {
            // Destroy notification
            p_game_object->__DestroyMessage();

            m_game_objects[n_go] = m_game_objects.back();
            m_game_objects.pop_back();

            delete p_game_object;
            go_count = static_cast<uint32_t>(m_game_objects.size());
        }
        else
        {
            n_go++;
        }
    }
}

/* static */ CGameObject* CEngine::Instantiate(/* void */)
{
    return Instantiate(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
}

/* static */ CGameObject* CEngine::Instantiate(CTransform* parent)
{
    auto* p_game_object = new CGameObject(parent);
    sp_instance->m_game_objects.push_back(p_game_object);

    return p_game_object;
}

/* static */ CGameObject* CEngine::Instantiate(const glm::vec3& position)
{
    return Instantiate((position), glm::vec3(0.0f), glm::vec3(0.0f));
}

/* static */ CGameObject* CEngine::Instantiate(const glm::vec3& position, const glm::vec3& scale)
{
    return Instantiate((position), glm::vec3(0.0f), glm::vec3(0.0f));
}

/* static */ CGameObject* CEngine::Instantiate(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation)
{
    auto* p_game_object = new CGameObject(position, scale, orientation);
    sp_instance->m_game_objects.push_back(p_game_object);

    return p_game_object;
}

/* static */ void CEngine::Destroy(CGameObject* p_game_object)
{
    p_game_object->m_is_destroyed = true;
}

/* static */ void CEngine::Destroy(CGameObject* p_game_object, float delay)
{
    p_game_object->m_is_destroyed  = true;
    p_game_object->m_destroy_delay = delay;
}

/* static */ void CEngine::DestroyImmediate(CGameObject* p_game_object)
{
	for (auto i = 0; i < sp_instance->m_game_objects.size(); ++i)
	{
		if (sp_instance->m_game_objects[i] == p_game_object)
		{
			p_game_object->__DestroyMessage();

			sp_instance->m_game_objects[i] = sp_instance->m_game_objects.back();
			sp_instance->m_game_objects.pop_back();

			delete p_game_object;
			return;
		}
	}
}

/* static */ CGameObject* CEngine::Find(const CString& name)
{
    for(auto* p_game_object : sp_instance->m_game_objects)
    {
        if(p_game_object->GetName() == name)
            return p_game_object;
    }

    return nullptr;
}

/* static */ CGameObject* CEngine::FindWithTag(const CString& tag)
{
    for(auto* p_game_object : sp_instance->m_game_objects)
    {
        if(p_game_object->GetTag() == tag)
            return p_game_object;
    }

    return nullptr;
}

/* static */ std::vector<CGameObject*> CEngine::FindGameObjectsWithTag(const CString& tag)
{
    std::vector<CGameObject*> game_objects;
    for(auto* p_game_object : sp_instance->m_game_objects)
    {
        if(p_game_object->GetTag() == tag)
            game_objects.push_back(p_game_object);
    }

    return game_objects;
}

/* static */ void CEngine::SetMousePosition(const glm::vec2 &position)
{
    glfwSetCursorPos(sp_instance->mp_renderer->GetWindow()->GetHandle(),
                     position.x, position.y);
}

/* static */ glm::tvec3<double> CEngine::GetMousePosition()
{
    glm::tvec3<double> mouse;
    glfwGetCursorPos(sp_instance->mp_renderer->GetWindow()->GetHandle(),
                     &mouse.x, &mouse.y);

    return mouse;
}

/* static */ glm::vec2 CEngine::GetWindowSize()
{
    return sp_instance->mp_renderer->GetWindow()->GetWindowSize();
}

/* static */ bool CEngine::IsKeyPressed(int key_code)
{
    return (glfwGetKey(sp_instance->mp_renderer->GetWindow()->GetHandle(), key_code) == GLFW_PRESS);
}

/* static */ bool CEngine::IsKeyReleased(int key_code)
{
    return (glfwGetKey(sp_instance->mp_renderer->GetWindow()->GetHandle(), key_code) == GLFW_RELEASE);
}

/* static */ void CEngine::RegisterBehavior(CBehavior* p_behavior)
{
    sp_instance->m_behaviors.push_back(p_behavior);
}

/* static */ void CEngine::UnregisterBehavior(CBehavior* p_behavior)
{
    std::vector<CBehavior*>& behaviors = sp_instance->m_behaviors;

    for(auto i = 0; i < behaviors.size(); ++i)
    {
        if(behaviors[i] == p_behavior)
        {
            behaviors[i] = behaviors.back();
            behaviors.pop_back();
            break;
        }
    }
}

/* static */ const std::vector<CGameObject*>& CEngine::GetAllGameObjects()
{ return sp_instance->m_game_objects; }

}