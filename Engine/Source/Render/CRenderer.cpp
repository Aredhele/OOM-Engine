/// \file       CRenderer.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Render/CRenderer.hpp"
#include "Core/Debug/SLogger.hpp"

namespace Oom
{

/* static */ CRenderer* CRenderer::sp_instance = nullptr;

bool CRenderer::Initialize()
{
    SLogger::LogInfo("Renderer initialization.");

    sp_instance = this;
    mp_window   = new CWindow();
    mp_window->Initialize(1600, 900, "Oom-Engine"); //< TODO : Add option

    SLogger::LogInfo("Renderer initialization.");
    return true;
}

void CRenderer::Release()
{
    SLogger::LogInfo("Releasing renderer.");

    mp_window->Release();
    delete mp_window;

    mp_window   = nullptr;
    sp_instance = nullptr;

    SLogger::LogInfo("Renderer released.");
}

void CRenderer::Render()
{
    // TODO
}

}

