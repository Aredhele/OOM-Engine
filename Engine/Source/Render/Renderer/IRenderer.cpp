/// \file       IRenderer.cpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Render/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CGameObject.hpp"
#include "Render/Renderer/IRenderer.hpp"

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
    m_is_visible = true;
}

}