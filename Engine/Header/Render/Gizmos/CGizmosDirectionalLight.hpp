/// \file       CGizmosDirectionalLight.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_DIRECTIONAL_LIGHT_HPP__
#define OOM_ENGINE_C_GIZMOS_DIRECTIONAL_LIGHT_HPP__

#include <GLM/glm.hpp>

namespace Oom {

void DrawDirectionalLight(glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& color, float scale);

}

#endif // !OOM_ENGINE_C_GIZMOS_DIRECTIONAL_LIGHT_HPP__