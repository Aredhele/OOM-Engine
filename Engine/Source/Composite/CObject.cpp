/// \file       CObject.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CObject.hpp"

namespace Oom
{

void CObject::SetName(const CString &name)
{ m_name = name; }

void CObject::SetName(CString&& name)
{ m_name = static_cast<CString&&>(name); }

const CString &CObject::GetName() const
{ return m_name; }

}