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

CGameObject::CGameObject(const CTransform& parent)
{
    m_tag             = "Default";
    m_is_active       = true;
    m_is_detroyed     = false;
    m_destroy_delay   = 0.0f;
    m_destroy_elapsed = 0.0f;

    // TODO
}

CGameObject::CGameObject(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation)
{
    m_tag             = "Default";
    m_is_active       = true;
    m_is_detroyed     = false;
    m_destroy_delay   = 0.0f;
    m_destroy_elapsed = 0.0f;

    // TODO
}

const CString& CGameObject::GetTag() const
{
    return m_tag;
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
    m_is_active = active;
    // TODO
}

void CGameObject::__DestroyMessage()
{

}

void CGameObject::__EnableMessage()
{

}

void CGameObject::__DisableMessage()
{

}

}