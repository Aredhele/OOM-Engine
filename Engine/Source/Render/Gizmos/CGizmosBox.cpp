/// \file       CGizmosBox.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include "Render/Gizmos/CGizmosBox.hpp"
#include "Render/Gizmos/CGizmosManager.hpp"

namespace Oom
{

void DrawBox(glm::vec3 const& center, float width, float height, glm::vec3 const& color)
{
#ifndef NDEBUG
    if(!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::Box))
        return;

    float halfWidth  = width  / 2.0f;
    float halfHeight = height / 2.0f;

    glm::vec3 A(center.x - halfWidth, center.y + halfWidth, center.z - halfHeight);
    glm::vec3 B(center.x + halfWidth, center.y + halfWidth, center.z - halfHeight);
    glm::vec3 C(center.x + halfWidth, center.y - halfWidth, center.z - halfHeight);
    glm::vec3 D(center.x - halfWidth, center.y - halfWidth, center.z - halfHeight);
    glm::vec3 E(center.x - halfWidth, center.y + halfWidth, center.z + halfHeight);
    glm::vec3 F(center.x + halfWidth, center.y + halfWidth, center.z + halfHeight);
    glm::vec3 G(center.x + halfWidth, center.y - halfWidth, center.z + halfHeight);
    glm::vec3 H(center.x - halfWidth, center.y - halfWidth, center.z + halfHeight);

    CGizmosManager::AddLine(A, B, color);
    CGizmosManager::AddLine(B, C, color);
    CGizmosManager::AddLine(C, D, color);
    CGizmosManager::AddLine(D, A, color);

    CGizmosManager::AddLine(A, E, color);
    CGizmosManager::AddLine(B, F, color);
    CGizmosManager::AddLine(C, G, color);
    CGizmosManager::AddLine(D, H, color);

    CGizmosManager::AddLine(E, F, color);
    CGizmosManager::AddLine(F, G, color);
    CGizmosManager::AddLine(G, H, color);
    CGizmosManager::AddLine(H, E, color);
#endif
}

}
