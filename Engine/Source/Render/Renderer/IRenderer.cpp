/// \file       IRenderer.cpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Render/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CGameObject.hpp"

#include "Render/CRenderer.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Renderer/IRenderer.hpp"
#include "Render/Material/CMaterial.hpp"

namespace Oom
{

bool IRenderer::IsVisible()
{
    return m_is_visible;
}

CMeshFilter* IRenderer::GetAttachedMeshFilter()
{
    return mp_game_object->GetComponent<CMeshFilter>();
}

CMaterial* IRenderer::GetAttachedMaterial()
{
    return mp_game_object->GetComponent<CMaterial>();
}

void IRenderer::SetVisible(bool visible)
{
    m_is_visible = visible;
}

/* virtual */ void IRenderer::_Register()
{
    CRenderer::RegisterRenderer(this);
    m_is_visible = true;
}

/* virtual */ void IRenderer::_Destroy()
{
    CRenderer::UnregisterRenderer(this);
    m_is_visible = false;
}

}