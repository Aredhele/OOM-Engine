/// \file       CMaterial.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Material
/// \author     Vincent STEHLY--CALISTO

#include "Render/Material/CMaterial.hpp"

namespace Oom
{

void CMaterial::SetShader(EShaderType shader_type)
{
    m_shader_type = shader_type;
    m_program     = SShaderManager::GetProgram(shader_type);
}

GLuint CMaterial::GetShader() const
{
    return m_program;
}

EShaderType CMaterial::GetShaderType() const
{
    return m_shader_type;
}

const glm::vec3& CMaterial::GetColor() const
{
    return m_color;
}

bool CMaterial::HasProperty(const char* p_name) const
{
    return (glGetUniformLocation(m_program, p_name) != -1);
}

void CMaterial::SetInt(const char* p_name, int data)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniform1i(m_location, data);
    glUseProgram(0);
}

void CMaterial::SetFloat(const char* p_name, float data)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniform1f(m_location, data);
    glUseProgram(0);
}

void CMaterial::SetColor(const char* p_name, const glm::vec3& color)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniform3f(m_location, color[0], color[1], color[2]);
    glUseProgram(0);
}

void CMaterial::SetColor(const char* p_name, const glm::vec4& color)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniform4f(m_location, color[0], color[1], color[2], color[3]);
    glUseProgram(0);
}

void CMaterial::SetVector(const char* p_name, const glm::vec2& vector)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniform2f(m_location, vector[0], vector[1]);
    glUseProgram(0);
}

void CMaterial::SetVector(const char* p_name, const glm::vec3& vector)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniform3f(m_location, vector[0], vector[1], vector[2]);
    glUseProgram(0);
}

void CMaterial::SetVector(const char* p_name, const glm::vec4& vector)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniform4f(m_location, vector[0], vector[1], vector[2], vector[3]);
    glUseProgram(0);
}

void CMaterial::SetMatrix(const char* p_name, const glm::mat4 &matrix4)
{
    GLint m_location = glGetUniformLocation(m_program, p_name);

    glUseProgram(m_program);
        glUniformMatrix4fv(m_location, 1, GL_FALSE, &matrix4[0][0]);
    glUseProgram(0);
}

/* virtual */ void CMaterial::_Register()
{
    // None
}

/* virtual */ void CMaterial::_Destroy()
{
    // None
}

}