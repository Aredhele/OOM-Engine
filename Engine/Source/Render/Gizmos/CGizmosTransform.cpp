/// \file       CGizmosTransform.cpp
/// \date       07/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include "Render/Gizmos/CGizmosManager.hpp"
#include "Render/Gizmos/CGizmosTransform.hpp"

namespace Oom
{

void DrawTransform(const glm::vec3& position, const glm::vec3& up, const glm::vec3& right, const glm::vec3& forward, const glm::vec3& target)
{
	if (!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::Transform))
		return;

	// Axis
	CGizmosManager::AddLine(position, position + up      * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	CGizmosManager::AddLine(position, position + right   * 5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	CGizmosManager::AddLine(position, position + forward * 5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

}
