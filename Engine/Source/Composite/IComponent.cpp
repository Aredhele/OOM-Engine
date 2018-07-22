/// \file       IComponent.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#include "Composite/IComponent.hpp"
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

const CString& IComponent::GetTag() const
{
    return m_tag;
}

const CTransform& IComponent::GetTransform() const
{
    return *mp_transform;
}

CGameObject* IComponent::GetGameObject() const
{
    return mp_game_object;
}

bool IComponent::IsEnabled() const
{
    return m_is_enabled;
}

void IComponent::SetTag(const CString& tag)
{
    m_tag = tag;
}

void IComponent::SetTag(CString&& tag)
{
    m_tag = static_cast<CString&&>(tag);
}

void IComponent::SetEnabled(bool enabled)
{
    if(m_is_enabled != enabled)
    {
        (enabled) ? OnEnable() : OnDisable();
        m_is_enabled = enabled;
    }
}

void IComponent::OnEnable()
{ /* None */ }

void IComponent::OnDisable()
{ /* None */ }

void IComponent::OnDestroy()
{ /* None */ }

void IComponent::__DestroyMessage()
{
    OnDestroy();
}

void IComponent::__EnableMessage()
{
    if(m_is_enabled)
        OnEnable();
}

void IComponent::__DisableMessage()
{
    if(m_is_enabled)
        OnDisable();
}

}
