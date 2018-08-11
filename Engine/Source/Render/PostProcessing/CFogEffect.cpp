/// \file       CFogEffect.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/SShaderManager.hpp"
#include "Render/PostProcessing/CFogEffect.hpp"

namespace Oom
{

CFogEffect::CFogEffect() : IPostEffect(IPostEffect::EType::Fog, "Fog")
{
    m_shader_id = SShaderManager::GetProgram(SShaderManager::EShaderType::FogEffect);

    // Getting uniforms
    m_color_texture_id = glGetUniformLocation(m_shader_id, "colorTexture");
    m_depth_texture_id = glGetUniformLocation(m_shader_id, "depthTexture");

    m_fogColorID   = glGetUniformLocation(m_shader_id, "fogColor");
    m_fogDensityID = glGetUniformLocation(m_shader_id, "fogDensity");

    m_fogDensity = 30.0f;
    m_fogColor   = glm::vec3(0.1f, 0.05f, 0.05f);

    glUseProgram(m_shader_id);
    glUniform3f (m_fogColorID,   m_fogColor.x, m_fogColor.y, m_fogColor.z);
    glUniform1f (m_fogDensityID, m_fogDensity);
    glUseProgram(0);
}

CFogEffect::~CFogEffect() // NOLINT
{
    // None
}

void CFogEffect::ApplyEffect(GLuint color_texture, GLuint depth_texture)
{
    glUseProgram   (m_shader_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, color_texture);
    glUniform1i    (m_color_texture_id, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture  (GL_TEXTURE_2D, depth_texture);
    glUniform1i    (m_depth_texture_id, 1);
}

const glm::vec3& CFogEffect::GetFogColor() const
{
    return m_fogColor;
}

float CFogEffect::GetFogDensity() const
{
    return m_fogDensity;
}

void CFogEffect::SetFogColor(const glm::vec3 &color)
{
    m_fogColor = color;

    glUseProgram(m_shader_id);
    glUniform3f (m_fogColorID,   m_fogColor.x, m_fogColor.y, m_fogColor.z);
    glUseProgram(0);
}

void CFogEffect::SetFogDensity(float density)
{
    m_fogDensity = density;

    glUseProgram(m_shader_id);
    glUniform1f (m_fogDensityID, m_fogDensity);
    glUseProgram(0);
}

} // !namespace