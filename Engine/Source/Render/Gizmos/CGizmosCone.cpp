/// \file       CGizmosCone.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"

#ifndef _USE_MATH_DEFINES
#	define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <GLM/gtc/constants.hpp>
#include "Render/Gizmos/CGizmosCone.hpp"
#include "Render/Gizmos/CGizmosManager.hpp"

namespace Oom
{
void DrawCone(glm::vec3 const& position, float radius,  float topRadius, float lenght, glm::vec3 const& color)
{
    if(!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::Cone))
        return;

    // Compute spherical coordinates
    int pointCount = static_cast<int>(20 * radius); // NOLINT
    float alpha    = (360.0f * (glm::pi<float>() / 180.0f)) / pointCount;

    std::vector<glm::vec3> points;
    for (int nPoint = 0; nPoint < pointCount; ++nPoint)
    {
        float x1 = position.x + glm::cos(alpha * nPoint) * radius;
        float y1 = position.y + glm::sin(alpha * nPoint) * radius;
        float z1 = position.z;

        points.emplace_back(x1, y1, z1);

        if(nPoint != 0)
            CGizmosManager::AddLine(points[nPoint - 1], points[nPoint], color);
    }

    // Adding last points
    CGizmosManager::AddLine(points[0], points[points.size() - 1], color);

    // Compute spherical coordinates
    pointCount = static_cast<int>(32 * topRadius); // NOLINT
    alpha      = (360.0f * (glm::pi<float>() / 180.0f)) / pointCount;

    points.clear();
    for (int nPoint = 0; nPoint < pointCount; ++nPoint)
    {
        float x1 = position.x + glm::cos(alpha * nPoint) * topRadius;
        float y1 = position.y + glm::sin(alpha * nPoint) * topRadius;
        float z1 = position.z + lenght;

        points.emplace_back(x1, y1, z1);

        if(nPoint != 0)
            CGizmosManager::AddLine(points[nPoint - 1], points[nPoint], color);
    }

    // Adding last points
    CGizmosManager::AddLine(points[0], points[points.size() - 1], color);

    // Add 4 four side lines
    CGizmosManager::AddLine(glm::vec3(position.x + glm::cos(0) * radius,    position.y + glm::sin(0) * radius,    position.z),
                          glm::vec3(position.x   + glm::cos(0) * topRadius, position.y + glm::sin(0) * topRadius, position.z + lenght), color);

    CGizmosManager::AddLine(glm::vec3(position.x + glm::cos(M_PI_2) * radius,    position.y + glm::sin(M_PI_2) * radius,    position.z),
                          glm::vec3(position.x   + glm::cos(M_PI_2) * topRadius, position.y + glm::sin(M_PI_2) * topRadius, position.z + lenght), color);

    CGizmosManager::AddLine(glm::vec3(position.x + glm::cos(M_PI) * radius,    position.y + glm::sin(M_PI) * radius,    position.z),
                          glm::vec3(position.x   + glm::cos(M_PI) * topRadius, position.y + glm::sin(M_PI) * topRadius, position.z + lenght), color);

    CGizmosManager::AddLine(glm::vec3(position.x + glm::cos(M_PI + M_PI_2) * radius,    position.y + glm::sin(M_PI + M_PI_2) * radius,    position.z),
                          glm::vec3(position.x   + glm::cos(M_PI + M_PI_2) * topRadius, position.y + glm::sin(M_PI + M_PI_2) * topRadius, position.z + lenght), color);
}

}
