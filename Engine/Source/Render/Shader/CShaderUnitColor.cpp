/// \file       CShaderUnlitColor.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/CShaderUnlitColor.hpp"

namespace Oom
{

CShaderUnlitColor::CShaderUnlitColor()
{
    m_shader_id = SShaderManager::GetProgram(EShaderType::UnlitColor);
}


void CShaderUnlitColor::Begin(const SRenderData& render_data)
{
    // TODO
}

void CShaderUnlitColor::End()
{
    // TODO
}

}