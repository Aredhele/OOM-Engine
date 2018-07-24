/// \file       CMeshRenderer.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"
#include "Render/Renderer/CMeshRenderer.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

void Oom::CMeshRenderer::Draw(const glm::mat4& projection_matrix,
                              const glm::mat4& view_matrix)
{
    CMaterial*   p_material    = GetAttachedMaterial();
    CMeshFilter* p_mesh_filter = GetAttachedMeshFilter();

    if(!p_material || !p_mesh_filter)
    {
        SLogger::LogWaring("No material or no mesh filter to render the mesh.");
        return;
    }

    // Computing the MVP matrix
    glm::mat4 MVP = projection_matrix * view_matrix * mp_transform->GetLocalToWorldMatrix();

    glUseProgram(p_material->GetShader());
    p_material->SetMatrix("MVP", MVP);
    glUseProgram(p_material->GetShader());

    glBindVertexArray(p_mesh_filter->GetMesh().GetVAO());
    if(p_mesh_filter->GetMesh().HasVertices()) glEnableVertexAttribArray(0);
    if(p_mesh_filter->GetMesh().HasColor())    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, p_mesh_filter->GetMesh().GetVerticesCount());
    glDisableVertexAttribArray(0);
}

}