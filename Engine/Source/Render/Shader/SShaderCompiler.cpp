/// \file       SShaderCompiler.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include <malloc.h>

#include "Core/Debug/SLogger.hpp"
#include "Render/Shader/SShaderCompiler.hpp"

namespace Oom
{

GLuint SShaderCompiler::CreateProgram(const char* p_shader_name,
                                      const char* p_vertex_shader,
                                      const char* p_fragment_shader)
{
    // Compiling shader
    GLuint vertex_shader_id   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    if(!CompileShader(p_shader_name, "vertex  ",   p_vertex_shader,   vertex_shader_id) ||
       !CompileShader(p_shader_name, "fragment", p_fragment_shader, fragment_shader_id))
    {
        SLogger::LogWaring("Shader errors occurred, some materials could be disabled.");
    }

    // Linking shader to cg program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram (program_id);

    GLint link_result     = GL_FALSE;
    int   info_log_lenght = 0;

    // Check the program
    GLsizei size = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS,     &link_result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_lenght);

    if (info_log_lenght > 0)
    {
        auto* p_buffer = (char*)malloc(static_cast<size_t>(info_log_lenght + 1));

        SLogger::LogError("glLinkProgram failed (%s) : %", p_shader_name, p_buffer);
        free(p_buffer);
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

bool SShaderCompiler::CompileShader(const char* p_shader_name, const char* p_shader_type,
                                    const char* p_shader, GLuint shader_id)
{
    GLint compile_result  = GL_FALSE;
    int   info_log_lenght = 0;

    SLogger::LogInfo("Compiling %s shader %s ...", p_shader_type, p_shader_name);
    glShaderSource (shader_id, 1, &p_shader, nullptr);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS,  &compile_result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_lenght);

    if (info_log_lenght > 0)
    {
        auto* p_buffer = (char*)malloc(static_cast<size_t>(info_log_lenght + 1));
        glGetShaderInfoLog(shader_id, info_log_lenght, nullptr, p_buffer);

        SLogger::LogError("Shader error (%s) : %", p_shader_name, p_buffer);
        free(p_buffer);

        return false;
    }

    return true;
}

}