/// \file       CShaderText.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/CShaderText.hpp"

namespace Oom
{

CShaderText::CShaderText()
{
    m_shader_id = SShaderManager::GetProgram(EShaderType::Text);
}

void CShaderText::Begin(const SRenderData& render_data)
{
    BindShader();
	SetMatrix("proj",     render_data.P);
	SetMatrix("model",    render_data.M);
	SetColor("textColor", m_shader_color);

    glActiveTexture   (GL_TEXTURE0);
    glBindTexture     (GL_TEXTURE_2D, m_texture_id);
}

void CShaderText::End()
{
    UnbindShader();
    glBindVertexArray(0);
}

}