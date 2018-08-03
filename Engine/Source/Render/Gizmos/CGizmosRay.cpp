/// \file       CGizmosRay.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include "Render/Gizmos/CGizmosRay.hpp"
#include "Render/Gizmos/CGizmosManager.hpp"

namespace Oom
{

void DrawRay(glm::vec3 const& start, glm::vec3 const& dir, glm::vec3 const& color)
{
#ifndef NDEBUG
    if(!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::Ray))
        return;

    CGizmosManager::AddLine(start, start + dir, color);
#endif
}

}
