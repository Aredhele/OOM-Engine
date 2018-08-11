/// \file       CEngine.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

// User code
#include "Scene/Hook.hpp"

// Engines
#include "Engine/CEngine.hpp"
#include "Render/CRenderer.hpp"
#include "Audio/CAudioEngine.hpp"
#include "Physics/CPhysicWorld.hpp"

// Components
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"
#include "Composite/Component/CTransform.hpp"

// Globals
#include "Engine/CTime.hpp"
#include "Engine/CConfig.hpp"

// Misc
#include "Render/CWindow.hpp"
#include "Core/Debug/SLogger.hpp"
#include "Render/Renderer/CTextRenderer.hpp"
#include "Render/Renderer/CUISpriteRenderer.hpp"

#include "Render/Gizmos/CGizmosManager.hpp"
#include "Render/Gizmos/CGizmosTransform.hpp"

namespace Oom
{

/* static */ CEngine* CEngine::sp_instance = nullptr;

bool CEngine::Initialize()
{
    SLogger::LogInfo("Oom-Engine initialization.");

	// Getting engine parameters
	ReadConfiguration();

	// Change the window name with the game name
	SRendererCreateInfo renderer_create_info {};
	renderer_create_info.window_name   = "Engine";
	renderer_create_info.full_screen   = CConfig::window_full_screen;
	renderer_create_info.opengl_major  = CConfig::opengl_version_major;
	renderer_create_info.opengl_minor  = CConfig::opengl_version_minor;
	renderer_create_info.window_width  = CConfig::default_window_width;
	renderer_create_info.window_height = CConfig::default_window_height;

	renderer_create_info.enable_anti_aliasing   = CConfig::enable_anti_aliasing;
	renderer_create_info.enable_post_processing = CConfig::enable_post_processing;
	
	// Initializing the rendering engine
    mp_renderer = new CRenderer();
    mp_renderer->Initialize(renderer_create_info);

	SPhysicWorldCreateInfo world_create_info {};
	world_create_info.delta_time =  1.0f / CConfig::default_update_per_second;
	world_create_info.gravity_x  =  0.0f;
	world_create_info.gravity_y  =  0.0f;
	world_create_info.gravity_z  = -9.81f;

    mp_physic_world = new CPhysicWorld();
    mp_physic_world->Initialize(world_create_info);

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

	if(mp_renderer)
	{
		mp_renderer->Release();
		delete mp_renderer;
	}

    mp_renderer = nullptr;
    sp_instance = nullptr;

    SLogger::LogInfo("Oom-Engine released.");
}

void CEngine::ReadConfiguration()
{
	SLogger::LogInfo("Reading engine configuration...");

	// Rendering
	const bool b_enable_post_processing = GetPrivateProfileInt("Rendering", "enable_post_processing", 1, "Resources/Engine.ini");
	const bool b_enable_anti_aliasing   = GetPrivateProfileInt("Rendering", "enable_anti_aliasing",   1, "Resources/Engine.ini");
		  int  opengl_version_major     = GetPrivateProfileInt("Rendering", "opengl_version_major",   3, "Resources/Engine.ini");
		  int  opengl_version_minor     = GetPrivateProfileInt("Rendering", "opengl_version_minor",   3, "Resources/Engine.ini");

	// Window
	int        window_size_width  = GetPrivateProfileInt("Window", "window_size_width",  1600, "Resources/Engine.ini");
	int        window_size_height = GetPrivateProfileInt("Window", "window_size_height",  900, "Resources/Engine.ini");
	const bool window_full_screen = GetPrivateProfileInt("Window", "window_full_screen",    0, "Resources/Engine.ini");
	
	// Logic
	int update_per_second   = GetPrivateProfileInt("Logic", "update_per_second", 60, "Resources/Engine.ini");

	// Checking arguments
	if(opengl_version_major < 3 || opengl_version_minor < 3)
	{
		SLogger::LogError("OpenGL bad version. Taking the default value (3.3).");
		opengl_version_major = 3;
		opengl_version_minor = 3;
	}

	const float ratio = 16.0f / 9.0f;
	if(ratio != ((float)window_size_width / (float)window_size_height))
	{
		SLogger::LogError("The window size is not a 16:9 ratio. Taking the default value (1600x900).");
		window_size_width  = 1600;
		window_size_height = 900;
	}

	if(update_per_second <= 25 || update_per_second >= 240)
	{
		SLogger::LogError("The update count is too low or too hight. Taking the default value (60).");
		update_per_second = 60;
	}

	// Updating the config
	CConfig::window_full_screen     = window_full_screen;
	CConfig::enable_anti_aliasing   = b_enable_anti_aliasing;
	CConfig::enable_post_processing = b_enable_post_processing;

	CConfig::opengl_version_major      = opengl_version_major;
	CConfig::opengl_version_minor      = opengl_version_minor;
	CConfig::default_window_width      = window_size_width;
	CConfig::default_window_height     = window_size_height;
	CConfig::default_update_per_second = update_per_second;

	SLogger::LogInfo("Read %s : %d", "enable_post_processing", b_enable_post_processing);
	SLogger::LogInfo("Read %s : %d", "enable_anti_aliasing  ", b_enable_anti_aliasing);
	SLogger::LogInfo("Read %s : %d", "opengl_version_major  ", opengl_version_major);
	SLogger::LogInfo("Read %s : %d", "opengl_version_minor  ", opengl_version_minor);
	SLogger::LogInfo("Read %s : %d", "window_size_width     ", window_size_width);
	SLogger::LogInfo("Read %s : %d", "window_size_height    ", window_size_height);
	SLogger::LogInfo("Read %s : %d", "window_full_screen    ", window_full_screen);
	SLogger::LogInfo("Read %s : %d", "update_per_second     ", update_per_second);

	SLogger::LogInfo("Configuration filed parsed.");
}

void CEngine::Run()
{
	m_running = true;

    // Getting GLFW window
    GLFWwindow* p_handle = mp_renderer->GetWindow()->GetHandle();

    double lag              = 0.0;
    double previous         = glfwGetTime();
    const double delta_time = 1.0 / CConfig::default_update_per_second;

    // Setting up the scene
    LoadScene();

    while (m_running && 
		   glfwWindowShouldClose(p_handle) == 0 &&
           glfwGetKey(p_handle, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        const double current = glfwGetTime();
		const double elapsed = current - previous;
        previous             = current;

        lag += elapsed;

        // Processing events
        glfwPollEvents();

        // Fixed granularity
        while(lag >= delta_time)
        {
			// Updating the time manager
			CTime::time      += delta_time;
			CTime::delta_time = delta_time;

            BehaviorUpdate  (p_handle, static_cast<float>(delta_time));
            GameObjectUpdate(p_handle, static_cast<float>(delta_time));

            lag -= delta_time;

			// The physic world needs a fixed update
			mp_physic_world->Update();
			mp_audio_engine->Update(delta_time);
        }

        mp_renderer->Render();
    }
}

void CEngine::BehaviorUpdate(GLFWwindow* p_window, float delta_time)
{
    // Behavior updates
    const auto behavior_count = static_cast<uint32_t>(m_behaviors.size());
    for(uint32_t i = 0; i < behavior_count; ++i)
    {
        auto* p_behavior = m_behaviors[i];
		auto* p_go       = p_behavior->GetGameObject();

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

void CEngine::GameObjectUpdate(GLFWwindow* p_window, const float delta_time)
{
    // Game objects life cycle check
    auto go_count = static_cast<uint32_t>(m_game_objects.size());
    for(uint32_t n_go = 0; n_go < go_count; /* no increment */)
    {
        auto* p_game_object = m_game_objects[n_go];
		auto& p_transform   = p_game_object->GetTransform();

		if(!(p_game_object->GetComponent<CTextRenderer>() || 
			 p_game_object->GetComponent<CUISpriteRenderer>()))
		{
			if (CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::AllTransforms))
			{
				DrawTransform(
					p_transform.GetPosition(), p_transform.GetUp(),
					p_transform.GetRight(), p_transform.GetForward());
			}
		}
		
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
    return Instantiate((position), glm::vec3(1.0f), glm::vec3(0.0f));
}

/* static */ CGameObject* CEngine::Instantiate(const glm::vec3& position, const glm::vec3& scale)
{
    return Instantiate((position), glm::vec3(1.0f), glm::vec3(0.0f));
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

/* static */ void CEngine::ShowMouse()
{
	glfwSetInputMode(sp_instance->mp_renderer->GetWindow()->GetHandle(), 
		GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

/* static */ void CEngine::HideMouse()
{
	glfwSetInputMode(sp_instance->mp_renderer->GetWindow()->GetHandle(), 
		GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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

/* static */ bool CEngine::IsMouseButtonPressed(int button)
{
	return (glfwGetMouseButton(sp_instance->mp_renderer->GetWindow()->GetHandle(), button) == GLFW_PRESS);
}

/* static */ bool CEngine::IsMouseButtonReleased(int button)
{
	return (glfwGetMouseButton(sp_instance->mp_renderer->GetWindow()->GetHandle(), button) == GLFW_RELEASE);
}

/* static */ void CEngine::Exit()
{
	sp_instance->m_running = false;
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
{
	return sp_instance->m_game_objects;
}

}
