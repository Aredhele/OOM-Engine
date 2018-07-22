/// \file       CGameObject.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CGameObject.hpp"

namespace Oom
{

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

}