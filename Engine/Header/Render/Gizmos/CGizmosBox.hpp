/// \file       CGizmosBox.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_BOX_HPP__
#define OOM_ENGINE_C_GIZMOS_BOX_HPP__

#include <GLM/glm.hpp>

namespace Oom {

void DrawBox(glm::vec3 const& center, float width, float height, glm::vec3 const& color);

}

#endif // !OOM_ENGINE_C_GIZMOS_BOX_HPP__