/// \file       SShaderManager.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Render/Shader/SShaderManager.hpp"
#include "Render/Shader/SShaderCompiler.hpp"

namespace Oom
{

/* static */ std::vector<SShaderManager::SPair> SShaderManager::s_shaders;

void SShaderManager::RegisterShader(SShaderManager::EShaderType shader_type,
    const char* p_shader_name,
    const char* p_vertex_shader,
    const char* p_fragment_shader)
{
    GLuint program = SShaderCompiler::CreateProgram(p_shader_name, p_vertex_shader, p_fragment_shader);
    s_shaders.emplace_back(SPair {shader_type, program});
}

GLuint SShaderManager::GetProgram(SShaderManager::EShaderType shader_type)
{
    for(const auto& pair : s_shaders)
    {
        if(pair.shader_type == shader_type)
            return pair.cg_program;
    }

    return 0;
}

}
