/// \file       CGizmosTransform.hpp
/// \date       07/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_TRANSFORM_HPP__
#define OOM_ENGINE_C_GIZMOS_TRANSFORM_HPP__

#include <GLM/glm.hpp>

namespace Oom {

	void DrawTransform(const glm::vec3& position, const glm::vec3& up, const glm::vec3& right, const glm::vec3& forward, const glm::vec3& target);

}

#endif // !OOM_ENGINE_C_GIZMOS_TRANSFORM_HPP__