/// \file       CWindow.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Render/CWindow.hpp"
#include "Core/Debug/SLogger.hpp"
#include <cstdio>
#include <xutility>

namespace Oom
{

/// \brief  Initializes the opengl context and the window
/// \param  window_create_info The parameters structure
/// \return True on success, else false
bool CWindow::Initialize(const SWindowCreateInfo& window_create_info)
{
    SLogger::LogInfo("Window initialization.");

    if(!glfwInit())
    {
        SLogger::LogError("Failed to initialize GLFW.");
        return false;
    }

    SLogger::LogInfo("GLFW successfully initialized.");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window_create_info.opengl_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window_create_info.opengl_minor);

	// Hard constraint. We don't of all OpenGL deprecated stuff.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(window_create_info.full_screen)
	{
		GLFWmonitor*       p_primary_monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* p_video_mode      = glfwGetVideoMode(p_primary_monitor);
		
		// Full screen creation from the primary monitor
		mp_window = glfwCreateWindow(
			p_video_mode->width, p_video_mode->height,
			window_create_info.window_name, glfwGetPrimaryMonitor(), nullptr);
	}
	else
	{
		// Regular creation
		mp_window = glfwCreateWindow(
			window_create_info.window_width, 
			window_create_info.window_height,
			window_create_info.window_name, nullptr, nullptr);
	}

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

/// \brief Releases all objects and the opengl context
void CWindow::Release()
{
    SLogger::LogInfo("Releasing window.");

    glfwTerminate();
    mp_window = nullptr;

    SLogger::LogInfo("Window released.");
}

/// \brief  Returns the glfw window
/// \return A pointer on the glfw window
GLFWwindow* CWindow::GetHandle()
{
	return mp_window;
}

/// \brief  Returns the window size
/// \return The window size
glm::vec2 CWindow::GetWindowSize()
{
    int x = 0, y = 0;
    glfwGetWindowSize(mp_window, &x, &y);

    return glm::vec2(x, y);
}

/// \brief Clears the window with a color
/// \param clear_color The clear color
void CWindow::Clear(const glm::vec3& clear_color)
{
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/// \brief Swaps window buffer (basic double buffering)
void CWindow::Display()
{
    glfwSwapBuffers(mp_window);
}

}
