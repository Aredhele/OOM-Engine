/// \file       CGizmosLine.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include "Render/Gizmos/CGizmosLine.hpp"
#include "Render/Gizmos/CGizmosManager.hpp"

namespace Oom
{

void DrawLine(glm::vec3 const& start, glm::vec3 const& end, glm::vec3 const& color)
{
    if(!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::Line))
        return;

    CGizmosManager::AddLine(start, end, color);
}

}
