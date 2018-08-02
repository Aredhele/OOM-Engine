/// \file       CShaderUnlitLine.hpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_SHADER_UNLIT_LINE_HPP__
#define OOM_ENGINE_C_SHADER_UNLIT_LINE_HPP__

#include "Render/Shader/IShader.hpp"

namespace Oom
{

class CShaderUnlitLine : public IShader
{
public:

    CShaderUnlitLine();

    void Begin(const SRenderData& render_data) final;
    void End  ()                               final;

};

}

#endif // !OOM_ENGINE_C_SHADER_UNLIT_LINE_HPP__