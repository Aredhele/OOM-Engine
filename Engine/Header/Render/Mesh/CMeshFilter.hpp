/// \file       CMeshFilter.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MESH_FILTER_HPP__
#define OOM_ENGINE_C_MESH_FILTER_HPP__

#include "Resource/CMesh.hpp"
#include "Composite/IComponent.hpp"

namespace Oom
{

class CMeshFilter : public IComponent
{
public:
          CMesh& GetMesh();
    const CMesh& GetMesh() const;

protected:
    void _Register() override;
    void _Destroy() override;

private:

    CMesh m_mesh;
};

}

#endif // !OOM_ENGINE_C_MESH_FILTER_HPP__