/// \file       IComponent.hpp
/// \date       22/07/2018 
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_COMPONENT_HPP__
#define OOM_ENGINE_I_COMPONENT_HPP__

#include <vector>
#include <GLM/glm.hpp>
#include "Composite/CObject.hpp"

namespace Oom
{

// Forward declaration
class CGameObject;
class CTransform;

class IComponent : public CObject
{
public:

    // Properties
    const CString&      GetTag        () const;
          CTransform*   GetTransform  ();
          CGameObject*  GetGameObject ();
    bool                IsEnabled     () const;
    void                SetTag        (const CString& tag);
    void                SetTag        (CString&& tag);
    void                SetEnabled    (bool enabled);

public:

    // Methods
    virtual void OnEnable  ();
    virtual void OnDisable ();
    virtual void OnDestroy ();

    // Useful ?
    // template <class T> inline T *				      GetComponent			(/* void */);
    // template <class T> inline std::vector<T*>          GetComponents			(/* void */);

    static CGameObject*                 Instantiate             ();
    static CGameObject*                 Instantiate             (CTransform* parent);
    static CGameObject*                 Instantiate             (const glm::vec3& position);
    static CGameObject*                 Instantiate             (const glm::vec3& position, const glm::vec3& scale);
    static CGameObject*                 Instantiate             (const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation);
    static void						    Destroy				    (CGameObject* p_game_object);
    static void						    Destroy				    (CGameObject* p_game_object, float delay);
    static void						    DestroyImmediate		(CGameObject* p_game_object);

protected:

    virtual void _Register () = 0;
    virtual void _Destroy  () = 0;

protected:

    CString      m_tag;
    CTransform*  mp_transform   = nullptr;
    CGameObject* mp_game_object = nullptr;
    bool         m_is_enabled   = true;

protected:

    uint32_t    m_component_id  = 0;

private:

    friend class CEngine;
    friend class CGameObject;

    void __DestroyMessage ();
    void __EnableMessage  ();
    void __DisableMessage ();
};

}

#include "Composite/Impl/IComponent.inl"

#endif // !OOM_ENGINE_I_COMPONENT_HPP__