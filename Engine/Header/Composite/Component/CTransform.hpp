/// \file       CTransform.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_TRANSFORM_HPP__
#define OOM_ENGINE_C_TRANSFORM_HPP__

#include <vector>

#include "Render/Config.hpp"
#include "Composite/IComponent.hpp"

#include <GLM/glm.hpp>
#include <GLM/gtx/rotate_vector.hpp>

namespace Oom
{

class CTransform : public IComponent
{
public:

    CTransform();

public:

    // Properties
    uint32_t            GetChildCount       () const;
    uint32_t            GetHierarchyCount   () const;
    const CTransform&   GetParent           () const;
    const CTransform&   GetRoot             () const;
    const glm::vec3&    GetUp               () const;
    const glm::vec3&    GetRight            () const;
    const glm::vec3&    GetForward          () const;
    const glm::vec3&    GetLocalPosition    () const;
    const glm::vec3&    GetLocalScale       () const;
    const glm::vec3&    GetLocalOrientation () const;
          glm::vec3     GetWorldPosition    () const;
          glm::vec3     GetWorldScale       () const;
          glm::vec3     GetWorldOrientation () const;

    void SetLocalScale       (const glm::vec3& scale);
    void SetLocalScale       (float x, float y, float z);
    void SetLocalPosition    (const glm::vec3& position);
    void SetLocalPosition    (float x, float y, float z);
    void SetLocalOrientation (const glm::vec3& orientation);
    void SetLocalOrientation (float x, float y, float z);

    void SetWorldScale       (const glm::vec3& scale);
    void SetWorldScale       (float x, float y, float z);
    void SetWorldPosition    (const glm::vec3& position);
    void SetWorldPosition    (float x, float y, float z);
    void SetWorldOrientation (const glm::vec3& orientation);
    void SetWorldOrientation (float x, float y, float z);

    // TODO : Local to matrix world

public:

    // Methods
    const CTransform*   Find            (const CString& name);
    void                LookAt          (const CTransform& target);
    void                Rotate          (float x, float y, float z);
    void                Rotate          (const glm::vec3& point);
    void                RotateAround    (const glm::vec3& point, const glm::vec3& axis, float angle);
    void                SetParent       (CTransform& parent);
    void                Translate       (float x, float y, float z);
    void                Translate       (const glm::vec3& translation);

public:

    std::vector<CTransform*>& GetChildren();

private:

    void                UpdateVectors   ();

private:

    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_orientation;

    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_forward;

private:

    friend class CGameObject;

    CTransform*  mp_parent      = nullptr;
    CGameObject* mp_game_object = nullptr;

    std::vector<CTransform*>    m_children;
};

}

#endif // !OOM_ENGINE_C_TRANSFORM_HPP__