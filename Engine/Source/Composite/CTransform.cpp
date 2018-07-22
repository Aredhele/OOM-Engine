/// \file       CTransform.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CGameObject.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

CTransform::CTransform()
{
    m_scale       = glm::vec3(1.0f);
    m_position    = glm::vec3(0.0f);
    m_orientation = glm::vec3(0.0f);

    m_up       = glm::vec3(0.0f, 0.0f, 1.0f);
    m_right    = glm::vec3(1.0f, 0.0f, 0.0f);
    m_forward  = glm::vec3(0.0f, 1.0f, 0.0f);
}

uint32_t CTransform::GetChildCount() const
{
    return static_cast<uint32_t>(m_childrens.size());
}

uint32_t CTransform::GetHierarchyCount() const
{
    uint32_t hierarchy_count = 0;
    for(const auto& transform : m_childrens)
        hierarchy_count += transform->GetHierarchyCount();

    return hierarchy_count;
}

const CTransform& CTransform::GetParent() const
{
    return *mp_parent;
}

const CTransform& CTransform::GetRoot() const
{
    return (mp_parent) ? mp_parent->GetRoot() : *this;
}

const glm::vec3& CTransform::GetUp() const
{
    return m_up;
}

const glm::vec3& CTransform::GetRight() const
{
    return m_right;
}

const glm::vec3 &CTransform::GetForward() const
{
    return m_forward;
}

const glm::vec3& CTransform::GetLocalPosition() const
{
    return m_position;
}

const glm::vec3& CTransform::GetLocalScale() const
{
    return m_scale;
}

const glm::vec3& CTransform::GetLocalOrientation() const
{
    return m_orientation;
}

glm::vec3 CTransform::GetWorldPosition() const
{
    return (mp_parent) ? m_position + mp_parent->GetWorldPosition() : m_position;
}

glm::vec3 CTransform::GetWorldScale() const
{
    return (mp_parent) ? m_scale * mp_parent->GetWorldScale() : m_scale;
}

glm::vec3 CTransform::GetWorldOrientation() const
{
    return (mp_parent) ? m_orientation * mp_parent->GetWorldOrientation() : m_orientation;
}

void CTransform::SetLocalScale(float x, float y, float z)
{
    SetLocalScale(glm::vec3(x, y, z));
}

void CTransform::SetLocalScale(const glm::vec3 &scale)
{
    m_scale = scale;
}

void CTransform::SetLocalPosition(float x, float y, float z)
{
    SetLocalPosition(glm::vec3(x, y, z));
}

void CTransform::SetLocalPosition(const glm::vec3& position)
{
    m_position = position;
    UpdateVectors();
}

void CTransform::SetLocalOrientation(float x, float y, float z)
{
    SetLocalOrientation(glm::vec3(x, y, z));
}

void CTransform::SetLocalOrientation(const glm::vec3& orientation)
{
    m_orientation = orientation;
    UpdateVectors();
}

void CTransform::SetWorldScale(float x, float y, float z)
{
    SetWorldScale(glm::vec3(x, y, z));
}

void CTransform::SetWorldScale(const glm::vec3 &scale)
{
    glm::vec3 world_scale = GetWorldScale();
    m_scale /= world_scale;
}

void CTransform::SetWorldPosition(float x, float y, float z)
{
    SetWorldPosition(glm::vec3(x, y, z));
}

void CTransform::SetWorldPosition(const glm::vec3 &position)
{
    glm::vec3 world_position = GetWorldPosition();
    m_position = position - world_position;
    UpdateVectors();
}

void CTransform::SetWorldOrientation(float x, float y, float z)
{
    SetWorldOrientation(glm::vec3(x, y, z));
}

void CTransform::SetWorldOrientation(const glm::vec3& orientation)
{
    glm::vec3 world_orientation = GetWorldOrientation();
    m_orientation = orientation - world_orientation;
    UpdateVectors();
}

const CTransform* CTransform::Find(const CString& name)
{
    // The wanted object could be this one
    if(mp_game_object->GetName() == name)
        return this;

    // Else, a child
    for(const auto& transform : m_childrens)
    {
        const CTransform* p_transform = transform->Find(name);

        if(p_transform)
            return p_transform;
    }

    // Else, there is no child with this name
    return nullptr;
}

void CTransform::LookAt(const CTransform& target)
{
    m_forward = target.m_position;
    UpdateVectors();
}

void CTransform::Rotate(float x, float y, float z)
{
    Rotate(glm::vec3(x, y, z));
}

void CTransform::Rotate(const glm::vec3& point)
{
    m_orientation += point;
    UpdateVectors();
}

void CTransform::RotateAround(const glm::vec3& point, const glm::vec3& axis, float angle)
{
    m_forward -= m_position;
    m_forward  = glm::rotate(point, angle, axis);
    m_forward += m_position;
    UpdateVectors();
}

void CTransform::SetParent(const CTransform& parent)
{
    mp_parent = &parent.mp_game_object->m_transform;
}

void CTransform::Translate(float x, float y, float z)
{
    Translate(glm::vec3(x, y, z));
}

void CTransform::Translate(const glm::vec3& translation)
{
    m_position += translation;
    UpdateVectors();
}

void CTransform::UpdateVectors()
{
    m_orientation  = m_forward;
    m_orientation -= m_position;
    m_orientation  = glm::normalize(m_orientation);

    m_up    = glm::vec3     (0.0f, 0.0f, 1.0f);
    m_right = glm::cross    (m_orientation, m_up);
    m_right = glm::normalize(m_right);
    m_up    = glm::cross    (m_right, m_orientation);
    m_up    = glm::normalize(m_up);
}

}