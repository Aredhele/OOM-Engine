/// \file       CEngine.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_ENGINE_HPP__
#define OOM_ENGINE_C_ENGINE_HPP__

#include <vector>
#include <GLM/glm.hpp>

#include "Render/CRenderer.hpp"
#include "Core/Standard/CString.hpp"

namespace Oom
{

// Forward declaration
class CBehavior;
class CTransform;
class CGameObject;

class CEngine
{
public:

    bool Initialize ();
    void Release    ();
    void Run        ();

public:

    static CGameObject*              Instantiate            ();
    static CGameObject*              Instantiate            (CTransform& parent );
    static CGameObject*              Instantiate            (const glm::vec3& position);
    static CGameObject*              Instantiate            (const glm::vec3& position, const glm::vec3& scale);
    static CGameObject*              Instantiate            (const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation);
    static void						 Destroy				(CGameObject* p_game_object);
    static void						 Destroy				(CGameObject* p_game_object, float delay);
    static void						 DestroyImmediate		(CGameObject* p_game_object);
    static CGameObject*				 Find					(const CString& name);
    static CGameObject*				 FindWithTag			(const CString& tag);
    static std::vector<CGameObject*> FindGameObjectsWithTag (const CString& tag);

    template <class T> static inline T*   AllocateComponent();
    template <class T> static inline void ReleaseComponent (T* p_component);

    static void BehaviorAwake(CBehavior* p_behavior);

private:

    void BehaviorUpdate  (GLFWwindow* p_window, float delta_time);
    void GameObjectUpdate(GLFWwindow* p_window, float delta_time);

private:

    static CEngine* sp_instance;

private:

    CRenderer*                mp_renderer = nullptr;
    std::vector<CBehavior*  > m_behaviors;
    std::vector<CGameObject*> m_game_objects;
};

}

#include "CEngine.inl"

#endif // !OOM_ENGINE_C_ENGINE_HPP__