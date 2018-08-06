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

	// Target
	const float halfWidth  = 0.5f / 2.0f;
	const float halfHeight = 0.5f / 2.0f;

	const glm::vec3 color(0.3f, 0.5f, 0.7f);
	const glm::vec3 A(position.x - halfWidth, position.y + halfWidth, position.z - halfHeight);
	const glm::vec3 B(position.x + halfWidth, position.y + halfWidth, position.z - halfHeight);
	const glm::vec3 C(position.x + halfWidth, position.y - halfWidth, position.z - halfHeight);
	const glm::vec3 D(position.x - halfWidth, position.y - halfWidth, position.z - halfHeight);
	const glm::vec3 E(position.x - halfWidth, position.y + halfWidth, position.z + halfHeight);
	const glm::vec3 F(position.x + halfWidth, position.y + halfWidth, position.z + halfHeight);
	const glm::vec3 G(position.x + halfWidth, position.y - halfWidth, position.z + halfHeight);
	const glm::vec3 H(position.x - halfWidth, position.y - halfWidth, position.z + halfHeight);

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
}

}
