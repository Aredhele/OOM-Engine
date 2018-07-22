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

const CGameObject& IComponent::GetGameObject() const
{
    return *mp_game_object;
}

void IComponent::SetTag(const CString& tag)
{
    m_tag = tag;
}

void IComponent::SetTag(CString&& tag)
{
    m_tag = static_cast<CString&&>(tag);
}

}
