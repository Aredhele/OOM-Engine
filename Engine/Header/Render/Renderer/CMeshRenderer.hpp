/// \file       CMeshRenderer.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MESH_RENDERER_HPP__
#define OOM_ENGINE_C_MESH_RENDERER_HPP__

#include "Render/Renderer/IRenderer.hpp"

namespace Oom
{

class CMeshRenderer : public IRenderer
{
public:
    void Draw(const glm::mat4 &projection_matrix,
              const glm::mat4 &view_matrix       ) override;
};

}

#endif // !OOM_ENGINE_C_MESH_RENDERER_HPP__