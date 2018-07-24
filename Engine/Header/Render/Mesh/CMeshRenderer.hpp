/// \file       CMeshRenderer.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MESH_RENDERER_HPP__
#define OOM_ENGINE_C_MESH_RENDERER_HPP__

#include "Composite/IComponent.hpp"

#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"

namespace Oom
{

class CMeshRenderer : public IComponent
{
public:

    bool         IsVisible              ();
    CMeshFilter* GetAttachedMeshFilter  ();
    CMaterial*   GetAttachedMaterial    ();

public:

    void         SetVisible             (bool visible);

protected:
    void _Register() override;

    void _Destroy() override;

private:

    bool m_is_visible;
};

}

#endif // !OOM_ENGINE_C_MESH_RENDERER_HPP__