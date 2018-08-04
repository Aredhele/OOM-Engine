/// \file       CGizmosAudioSource.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include <GLM/gtc/constants.hpp>
#include "Render/Gizmos/CGizmosManager.hpp"
#include "Render/Gizmos/CGizmosAudioSource.hpp"

namespace Oom
{

void DrawAudioSource(glm::vec3 const& position, float distance_min, float distance_max, int resolution, float scale)
{
#ifndef NDEBUG
	if (!CGizmosManager::IsGizmoEnabled(CGizmosManager::EGizmo::AudioSource))
		return;

	// Compute spherical coordinates
	int pointCount = static_cast<int>(resolution * scale); // NOLINT
	float alpha    = (360.0f * (glm::pi<float>() / 180.0f)) / pointCount;

	// Min circle
	std::vector<glm::vec3> pointsZ;
	std::vector<glm::vec3> pointsY;
	for (int nPoint = 0; nPoint < pointCount; ++nPoint)
	{
		float x1 = position.x + glm::cos(alpha * nPoint) * distance_min;
		float y1 = position.y + glm::sin(alpha * nPoint) * distance_min;
		float z1 = position.z;

		float x2 = position.x;
		float y2 = position.y + glm::sin(alpha * nPoint) * distance_min;
		float z2 = position.z + glm::cos(alpha * nPoint) * distance_min;

		pointsZ.emplace_back(x1, y1, z1);
		pointsY.emplace_back(x2, y2, z2);

		if (nPoint != 0)
		{
			CGizmosManager::AddLine(pointsZ[nPoint - 1], pointsZ[nPoint], glm::vec3(0.0f, 1.0f, 0.0f));
			CGizmosManager::AddLine(pointsY[nPoint - 1], pointsY[nPoint], glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	// Adding last points
	CGizmosManager::AddLine(pointsZ[0], pointsZ[pointsZ.size() - 1], glm::vec3(0.0f, 1.0f, 0.0f));
	CGizmosManager::AddLine(pointsY[0], pointsY[pointsY.size() - 1], glm::vec3(0.0f, 1.0f, 0.0f));

	// Max circle
	pointsZ.clear();
	pointsY.clear();
	for (int nPoint = 0; nPoint < pointCount; ++nPoint)
	{
		float x1 = position.x + glm::cos(alpha * nPoint) * distance_max;
		float y1 = position.y + glm::sin(alpha * nPoint) * distance_max;
		float z1 = position.z;

		float x2 = position.x;
		float y2 = position.y + glm::sin(alpha * nPoint) * distance_max;
		float z2 = position.z + glm::cos(alpha * nPoint) * distance_max;

		pointsZ.emplace_back(x1, y1, z1);
		pointsY.emplace_back(x2, y2, z2);

		if (nPoint != 0)
		{
			CGizmosManager::AddLine(pointsZ[nPoint - 1], pointsZ[nPoint], glm::vec3(0.4f, 0.4f, 0.4f));
			CGizmosManager::AddLine(pointsY[nPoint - 1], pointsY[nPoint], glm::vec3(0.4f, 0.4f, 0.4f));
		}
	}

	// Adding last points
	CGizmosManager::AddLine(pointsZ[0], pointsZ[pointsZ.size() - 1], glm::vec3(0.4f, 0.4f, 0.4f));
	CGizmosManager::AddLine(pointsY[0], pointsY[pointsY.size() - 1], glm::vec3(0.4f, 0.4f, 0.4f));
#endif
}

}
