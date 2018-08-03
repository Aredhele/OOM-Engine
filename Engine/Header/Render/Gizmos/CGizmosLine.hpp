/// \file       CGizmosLine.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_LINE_HPP__
#define OOM_ENGINE_C_GIZMOS_LINE_HPP__

#include <GLM/glm.hpp>

namespace Oom {

void DrawLine(glm::vec3 const& start, glm::vec3 const& end, glm::vec3 const& color);

}

#endif // !OOM_ENGINE_C_GIZMOS_LINE_HPP__