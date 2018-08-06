/// \file       CUISpriteRenderer.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Render/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"
#include "Render/Renderer/CUISpriteRenderer.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

void CUISpriteRenderer::Draw(SRenderData& render_data)
{
	// TODO
	CMaterial*   p_material    = GetAttachedMaterial();
	CMeshFilter* p_mesh_filter = GetAttachedMeshFilter();

	if (!p_material || !p_mesh_filter)
	{
		SLogger::LogWaring("No material or no mesh filter to render the mesh.");
		return;
	}

	// Computing the MVP matrix
	render_data.MVP = render_data.P * render_data.V * glm::mat4(1.0f);

	p_material->Begin(render_data);

	glBindVertexArray(p_mesh_filter->GetMesh().GetVAO());
	glEnableVertexAttribArray(0); // Vertices
	glEnableVertexAttribArray(2); // UVs

	glDrawArrays(GL_TRIANGLES, 0, p_mesh_filter->GetMesh().GetVerticesCount());

	p_material->End();
}

}

