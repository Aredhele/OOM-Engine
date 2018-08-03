/// \file       CDebugGrid.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_DEBUG_GRID_HPP__
#define OOM_ENGINE_C_DEBUG_GRID_HPP__

#include <GLM/glm.hpp>
#include "Render/Config.hpp"

namespace Oom
{

class CDebugGrid
{
public:

    void Initialize(int size, float spacing, glm::vec3 const& color);
    void Draw      (glm::mat4 const& PV);

private:

    GLuint      m_vertexCount;
    GLuint      m_vao;
    GLuint      m_vbo;
    GLuint      m_cbo;
    GLint       m_matrixID;
    GLuint      m_shaderID;
};

}

#endif // !OOM_ENGINE_C_DEBUG_GRID_HPP__