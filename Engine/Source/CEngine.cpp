/// \file       CEngine.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "CEngine.hpp"
#include "Core/Debug/SLogger.hpp"

namespace Oom
{

bool CEngine::Initialize()
{
    SLogger::LogInfo("Oom-Engine initialization.");

    mp_renderer = new CRenderer();
    mp_renderer->Initialize();

    SLogger::LogInfo("Oom-Engine initialized.");
    return true;
}

void CEngine::Release()
{
    SLogger::LogInfo("Releasing Oom-Engine");

    mp_renderer->Release();
    delete mp_renderer;
    mp_renderer = nullptr;

    SLogger::LogInfo("Oom-Engine released.");
}

void CEngine::Run()
{
    // TODO
}

}