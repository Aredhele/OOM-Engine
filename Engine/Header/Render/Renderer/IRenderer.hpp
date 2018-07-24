/// \file       IRenderer.hpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_RENDERER_HPP__
#define OOM_ENGINE_I_RENDERER_HPP__

#include "Composite/IComponent.hpp"

namespace Oom
{

// Forward declaration
class CMaterial;
class CMeshFilter;

class IRenderer : public IComponent
{
public:

    bool         IsVisible              ();
    CMeshFilter* GetAttachedMeshFilter  ();
    CMaterial*   GetAttachedMaterial    ();

public:

    virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) = 0;

public:

    void         SetVisible             (bool visible);

private:

    bool m_is_visible;
};

}

#endif // !OOM_ENGINE_C_MESH_RENDERER_HPP__