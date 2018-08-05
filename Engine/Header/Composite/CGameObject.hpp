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

// Forward declaration
class CBehavior;

class CGameObject : public CObject
{
public:

    // Properties
    const CString& GetTag       () const;
    bool           IsActive     () const;
    CTransform&    GetTransform ();

    void SetTag     (const CString& tag);
    void SetTag     (CString&& tag);
    void SetActive  (bool active);

public:

    template <class T> inline T *		GetComponent			(/* void */);
    template <class T>
    inline std::vector<T*>              GetComponents			(/* void */);
    template <class T> inline T *		AddComponent			(/* void */);
    template <class T> inline void		RemoveComponent			(/* void */);
    template <class T> inline void		RemoveComponents		(/* void */);
    inline void                         RemoveComponents        (/* void */);

    static CGameObject*                 Instantiate             ();
    static CGameObject*                 Instantiate             (CTransform* parent);
    static CGameObject*                 Instantiate             (const glm::vec3& position);
    static CGameObject*                 Instantiate             (const glm::vec3& position, const glm::vec3& scale);
    static CGameObject*                 Instantiate             (const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation);
    static void						    Destroy				    (CGameObject* p_game_object);
    static void						    Destroy				    (CGameObject* p_game_object, float delay);
    static void						    DestroyImmediate		(CGameObject* p_game_object);
    static CGameObject*				    Find					(const CString& name);
    static CGameObject*				    FindWithTag			    (const CString& tag);
    static std::vector<CGameObject*>    FindGameObjectsWithTag  (const CString& tag);

private:

    // Properties
    CString m_tag;
    bool    m_is_active;
    bool    m_is_destroyed;
    float   m_destroy_delay;
    float   m_destroy_elapsed;

private:

    friend class CEngine;
    friend class CTransform;
	friend class CContactListener;

             CGameObject();
    explicit CGameObject(CTransform* parent);
             CGameObject(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation);

    void                    __DestroyMessage ();
    void                    __EnableMessage  ();
    void                    __DisableMessage ();
	std::vector<CBehavior*> __GetBehaviors   ();

private:

    CTransform                m_transform;
    std::vector<IComponent* > m_components;
};

}

#include "Composite/Impl/CGameObject.inl"

#endif // !OOM_ENGINE_C_GAME_OBJECT_HPP__