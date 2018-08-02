/// \file       CShaderUnlitLine.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/CShaderUnlitLine.hpp"

namespace Oom
{

CShaderUnlitLine::CShaderUnlitLine()
{
    m_shader_id = SShaderManager::GetProgram(EShaderType::UnlitLine);
}

void CShaderUnlitLine::Begin(const SRenderData& render_data)
{
    // TODO
}

void CShaderUnlitLine::End()
{
    // TODO
}

}