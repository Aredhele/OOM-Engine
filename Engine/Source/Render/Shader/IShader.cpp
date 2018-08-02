/// \file       IShader.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/IShader.hpp"

namespace Oom
{

void IShader::BindShader()
{
    glUseProgram(m_shader_id);
}

void IShader::UnbindShader()
{
    glUseProgram(0);
}

GLuint IShader::GetShader() const
{
    return m_shader_id;
}

GLuint IShader::GetTexture() const
{
    return m_texture_id;
}

const glm::vec3& IShader::GetColor() const
{
    return m_shader_color;
}

void IShader::SetColor(const glm::vec3& color)
{
    m_shader_color = color;
}

void IShader::SetInt(const char* p_name, int data)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniform1i(m_location, data);
}

void IShader::SetFloat(const char* p_name, float data)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniform1f(m_location, data);
}

void IShader::SetColor(const char* p_name, const glm::vec3& color)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniform3f(m_location, color[0], color[1], color[2]);
}

void IShader::SetColor(const char* p_name, const glm::vec4& color)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniform4f(m_location, color[0], color[1], color[2], color[3]);
}

void IShader::SetVector(const char* p_name, const glm::vec2& vector)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniform2f(m_location, vector[0], vector[1]);
}

void IShader::SetVector(const char* p_name, const glm::vec3& vector)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniform3f(m_location, vector[0], vector[1], vector[2]);
}

void IShader::SetVector(const char* p_name, const glm::vec4& vector)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniform4f(m_location, vector[0], vector[1], vector[2], vector[3]);
}

void IShader::SetMatrix(const char* p_name, const glm::mat4 &matrix4)
{
    GLint m_location = glGetUniformLocation(m_shader_id, p_name);
    glUniformMatrix4fv(m_location, 1, GL_FALSE, &matrix4[0][0]);
}

void IShader::SetTexture(GLuint texture)
{
    m_texture_id = texture;
}

}
