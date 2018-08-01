/// \file       CWindow.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Render/CWindow.hpp"
#include "Core/Debug/SLogger.hpp"

namespace Oom
{

bool CWindow::Initialize(int width, int height, const char* p_name)
{
    SLogger::LogInfo("Window initialization.");

    if(!glfwInit())
    {
        SLogger::LogError("Failed to initialize GLFW.");
        return false;
    }

    SLogger::LogInfo("GLFW successfully initialized.");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //< TODO : Add option
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //< TODO : Add option
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mp_window = glfwCreateWindow(width, height, p_name, nullptr, nullptr);
    if(mp_window == nullptr)
    {
        SLogger::LogError(
                "Unable to create the OpenGL context."
                "Your openGL version must be at least 3.3.");

        Release();
        return false;
    }

    glfwMakeContextCurrent(mp_window);
    glewExperimental = 1;
    if (glewInit()  != GLEW_OK)
    {
        SLogger::LogError("Failed to initialized Glew");
        Release();
        return false;
    }

    SLogger::LogInfo("Window initialized.");
    SLogger::LogInfo("OpenGL Version %s", glGetString(GL_VERSION));

    return true;
}

void CWindow::Release()
{
    SLogger::LogInfo("Releasing window.");

    glfwTerminate();
    mp_window = nullptr;

    SLogger::LogInfo("Window released.");
}

GLFWwindow* CWindow::GetHandle()
{ return mp_window; }

glm::vec2 CWindow::GetWindowSize()
{
    int x = 0, y = 0;
    glfwGetWindowSize(mp_window, &x, &y);

    return glm::vec2(x, y);
}

void CWindow::Clear(const glm::vec3& clear_color)
{
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CWindow::Display()
{
    glfwSwapBuffers(mp_window);
}

}