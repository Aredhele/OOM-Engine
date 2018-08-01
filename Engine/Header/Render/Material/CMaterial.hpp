/// \file       CMaterial.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Material
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MATERIAL_HPP__
#define OOM_ENGINE_C_MATERIAL_HPP__

#include "Composite/IComponent.hpp"
#include "Render/Shader/SShaderManager.hpp"

using EShaderType = Oom::SShaderManager::EShaderType;

namespace Oom
{

class CMaterial : public IComponent
{

public:

    void                SetTexture      (GLuint texture);
    void                SetShader       (EShaderType shader_type);
    GLuint              GetShader       () const;
    GLuint              GetTexture      () const;
    EShaderType         GetShaderType   () const;
    const glm::vec3&    GetColor        () const;
    bool                HasProperty     (const char* p_name) const;

public:

    void SetInt         (const char* p_name, int data);
    void SetFloat       (const char* p_name, float data);
    void SetColor       (const char* p_name, const glm::vec3& color);
    void SetColor       (const char* p_name, const glm::vec4& color);
    void SetVector      (const char* p_name, const glm::vec2& vector);
    void SetVector      (const char* p_name, const glm::vec3& vector);
    void SetVector      (const char* p_name, const glm::vec4& vector);
    void SetMatrix      (const char* p_name, const glm::mat4& matrix4);

protected:

    void _Register() override;
    void _Destroy () override;

private:

    glm::vec3   m_color;
    GLuint      m_texture;
    GLuint      m_program;
    EShaderType m_shader_type;
};

}

#endif // !OOM_ENGINE_C_MATERIAL_HPP__