/// \file       SDK.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    SDK
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_SDK_HPP__
#define OOM_ENGINE_SDK_HPP__

// Always include the config first
// To avoid including GL before GLEW
#include <Render/Config.hpp>

// Third party
#include <GLM/glm.hpp>

// Standard types
#include <Core/Standard/CString.hpp>

// Components
#include "Composite/Component/CBehavior.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Sdk
{

void               SetMousePosition     (const glm::vec2& position);
glm::tvec3<double> GetMousePosition     ();
glm::vec2          GetWindowSize        ();
bool               IsKeyPressed         (int key_code);
bool               IsKeyReleased        (int key_code);

}

#endif // !OOM_ENGINE_SDK_HPP__