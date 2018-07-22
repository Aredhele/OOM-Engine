/// \file       CBound.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Resource
/// \author     Vincent STEHLY--CALISTO

#include "Resource/CBound.hpp"

namespace Oom
{

const glm::vec3& CBound::GetCenter() const
{ return m_center; }

const glm::vec3& CBound::GetExtents() const
{ return m_extents; }

void CBound::SetCenter(const glm::vec3& center)
{ m_center = center; }

void CBound::SetExtents(const glm::vec3& extents)
{ m_extents = extents; }

}