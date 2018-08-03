/// \file       CDebugGrid.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include <vector>
#include "Render/Gizmos/CDebugGrid.hpp"
#include "Render/Shader/SShaderManager.hpp"

namespace Oom
{

void CDebugGrid::Initialize(int size, float spacing, glm::vec3 const& color)
{
    m_vao         = 0;
    m_vbo         = 0;
    m_cbo         = 0;
    m_matrixID    = 0;
    m_shaderID    = 0;
    m_vertexCount = 0;

    // Getting color shader
    m_shaderID = SShaderManager::GetProgram(SShaderManager::EShaderType::UnlitColor);
    m_matrixID = glGetUniformLocation(m_shaderID, "MVP");

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    for(int i = 0; i < size; ++i)
    {
        float d = i * spacing - size * spacing / 2.0f;
        vertices.emplace_back(i * spacing - size * spacing / 2.0f, -size * spacing / 2.0f, 0.0f);
        vertices.emplace_back(i * spacing - size * spacing / 2.0f, +size * spacing / 2.0f, 0.0f);
        vertices.emplace_back(-size * spacing / 2.0f, i * spacing - size * spacing / 2.0f, 0.0f);
        vertices.emplace_back(+size * spacing / 2.0f, i * spacing - size * spacing / 2.0f, 0.0f);

        colors.push_back(color);
        colors.push_back(color);
        colors.push_back(color);
        colors.push_back(color);
    }

    m_vertexCount = static_cast<GLuint>(vertices.size());

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers          (1, &m_vbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_vbo);
    glBufferData          (GL_ARRAY_BUFFER, m_vertexCount * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glGenBuffers          (1, &m_cbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_cbo);
    glBufferData          (GL_ARRAY_BUFFER, m_vertexCount * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void CDebugGrid::Draw(glm::mat4 const& PV)
{
    // Computes MVP matrix
    glm::mat4 MVP = PV * glm::mat4(1.0f);

    // glEnable (GL_MULTISAMPLE);
    // glDisable(GL_BLEND);

    // Sets up shader
    glUseProgram      (m_shaderID);
    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);

    // Draws all lines
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, m_vertexCount);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    // glDisable(GL_MULTISAMPLE);
}


} // !namespace