/// \file       CMeshFilter.cpp
/// \date       23/07/2018 
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#include "Render/Mesh/CMeshFilter.hpp"

namespace Oom
{

CMesh& MeshFilter::GetMesh()
{ return m_mesh; }

const CMesh& MeshFilter::GetMesh() const
{ return m_mesh; }

}

