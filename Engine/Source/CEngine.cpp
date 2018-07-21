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
    // Getting GLFW window
    GLFWwindow* p_handle = mp_renderer->GetWindow()->GetHandle();

    double lag        = 0.0;
    double previous   = glfwGetTime();
    double delta_time = 1.0 / 60.0;

    while (glfwWindowShouldClose(p_handle) == 0 &&
           glfwGetKey(p_handle, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous       = current;

        lag += elapsed;

        // Processing events
        glfwPollEvents();

        // Fixed granularity
        while(lag >= delta_time)
        {
            // TODO

            lag -= delta_time;
        }

        mp_renderer->Render();
    }
}

}