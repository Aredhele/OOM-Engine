/// \file       CShaderUnlitTexture.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/CShaderUnlitTexture.hpp"

namespace Oom
{

CShaderUnlitTexture::CShaderUnlitTexture()
{
    m_shader_id = SShaderManager::GetProgram(EShaderType::UnlitTexture);
}

void CShaderUnlitTexture::Begin(const SRenderData& render_data)
{
    BindShader();
    SetMatrix("MVP", render_data.MVP);

    glActiveTexture   (GL_TEXTURE0);
    glBindTexture     (GL_TEXTURE_2D, m_texture_id);
}

void CShaderUnlitTexture::End()
{
    UnbindShader();
    glBindVertexArray(0);
}

}