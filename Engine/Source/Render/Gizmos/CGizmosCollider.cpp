/// \file       CGizmosBox.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include "Render/Gizmos/CGizmosManager.hpp"
#include "Render/Gizmos/CGizmosCollider.hpp"

#include "GLM/gtx/transform.hpp"
#include "GLM/gtx/euler_angles.hpp"

namespace Oom
{

void DrawCollider(const glm::vec3& position, const glm::vec3& extent, const glm::vec3& euler, const glm::vec3& color)
{
	if (!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::Collider))
		return;

	float halfWidth  = extent.x / 2.0f;
	float halfDepth  = extent.y / 2.0f;
	float halfHeight = extent.z / 2.0f;

	glm::mat4 translation = glm::translate(position);
	glm::mat4 rotation    = glm::orientate4(euler);

	const glm::vec3 A = translation * rotation * glm::vec4(-halfWidth,  halfDepth, -halfHeight, 1.0f);
	const glm::vec3 B = translation * rotation * glm::vec4( halfWidth,  halfDepth, -halfHeight, 1.0f);
	const glm::vec3 C = translation * rotation * glm::vec4( halfWidth, -halfDepth, -halfHeight, 1.0f);
	const glm::vec3 D = translation * rotation * glm::vec4(-halfWidth, -halfDepth, -halfHeight, 1.0f);
	const glm::vec3 E = translation * rotation * glm::vec4(-halfWidth,  halfDepth,  halfHeight, 1.0f);
	const glm::vec3 F = translation * rotation * glm::vec4( halfWidth,  halfDepth,  halfHeight, 1.0f);
	const glm::vec3 G = translation * rotation * glm::vec4( halfWidth, -halfDepth,  halfHeight, 1.0f);
	const glm::vec3 H = translation * rotation * glm::vec4(-halfWidth, -halfDepth,  halfHeight, 1.0f);

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
