/// \file       CGameObject.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GAME_OBJECT_HPP__
#define OOM_ENGINE_C_GAME_OBJECT_HPP__

#include <vector>

#include "Composite/CObject.hpp"
#include "Core/Standard/CString.hpp"

// Components
#include "Composite/IComponent.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

class CGameObject : public CObject
{
public:

    // Properties
    const CString& GetTag () const;

    void SetTag     (const CString& tag);
    void SetTag     (CString&& tag);
    void SetActive  (bool active);

public:

    template <class T> inline T *				GetComponent			(/* void */);
    template <class T> inline std::vector<T*>  GetComponents			(/* void */);
    template <class T> inline T *				AddComponent			(/* void */);
    template <class T> inline void				RemoveComponent			(/* void */);
    template <class T> inline void				RemoveComponents		(/* void */);

private:

    // Properties
    CString m_tag;
    bool    m_is_active;
    bool    m_is_detroyed;
    float   m_destroy_delay;
    float   m_destroy_elapsed;

private:

    friend class CEngine;
    friend class CTransform;

             CGameObject();
    explicit CGameObject(const CTransform& parent);
             CGameObject(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation);

    void __DestroyMessage ();
    void __EnableMessage  ();
    void __DisableMessage ();

private:

    CTransform                m_transform;
    std::vector<IComponent* > m_components;
};

}

#include "Composite/Impl/CGameObject.inl"

#endif // !OOM_ENGINE_C_GAME_OBJECT_HPP__