/// \file       SShaderManager.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include <cstdio>
#include <cstdlib>

#include "Core/Debug/SLogger.hpp"
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
    FILE* vertex_shader_file   = nullptr;
    FILE* fragment_shader_file = nullptr;

    if(!(vertex_shader_file = fopen(p_vertex_shader,   "r"))) {
        SLogger::LogError("Unable to open the vertex shader %s", p_shader_name);
        return;
    }

    if(!(fragment_shader_file = fopen(p_fragment_shader, "r"))) {
        fclose(vertex_shader_file);
        SLogger::LogError("Unable to open the fragment shader %s", p_shader_name);
        return;
    }

    fseek(vertex_shader_file,   0, SEEK_END);
    fseek(fragment_shader_file, 0, SEEK_END);

    auto size_vertex   = static_cast<size_t>(ftell(vertex_shader_file));
    auto size_fragment = static_cast<size_t>(ftell(fragment_shader_file));

    fseek(vertex_shader_file, 0,   SEEK_SET);
    fseek(fragment_shader_file, 0, SEEK_SET);

    auto vertex_buffer   = (char*)calloc(1, size_vertex   + 1);
    auto fragment_buffer = (char*)calloc(1, size_fragment + 1);

    fread(vertex_buffer, size_vertex,     1, vertex_shader_file);
    fread(fragment_buffer, size_fragment, 1, fragment_shader_file);

    GLuint program = SShaderCompiler::CreateProgram(p_shader_name, vertex_buffer, fragment_buffer);
    s_shaders.emplace_back(SPair {shader_type, program});

    free(vertex_buffer);
    free(fragment_buffer);

    fclose(vertex_shader_file);
    fclose(fragment_shader_file);
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
