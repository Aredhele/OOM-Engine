/// \file       CTexRenderer.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"
#include "Render/Renderer/CTextRenderer.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

void CTextRenderer::Draw(SRenderData render_data)
{
    CMaterial*   p_material    = GetAttachedMaterial();
    CMeshFilter* p_mesh_filter = GetAttachedMeshFilter();

    if(!p_material || !p_mesh_filter)
    {
        SLogger::LogWaring("No material or no mesh filter to render the mesh.");
        return;
    }

	const glm::mat4 translation_matrix    = glm::translate(mp_transform->GetPosition() * glm::vec3(16.0f, 9.0f, 1.0f));
	const glm::mat4 rotation_matrix       = glm::orientate4(mp_transform->GetEulerAngles());
	const glm::mat4 scale_maxtrix         = glm::scale(mp_transform->GetScale());
	const glm::mat4 transformation_matrix = translation_matrix * rotation_matrix * scale_maxtrix;

	render_data.M = transformation_matrix;
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

}

