/// \file       SShaderManager.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_SHADER_MANAGER_HPP__
#define OOM_ENGINE_S_SHADER_MANAGER_HPP__

#include <vector>
#include "Render/Config.hpp"

namespace Oom
{

class SShaderManager
{
public:

    enum EShaderType
    {
        Text,
        Standard,
        UnlitLine,
        UnlitColor,
        UnlitTexture,
        UnlitTransparent,

        // Post processing
        FXAA,
        Vignette,
        FogEffect,
        IdentityEffect
    };

    struct SPair
    {
        EShaderType shader_type;
        GLuint      cg_program;
    };

    static void RegisterShader(EShaderType shader_type,
                               const char* p_shader_name,
                               const char* p_vertex_shader,
                               const char* p_fragment_shader);

    static GLuint GetProgram(EShaderType shaderType);

private:

    static std::vector<SPair> s_shaders;
};

}

#endif // !OOM_ENGINE_S_SHADER_MANAGER_HPP__