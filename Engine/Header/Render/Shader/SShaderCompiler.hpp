/// \file       SShaderCompiler.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_SHADER_COMPILER_HPP__
#define OOM_ENGINE_S_SHADER_COMPILER_HPP__

#include "Render/Config.hpp"

namespace Oom
{

class SShaderCompiler
{
public:

    static GLuint CreateProgram(const char* p_shader_name, const char* p_vertex_shader, const char* p_fragment_shader);
    static bool   CompileShader(const char* p_shader_name, const char* p_shader_type, const char* p_shader, GLuint shader_id);
};

}

#endif // !OOM_ENGINE_S_SHADER_COMPILER_HPP__