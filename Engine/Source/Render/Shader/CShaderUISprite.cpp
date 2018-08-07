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
	SetMatrix("proj",  render_data.P);
	SetMatrix("model", render_data.M);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void CShaderUISprite::End()
{
	UnbindShader();
	glBindVertexArray(0);
}

}