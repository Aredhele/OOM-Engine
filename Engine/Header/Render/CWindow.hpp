/// \file       CWindow.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_WINDOW_HPP__
#define OOM_ENGINE_C_WINDOW_HPP__

#include <GLM/glm.hpp>
#include "Render/Config.hpp"

namespace Oom
{

// Vulkan style initialization
struct SWindowCreateInfo
{
	int         window_width;
	int         window_height;
	int			opengl_major;
	int			opengl_minor;
	bool        full_screen;
	const char* window_name;
};

class CWindow
{
public:

    bool        Initialize   (const SWindowCreateInfo& window_create_info);
    void        Release      ();
    GLFWwindow* GetHandle    ();
    glm::vec2   GetWindowSize();

    void        Clear       (const glm::vec3& clear_color);
    void        Display     ();

private:

    GLFWwindow* mp_window = nullptr;
};

}

#endif // !OOM_ENGINE_C_WINDOW_HPP__