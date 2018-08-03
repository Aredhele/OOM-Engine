/// \file       CGizmosCone.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_CONE_HPP__
#define OOM_ENGINE_C_GIZMOS_CONE_HPP__

#include <GLM/glm.hpp>

namespace Oom {

void DrawCone(glm::vec3 const& position, float radius, float topRadius, float lenght, glm::vec3 const& color);

}

#endif // !OOM_ENGINE_C_GIZMOS_CONE_HPP__