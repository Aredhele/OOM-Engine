/// \file       CShaderUnlitColor.hpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_SHADER_UNLIT_COLOR_HPP__
#define OOM_ENGINE_C_SHADER_UNLIT_COLOR_HPP__

#include "Render/Shader/IShader.hpp"

namespace Oom
{

class CShaderUnlitColor : public IShader
{
public:

    void Begin(const SRenderData& render_data) final;
    void End  ()                               final;

protected:

    GLuint m_shaderID = 0;
};

}

#endif // !OOM_ENGINE_C_SHADER_UNLIT_COLOR_HPP__