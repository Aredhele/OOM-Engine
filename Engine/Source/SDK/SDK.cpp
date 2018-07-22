/// \file       SDK.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    SDK
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
#include "CEngine.hpp"

void Sdk::SetMousePosition(const glm::vec2& position)
{
    Oom::CEngine::SetMousePosition(position);
}

glm::tvec3<double> Sdk::GetMousePosition()
{
    return Oom::CEngine::GetMousePosition();
}

glm::vec2 Sdk::GetWindowSize()
{
    return Oom::CEngine::GetWindowSize();
}

bool Sdk::IsKeyPressed(int key_code)
{
    return Oom::CEngine::IsKeyPressed(key_code);
}

bool Sdk::IsKeyReleased(int key_code)
{
    return Oom::CEngine::IsKeyReleased(key_code);
}