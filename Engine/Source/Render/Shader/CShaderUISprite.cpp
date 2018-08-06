/// \file       CShaderUISprite.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/CShaderUISprite.hpp"

namespace Oom
{

CShaderUISprite::CShaderUISprite()
{
	m_shader_id = SShaderManager::GetProgram(EShaderType::UISprite);
}

void CShaderUISprite::Begin(const SRenderData& render_data)
{
	// TODO
	BindShader();
	SetColor("textColor", m_shader_color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void CShaderUISprite::End()
{
	UnbindShader();
	glBindVertexArray(0);
}

}