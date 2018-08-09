/// \file       CMaterial.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Material
/// \author     Vincent STEHLY--CALISTO

#include "Render/Material/CMaterial.hpp"
#include "Render/Shader/CShaderText.hpp"
#include "Render/Shader/CShaderUISprite.hpp"
#include "Render/Shader/CShaderStandard.hpp"
#include "Render/Shader/CShaderUnlitLine.hpp"
#include "Render/Shader/CShaderUnlitColor.hpp"
#include "Render/Shader/CShaderUnlitTexture.hpp"
#include "Render/Shader/CShaderUnlitTransparent.hpp"

namespace Oom
{

void CMaterial::SetShader(EShaderType shader_type)
{
    m_shader_type = shader_type;

    glm::vec3 old_color(1.0f);
    GLuint    old_texture = 0;

    if(mp_shader != nullptr)
    {
        old_color   = mp_shader->GetColor();
        old_texture = mp_shader->GetTexture();

        delete mp_shader;
        mp_shader = nullptr;
    }

    switch (shader_type)
    {
        case SShaderManager::Text:             mp_shader = new CShaderText();             break;
        case SShaderManager::Standard:         mp_shader = new CShaderStandard();         break;
		case SShaderManager::UISprite:         mp_shader = new CShaderUISprite();         break;
        case SShaderManager::UnlitLine:        mp_shader = new CShaderUnlitLine();        break;
        case SShaderManager::UnlitColor:       mp_shader = new CShaderUnlitColor();       break;
        case SShaderManager::UnlitTexture:     mp_shader = new CShaderUnlitTexture();     break;
        case SShaderManager::UnlitTransparent: mp_shader = new CShaderUnlitTransparent(); break;
    }

    mp_shader->SetColor(old_color);
    mp_shader->SetTexture(old_texture);
}

/* virtual */ void CMaterial::_Register()
{
    // None
}

/* virtual */ void CMaterial::_Destroy()
{
    if(mp_shader != nullptr)
    {
        delete mp_shader;
        mp_shader = nullptr;
    }
}

void CMaterial::BindShader()
{ mp_shader->BindShader(); }

void CMaterial::UnbindShader()
{ mp_shader->UnbindShader(); }

void CMaterial::SetTexture(GLuint texture)
{ mp_shader->SetTexture(texture); }

GLuint CMaterial::GetTexture() const
{ return mp_shader->GetTexture(); }

GLuint CMaterial::GetShader() const
{ return mp_shader->GetShader(); }

EShaderType CMaterial::GetShaderType() const
{ return m_shader_type; }

const glm::vec3& CMaterial::GetColor() const
{ return mp_shader->GetColor(); }

void CMaterial::SetColor(const glm::vec3 &color)
{ mp_shader->SetColor(color); }

void CMaterial::SetInt(const char* p_name, int data)
{ mp_shader->SetInt(p_name, data); }

void CMaterial::SetFloat(const char* p_name, float data)
{ mp_shader->SetFloat(p_name, data); }

void CMaterial::SetColor(const char* p_name, const glm::vec3& color)
{ mp_shader->SetColor(p_name, color); }

void CMaterial::SetColor(const char* p_name, const glm::vec4& color)
{ mp_shader->SetColor(p_name, color); }

void CMaterial::SetVector(const char* p_name, const glm::vec2& vector)
{ mp_shader->SetVector(p_name, vector); }

void CMaterial::SetVector(const char* p_name, const glm::vec3& vector)
{ mp_shader->SetVector(p_name, vector); }

void CMaterial::SetVector(const char* p_name, const glm::vec4& vector)
{ mp_shader->SetVector(p_name, vector); }

void CMaterial::SetMatrix(const char* p_name, const glm::mat4 &matrix4)
{ mp_shader->SetMatrix(p_name, matrix4); }

void CMaterial::Begin(const SRenderData &render_data)
{ if(mp_shader) mp_shader->Begin(render_data); }

void CMaterial::End()
{ if (mp_shader) mp_shader->End(); }

}