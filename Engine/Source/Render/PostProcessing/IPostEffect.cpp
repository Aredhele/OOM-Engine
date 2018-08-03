/// \file       IPostEffect.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#include "Render/PostProcessing/IPostEffect.hpp"

namespace Oom
{

IPostEffect::IPostEffect(EType type, const CString& name)
{
    m_type      = type;
    m_is_active = false;
    m_name      = name;
    m_shader_id = 0;

    m_color_texture_id = -1;
    m_depth_texture_id = -1;
}

const CString& IPostEffect::GetName() const
{
    return m_name;
}

void IPostEffect::SetActive(bool bActive)
{
    m_is_active = bActive;
}

bool IPostEffect::IsActive() const
{
    return m_is_active;
}

}