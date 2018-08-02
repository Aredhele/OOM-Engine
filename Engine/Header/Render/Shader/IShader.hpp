/// \file       IShader.hpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_SHADER_HPP__
#define OOM_ENGINE_I_SHADER_HPP__

#include "Render/Config.hpp"
#include "Render/Shader/SRenderData.hpp"

namespace Oom
{

class IShader
{
public:

    virtual void Begin(const SRenderData& render_data) = 0;
    virtual void End  () = 0;

protected:

    GLuint m_shaderID = 0;
};

}

#endif // !OOM_ENGINE_I_SHADER_HPP__