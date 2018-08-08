/// \file       CGizmosCollider.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_COLLIDER_HPP__
#define OOM_ENGINE_C_GIZMOS_COLLIDER_HPP__

#include <GLM/glm.hpp>

namespace Oom {

	void DrawCollider(const glm::vec3& position, const glm::vec3& extent, const glm::vec3& euler,    const glm::vec3& color);
	void DrawCollider(const glm::vec3& position, const glm::vec3& extent, const glm::mat4& rotation, const glm::vec3& color);

}

#endif // !OOM_ENGINE_C_GIZMOS_COLLIDER_HPP__