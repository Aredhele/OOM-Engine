/// \file       IShader.hpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_SHADER_HPP__
#define OOM_ENGINE_I_SHADER_HPP__

#include "Render/Config.hpp"
#include "Render/Shader/SRenderData.hpp"
#include "Render/Shader/SShaderManager.hpp"

using EShaderType = Oom::SShaderManager::EShaderType;

namespace Oom
{

class IShader
{
public:

    virtual void Begin(const SRenderData& render_data) = 0;
    virtual void End  () = 0;

public:

    void                BindShader      ();
    void                UnbindShader    ();

    GLuint              GetShader       () const;
    GLuint              GetTexture      () const;
    const glm::vec3&    GetColor        () const;

	void SetUVOffset	(const glm::vec2& offset);
    void SetColor       (const glm::vec3& color);
    void SetInt         (const char* p_name, int data);
    void SetFloat       (const char* p_name, float data);
    void SetColor       (const char* p_name, const glm::vec3& color);
    void SetColor       (const char* p_name, const glm::vec4& color);
    void SetVector      (const char* p_name, const glm::vec2& vector);
    void SetVector      (const char* p_name, const glm::vec3& vector);
    void SetVector      (const char* p_name, const glm::vec4& vector);
    void SetMatrix      (const char* p_name, const glm::mat4& matrix4);
    void SetTexture     (GLuint texture);

protected:

    GLuint      m_shader_id  = 0;
    GLuint      m_texture_id = 0;

	glm::vec2   m_uv_offset;
    glm::vec3   m_shader_color;
};

}

#endif // !OOM_ENGINE_I_SHADER_HPP__