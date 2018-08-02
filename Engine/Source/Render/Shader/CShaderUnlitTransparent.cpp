/// \file       CShaderUnlitTransparent.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/SShaderManager.hpp"
#include "Render/Shader/CShaderUnlitTransparent.hpp"

namespace Oom
{

CShaderUnlitTransparent::CShaderUnlitTransparent()
{
    m_shader_id = SShaderManager::GetProgram(EShaderType::UnlitTransparent);
}

void CShaderUnlitTransparent::Begin(const SRenderData& render_data)
{
    // TODO
}

void CShaderUnlitTransparent::End()
{
    // TODO
}

}

