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

class CWindow
{
public:

    bool        Initialize   (int width, int height, const char* p_name);
    void        Release      ();
    GLFWwindow* GetHandle    ();
    glm::vec2   GetWindowSize();

private:

    GLFWwindow* mp_window = nullptr;
};

}

#endif // !OOM_ENGINE_C_WINDOW_HPP__