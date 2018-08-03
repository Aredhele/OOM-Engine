/// \file       CFXAAEffect.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/SShaderManager.hpp"
#include "Render/PostProcessing/CFXAAEffect.hpp"

namespace Oom
{

CFXAAEffect::CFXAAEffect() : IPostEffect(IPostEffect::EType::FXAA, "FXAA")
{
    m_shader_id = SShaderManager::GetProgram(SShaderManager::EShaderType::FXAA);

    // Getting uniforms
    m_color_texture_id    = glGetUniformLocation(m_shader_id, "colorTexture");
    m_fxaa_span_id        = glGetUniformLocation(m_shader_id, "FXAASpan");
    m_fxaa_reduce_mul_id  = glGetUniformLocation(m_shader_id, "FXAAReduceMul");
    m_fxaa_reduce_min_id  = glGetUniformLocation(m_shader_id, "FXAAReduceMin");

    m_fxaa_span       = 8.0f;
    m_fxaa_reduce_mul = 1.0f / 8.0f;
    m_fxaa_reduce_min = 1.0f / 128.0f;

    glUseProgram(m_shader_id);
    glUniform1f (m_fxaa_span_id,       m_fxaa_span);
    glUniform1f (m_fxaa_reduce_mul_id, m_fxaa_reduce_mul);
    glUniform1f (m_fxaa_reduce_min_id, m_fxaa_reduce_min);
    glUseProgram(0);
}

CFXAAEffect::~CFXAAEffect() // NOLINT
{
    // None
}

void CFXAAEffect::ApplyEffect(GLuint color_texture, GLuint depth_texture)
{
    glUseProgram   (m_shader_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, color_texture);
    glUniform1i    (m_color_texture_id, 0);
}

}