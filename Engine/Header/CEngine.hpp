/// \file       CEngine.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_ENGINE_HPP__
#define OOM_ENGINE_C_ENGINE_HPP__

#include <vector>
#include <GLM/glm.hpp>
#include <Composite/Component/CBehavior.hpp>

#include "Render/Config.hpp"

namespace Oom
{

// Forward declaration
// Basic   components
class CBehavior;
class CTransform;
class CGameObject;

// Engines
class CString;
class CRenderer;

class CEngine
{
public:

    bool Initialize ();
    void Release    ();
    void Run        ();

public:

    // Game objects
    static CGameObject*              Instantiate            ();
    static CGameObject*              Instantiate            (CTransform* parent);
    static CGameObject*              Instantiate            (const glm::vec3& position);
    static CGameObject*              Instantiate            (const glm::vec3& position, const glm::vec3& scale);
    static CGameObject*              Instantiate            (const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation);
    static void						 Destroy				(CGameObject* p_game_object);
    static void						 Destroy				(CGameObject* p_game_object, float delay);
    static void						 DestroyImmediate		(CGameObject* p_game_object);
    static CGameObject*				 Find					(const CString& name);
    static CGameObject*				 FindWithTag			(const CString& tag);
    static std::vector<CGameObject*> FindGameObjectsWithTag (const CString& tag);

public:

    // Tools
    static void               SetMousePosition  (const glm::vec2& position);
    static glm::tvec3<double> GetMousePosition  ();
    static glm::vec2          GetWindowSize     ();
    static bool               IsKeyPressed      (int key_code);
    static bool               IsKeyReleased     (int key_code);

private:

    friend class CBehavior;
    friend class CGameObject;

    void        GameObjectUpdate(GLFWwindow* p_window, float delta_time);
    void        BehaviorUpdate  (GLFWwindow* p_window, float delta_time);

    static void RegisterBehavior   (CBehavior* p_behavior);
    static void UnregisterBehavior (CBehavior* p_behavior);

private:

    static CEngine* sp_instance;

private:

    CRenderer*                mp_renderer = nullptr;
    std::vector<CBehavior*  > m_behaviors;
    std::vector<CGameObject*> m_game_objects;
};

}

#endif // !OOM_ENGINE_C_ENGINE_HPP__