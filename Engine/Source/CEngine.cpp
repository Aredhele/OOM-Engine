/// \file       CEngine.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include <Render/CCamera.hpp>
#include "CEngine.hpp"
#include "Core/Debug/SLogger.hpp"
#include "Render/Shader/SShaderCompiler.hpp"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"

// Keep
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

/* static */ CEngine* CEngine::sp_instance = nullptr;

bool CEngine::Initialize()
{
    SLogger::LogInfo("Oom-Engine initialization.");

    mp_renderer = new CRenderer();
    mp_renderer->Initialize();

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

    glfwSetInputMode(p_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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
            BehaviorUpdate(p_handle,   static_cast<float>(delta_time));
            GameObjectUpdate(p_handle, static_cast<float>(delta_time));
            lag -= delta_time;
        }

        mp_renderer->Render();
        glfwSwapBuffers(p_handle);
    }
}

void CEngine::BehaviorUpdate(GLFWwindow* p_window, float delta_time)
{
    // Behavior updates
    auto behavior_count = static_cast<uint32_t>(m_behaviors.size());
    for(uint32_t i = 0; i < behavior_count; ++behavior_count)
    {
        CBehavior* p_behavior = m_behaviors[i];

        // We can update the behavior
        if(p_behavior->m_is_enabled &&
           p_behavior->GetTransform().GetRoot().GetGameObject()->IsActive())
        {
            if(p_behavior->m_first_update)
                p_behavior->__Start();

            p_behavior->__Update();
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

/* static */ CGameObject* CEngine::Instantiate(CTransform& parent)
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

    for(CTransform* p_transform : p_game_object->GetTransform().GetChildren())
        Destroy(p_transform->GetGameObject());
}

/* static */ void CEngine::Destroy(CGameObject* p_game_object, float delay)
{
    p_game_object->m_is_destroyed   = true;
    p_game_object->m_destroy_delay = delay;

    for(CTransform* p_transform : p_game_object->GetTransform().GetChildren())
        Destroy(p_transform->GetGameObject(), delay);
}

/* static */ void CEngine::DestroyImmediate(CGameObject* p_game_object)
{
    std::vector<CGameObject*> destroy_list(1, p_game_object);
    for(CTransform* p_transform : p_game_object->GetTransform().GetChildren())
        destroy_list.push_back(p_transform->GetGameObject());

    auto go_count = static_cast<uint32_t>(sp_instance->m_game_objects.size());
    for(uint32_t n_go = 0; n_go < go_count; /* no increment */ )
    {
        if(!destroy_list.empty() && sp_instance->m_game_objects[n_go] == destroy_list.back())
        {
            destroy_list.back()->__DestroyMessage();

            sp_instance->m_game_objects[n_go] = sp_instance->m_game_objects.back();
            sp_instance->m_game_objects.pop_back();

            delete destroy_list.back();
            destroy_list.pop_back();

            go_count = static_cast<uint32_t>(sp_instance->m_game_objects.size());
        }
        else
        {
            n_go++;
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

void CEngine::BehaviorAwake(CBehavior* p_behavior)
{
    p_behavior->Awake();
}

}