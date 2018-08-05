/// \file       CGizmosPointLight.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include <GLM/gtc/constants.hpp>
#include "Render/Gizmos/CGizmosManager.hpp"
#include "Render/Gizmos/CGizmosPointLight.hpp"

namespace Oom
{

void DrawPointLight(glm::vec3 const& position, glm::vec3 const& color, int resolution, float range, float scale)
{
    if(!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::PointLight))
        return;

    // Compute spherical coordinates
    int pointCount = static_cast<int>(resolution * scale); // NOLINT
    float alpha    = (360.0f * (glm::pi<float>() / 180.0f)) / pointCount;

    std::vector<glm::vec3> pointsZ;
    std::vector<glm::vec3> pointsY;
    for (int nPoint = 0; nPoint < pointCount; ++nPoint)
    {
        float x1 = position.x + glm::cos(alpha * nPoint) * range;
        float y1 = position.y + glm::sin(alpha * nPoint) * range;
        float z1 = position.z;

        float x2 = position.x;
        float y2 = position.y + glm::sin(alpha * nPoint) * range;
        float z2 = position.z + glm::cos(alpha * nPoint) * range;

        pointsZ.emplace_back(x1, y1, z1);
        pointsY.emplace_back(x2, y2, z2);

        if(nPoint != 0)
        {
            CGizmosManager::AddLine(pointsZ[nPoint - 1], pointsZ[nPoint], color);
            CGizmosManager::AddLine(pointsY[nPoint - 1], pointsY[nPoint], color);
        }
    }

    // Adding last points
    CGizmosManager::AddLine(pointsZ[0], pointsZ[pointsZ.size() - 1], color);
    CGizmosManager::AddLine(pointsY[0], pointsY[pointsY.size() - 1], color);

    // Adding light at the center
    glm::vec3 top  (position.x, position.y, position.z + 2.0f * scale);
    glm::vec3 bot  (position.x, position.y, position.z - 2.0f * scale);
    glm::vec3 left (position.x - 1.0f * scale, position.y, position.z);
    glm::vec3 right(position.x + 1.0f * scale, position.y, position.z);
    glm::vec3 front(position.x, position.y + 1.0f * scale, position.z);
    glm::vec3 back (position.x, position.y - 1.0f * scale, position.z);

    glm::vec3 rayLeftStart (left.x - 1.0f,         left.y, left.z);
    glm::vec3 rayLeftEnd   (left.x - 2.0f * scale, left.y, left.z);

    glm::vec3 rayRightStart(right.x + 1.0f,         right.y, right.z);
    glm::vec3 rayRightEnd  (right.x + 2.0f * scale, right.y, right.z);
    glm::vec3 rayFrontStart(front.x, front.y + 1.0f,         front.z);
    glm::vec3 rayFrontEnd  (front.x, front.y + 2.0f * scale, front.z);

    glm::vec3 rayBackStart (back.x, back.y - 1.0f,         back.z);
    glm::vec3 rayBackEnd   (back.x, back.y - 2.0f * scale, back.z);

    CGizmosManager::AddLine(top, left,  color);
    CGizmosManager::AddLine(top, right, color);
    CGizmosManager::AddLine(top, front, color);
    CGizmosManager::AddLine(top, back,  color);

    CGizmosManager::AddLine(bot, left,  color);
    CGizmosManager::AddLine(bot, right, color);
    CGizmosManager::AddLine(bot, front, color);
    CGizmosManager::AddLine(bot, back,  color);

    CGizmosManager::AddLine(right,  back,  color);
    CGizmosManager::AddLine(right, front,  color);
    CGizmosManager::AddLine(front, left,   color);
    CGizmosManager::AddLine(back,  left,   color);

    CGizmosManager::AddLine(rayLeftStart,  rayLeftEnd,  color);
    CGizmosManager::AddLine(rayRightStart, rayRightEnd, color);
    CGizmosManager::AddLine(rayFrontStart, rayFrontEnd, color);
    CGizmosManager::AddLine(rayBackStart,  rayBackEnd,  color);
}

}
