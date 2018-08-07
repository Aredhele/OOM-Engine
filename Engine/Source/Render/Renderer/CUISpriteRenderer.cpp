/// \file       CUISpriteRenderer.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Render/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"
#include "Render/CRenderer.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"
#include "Render/Renderer/CUISpriteRenderer.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

void CUISpriteRenderer::Draw(SRenderData& render_data)
{
	CMaterial*   p_material    = GetAttachedMaterial();
	CMeshFilter* p_mesh_filter = GetAttachedMeshFilter();

	if (!p_material || !p_mesh_filter)
	{
		SLogger::LogWaring("No material or no mesh filter to render the mesh.");
		return;
	}

	// Computing the MVP matrix
	render_data.M = mp_transform->GetLocalToWorldMatrix();
	render_data.P = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f);  // 16:9 aspect ratio

	// No view matrix since it's screen space
	render_data.MVP = render_data.P * render_data.M;
	
	p_material->Begin(render_data);

	glBindVertexArray(p_mesh_filter->GetMesh().GetVAO());
	glEnableVertexAttribArray(0); // Vertices
	glEnableVertexAttribArray(2); // UVs

	glDrawArrays(GL_TRIANGLES, 0, p_mesh_filter->GetMesh().GetVerticesCount());

	p_material->End();
}

void CUISpriteRenderer::SetSortingLayer(uint32_t sorting_layer)
{
	m_sorting_layer = sorting_layer;
}

uint32_t CUISpriteRenderer::GetSortingLayer() const
{
	return m_sorting_layer;
}

/* virtual */ void CUISpriteRenderer::_Register()
{
	SetVisible(true);
	m_sorting_layer = 0;
	
	CRenderer::RegisterUIRenderer(this);
}

/* virtual */ void CUISpriteRenderer::_Destroy()
{
	SetVisible(false);
	m_sorting_layer = 0;

	CRenderer::UnregisterUIRenderer(this);
}

}

