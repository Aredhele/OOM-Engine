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
	int         window_width;  ///< The window width
	int         window_height; ///< The window height
	int			opengl_major;  ///< The openg major version
	int			opengl_minor;  ///< The openg minor version
	bool        full_screen;   ///< Is the window full sceen ?
	const char* window_name;   ///< The window name
};

/// \class CWindow
/// \brief Manages the GLFW windows
class CWindow
{
public:

	/// \brief  Initializes the opengl context and the window
	/// \param  window_create_info The parameters structure
	/// \return True on success, else false
    bool Initialize (const SWindowCreateInfo& window_create_info);

	/// \brief Releases all objects and the opengl context
    void Release();

	/// \brief  Returns the glfw window
	/// \return A pointer on the glfw window
    GLFWwindow* GetHandle();

	/// \brief  Returns the window size
	/// \return The window size
    glm::vec2 GetWindowSize();

	/// \brief Clears the window with a color
	/// \param clear_color The clear color
    void Clear (const glm::vec3& clear_color);

	/// \brief Swaps window buffer (basic double buffering)
    void Display ();

private:

    GLFWwindow* mp_window = nullptr;
};

}

#endif // !OOM_ENGINE_C_WINDOW_HPP__