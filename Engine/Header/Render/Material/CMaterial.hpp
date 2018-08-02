/// \file       CMaterial.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Material
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MATERIAL_HPP__
#define OOM_ENGINE_C_MATERIAL_HPP__

#include "Composite/IComponent.hpp"
#include "Render/Shader/IShader.hpp"
#include "Render/Shader/SShaderManager.hpp"

using EShaderType = Oom::SShaderManager::EShaderType;

namespace Oom
{

/// \brief This is only a proxy for the shader class
class CMaterial : public IComponent
{
public:

    void                BindShader      ();
    void                UnbindShader    ();
    void                SetTexture      (GLuint texture);
    void                SetShader       (EShaderType shader_type);
    GLuint              GetShader       () const;
    GLuint              GetTexture      () const;
    EShaderType         GetShaderType   () const;
    const glm::vec3&    GetColor        () const;

public:

    void SetColor       (const glm::vec3& color);
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

    friend class CMeshRenderer;
    friend class CTextRenderer;

    void Begin(const SRenderData& render_data);
    void End  ();

private:

    IShader*    mp_shader = nullptr;
    EShaderType m_shader_type;
};

}

#endif // !OOM_ENGINE_C_MATERIAL_HPP__