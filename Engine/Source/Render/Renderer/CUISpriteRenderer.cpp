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

	GLfloat aspectRatio = 1600 / 900;

	// Computing the MVP matrix
	render_data.M   = mp_transform->GetLocalToWorldMatrix();
	render_data.P   = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f); // Works but not
	render_data.P   = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
	render_data.P   = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f);

	render_data.MVP = render_data.P * render_data.V * render_data.M;
	
	p_material->Begin(render_data);

	glBindVertexArray(p_mesh_filter->GetMesh().GetVAO());
	glEnableVertexAttribArray(0); // Vertices
	glEnableVertexAttribArray(2); // UVs

	glDrawArrays(GL_TRIANGLES, 0, p_mesh_filter->GetMesh().GetVerticesCount());

	p_material->End();
}

}

