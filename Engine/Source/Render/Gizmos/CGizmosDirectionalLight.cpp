/// \file       CGizmosDirectionalLight.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include <GLM/gtc/constants.hpp>
#include "Render/Gizmos/CGizmosManager.hpp"
#include "Render/Gizmos/CGizmosDirectionalLight.hpp"

namespace Oom
{

void DrawDirectionalLight(glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& color, float scale)
{
#ifndef NDEBUG
    if(!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::DirectionalLight))
        return;

    glm::vec3 dir = glm::normalize(direction) * 5.0f;
    glm::vec3 top  (position.x, position.y, position.z + 2.0f * scale);
    glm::vec3 bot  (position.x, position.y, position.z - 2.0f * scale);
    glm::vec3 left (position.x - 1.0f * scale, position.y, position.z);
    glm::vec3 right(position.x + 1.0f * scale, position.y, position.z);
    glm::vec3 front(position.x, position.y + 1.0f * scale, position.z);
    glm::vec3 back (position.x, position.y - 1.0f * scale, position.z);

    glm::vec3 arrowStart(bot.x, bot.y, bot.z - 1.0f);
    glm::vec3 arrowEnd  (arrowStart + dir);

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

    CGizmosManager::AddLine(arrowStart, arrowEnd, glm::vec3(0.8f, 0.0f, 0.0f));
#endif
}


}
