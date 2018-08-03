/// \file       CVignetteEffect.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/SShaderManager.hpp"
#include "Render/PostProcessing/CVignetteEffect.hpp"

namespace Oom
{

CVignetteEffect::CVignetteEffect() : IPostEffect(IPostEffect::EType::Vignette, "Vignette")
{
    // Getting shader ...
    m_shader_id = SShaderManager::GetProgram(SShaderManager::EShaderType::Vignette);

    // Getting uniforms
    m_color_texture_id = glGetUniformLocation(m_shader_id, "colorTexture");
    m_radius_id        = glGetUniformLocation(m_shader_id, "radius");
    m_softness_id      = glGetUniformLocation(m_shader_id, "softness");
    m_center_id        = glGetUniformLocation(m_shader_id, "center");
    m_opacity_id       = glGetUniformLocation(m_shader_id, "opacity");

    m_radius   = 0.60f;
    m_softness = 0.45f;
    m_center   = glm::vec2(0.5f, 0.5f);
    m_opacity  = 0.8f;

    glUseProgram(m_shader_id);
    glUniform1f (m_radius_id,   m_radius);
    glUniform1f (m_softness_id, m_softness);
    glUniform1f (m_opacity_id,  m_opacity);
    glUniform2f (m_center_id  , m_center.x, m_center.y);
    glUseProgram(0);
}

CVignetteEffect::~CVignetteEffect() // NOLINT
{
    // None
}

void CVignetteEffect::ApplyEffect(GLuint color_texture, GLuint depth_texture)
{
    glUseProgram   (m_shader_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, color_texture);
    glUniform1i    (m_color_texture_id, 0);
}

void CVignetteEffect::SetRadius(float radius)
{
    m_radius = radius;

    glUseProgram(m_shader_id);
    glUniform1f (m_radius_id,   m_radius);
    glUseProgram(0);
}

void CVignetteEffect::SetOpacity(float opacity)
{
    m_opacity = opacity;

    glUseProgram(m_shader_id);
    glUniform1f (m_opacity_id,   m_opacity);
    glUseProgram(0);
}

void CVignetteEffect::SetSoftness(float softness)
{
    m_softness = softness;
    glUseProgram(m_shader_id);
    glUniform1f (m_softness_id,   m_softness);
    glUseProgram(0);

}

void CVignetteEffect::SetCenter(const glm::vec2 &center)
{
    m_center = center;
    glUseProgram(m_shader_id);
    glUniform2f (m_center_id, m_center.x, m_center.y);
    glUseProgram(0);
}

float CVignetteEffect::GetRadius() const
{
    return m_radius;
}

float CVignetteEffect::GetOpacity() const
{
    return m_opacity;
}

float CVignetteEffect::GetSoftness() const
{
    return m_softness;
}

const glm::vec2& CVignetteEffect::GetCenter() const
{
    return m_center;
}

}