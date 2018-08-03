/// \file       CIdentityEffect.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/SShaderManager.hpp"
#include "Render/PostProcessing/CIdentityEffect.hpp"

namespace Oom
{

CIdentityEffect::CIdentityEffect() : IPostEffect(IPostEffect::EType::Identity, "Identity")
{
    m_shader_id = SShaderManager::GetProgram(SShaderManager::EShaderType::IdentityEffect);

    // Getting uniforms
    m_color_texture_id = glGetUniformLocation(m_shader_id, "colorTexture");
}

CIdentityEffect::~CIdentityEffect() // NOLINT
{
    // None
}

void CIdentityEffect::ApplyEffect(GLuint color_texture, GLuint depth_texture)
{
    glUseProgram   (m_shader_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, color_texture);
    glUniform1i    (m_color_texture_id, 0);
}

} // !namespace