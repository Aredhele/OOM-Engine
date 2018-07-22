/// \file       CGameObject.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CGameObject.hpp"

namespace Oom
{

CGameObject::CGameObject()
: CGameObject(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f))
{
    // None
}

CGameObject::CGameObject(CTransform& parent)
{
    m_tag             = "Default";
    m_is_active       = true;
    m_is_destroyed    = false;
    m_destroy_delay   = 0.0f;
    m_destroy_elapsed = 0.0f;

    m_transform.mp_game_object = this;
    m_transform.SetParent(parent);
}

CGameObject::CGameObject(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation)
{
    m_tag             = "Default";
    m_is_active       = true;
    m_is_destroyed    = false;
    m_destroy_delay   = 0.0f;
    m_destroy_elapsed = 0.0f;

    m_transform.SetLocalScale(scale);
    m_transform.SetLocalPosition(position);
    m_transform.SetLocalOrientation(orientation);

    m_transform.mp_game_object = this;
}

const CString& CGameObject::GetTag() const
{
    return m_tag;
}

bool CGameObject::IsActive() const
{
    return m_is_active;
}

CTransform& CGameObject::GetTransform()
{
    return m_transform;
}

void CGameObject::SetTag(const CString& tag)
{
    m_tag = tag;
}

void CGameObject::SetTag(CString&& tag)
{
    m_tag = static_cast<CString&&>(tag);
}

void CGameObject::SetActive(bool active)
{
    if(m_is_active != active)
    {
        (active) ? __EnableMessage() :
                   __DisableMessage();
        m_is_active = active;
    }
}

void CGameObject::__DestroyMessage()
{
    for(IComponent* p_component : m_components)
        p_component->__DestroyMessage();
}

void CGameObject::__EnableMessage()
{
    for(IComponent* p_component : m_components)
        p_component->__EnableMessage();

    for(CTransform* p_transform : m_transform.GetChildren())
        p_transform->GetGameObject()->__EnableMessage();
}

void CGameObject::__DisableMessage()
{
    for(IComponent* p_component : m_components)
        p_component->__DisableMessage();

    for(CTransform* p_transform : m_transform.GetChildren())
        p_transform->GetGameObject()->__DisableMessage();
}

}