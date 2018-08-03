/// \file       CGizmosPointLight.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_POINT_LIGHT_HPP__
#define OOM_ENGINE_C_GIZMOS_POINT_LIGHT_HPP__

#include <GLM/glm.hpp>

namespace Oom {

void DrawPointLight(glm::vec3 const& position, glm::vec3 const& color, int resolution, float range, float scale);

}

#endif // !OOM_ENGINE_C_GIZMOS_POINT_LIGHT_HPP__