/// \file       CMeshRenderer.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CGameObject.hpp"
#include "Render/Mesh/CMeshRenderer.hpp"

namespace Oom
{

bool CMeshRenderer::IsVisible()
{ return m_is_visible; }

CMeshFilter* CMeshRenderer::GetAttachedMeshFilter()
{ return mp_game_object->GetComponent<CMeshFilter>(); }

CMaterial* CMeshRenderer::GetAttachedMaterial()
{ return mp_game_object->GetComponent<CMaterial>(); }

void CMeshRenderer::SetVisible(bool visible)
{ m_is_visible = visible; }

}