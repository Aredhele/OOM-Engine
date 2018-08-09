/// \file       CShaderStandard.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#include <cstdio>
#include "Core/Standard/CString.hpp"
#include "Render/Shader/CShaderStandard.hpp"

namespace Oom
{

CShaderStandard::CShaderStandard()
{
    m_shader_id = SShaderManager::GetProgram(EShaderType::Standard);
}

void CShaderStandard::Begin(const SRenderData& render_data)
{
    BindShader();

    SetMatrix("M",   render_data.M);
    SetMatrix("MVP", render_data.MVP);

    SetVector("lightColor",       render_data.directional.m_light_color);
    SetVector("lightDirection",   render_data.directional.m_direction);
    SetFloat ("lightIntensity",   render_data.directional.m_light_intensity);
    SetFloat ("ambientIntensity", render_data.directional.m_ambient_intensity);

    const auto  true_count  = static_cast<GLint>(render_data.point_lights.size());
	const GLint light_count = (true_count > 4) ? 4 : true_count;

    // Lighting
    SetInt("lightCount", light_count);

    // Setting uniforms
    for(auto nLight = 0; nLight < true_count; ++nLight)
    {
        char buf[8];

        sprintf(buf, "%d", nLight);
        CString index      = buf;
        const CString range      = "lights[" + index + "].range";
        const CString intensity  = "lights[" + index + "].intensity";
        const CString color      = "lights[" + index + "].color";
        const CString position   = "lights[" + index + "].position";

        const int locRange     = glGetUniformLocation(m_shader_id, range.Data());
        const int locIntensity = glGetUniformLocation(m_shader_id, intensity.Data());
        const int locColor     = glGetUniformLocation(m_shader_id, color.Data());
        const int locPosition  = glGetUniformLocation(m_shader_id, position.Data());

        glUniform1f(locRange,     render_data.point_lights[nLight].range);
        glUniform1f(locIntensity, render_data.point_lights[nLight].intensity);
        glUniform3f(locColor,     render_data.point_lights[nLight].color.x,    render_data.point_lights[nLight].color.y,    render_data.point_lights[nLight].color.z);
        glUniform3f(locPosition,  render_data.point_lights[nLight].position.x, render_data.point_lights[nLight].position.y, render_data.point_lights[nLight].position.z);
    }

	 glActiveTexture   (GL_TEXTURE0);
     glBindTexture     (GL_TEXTURE_2D, m_texture_id);
}

void CShaderStandard::End()
{
    UnbindShader();
    glBindVertexArray(0);
}

}