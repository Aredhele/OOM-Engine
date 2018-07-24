/// \file       CMeshFilter.cpp
/// \date       23/07/2018 
/// \project    OOM-Engine
/// \package    Render/Mesh
/// \author     Vincent STEHLY--CALISTO

#include "Render/Mesh/CMeshFilter.hpp"

namespace Oom
{

CMesh& CMeshFilter::GetMesh()
{ return m_mesh; }

const CMesh& CMeshFilter::GetMesh() const
{ return m_mesh; }

void CMeshFilter::_Register()
{ /* None */ }

void CMeshFilter::_Destroy()
{ /* None */ }

}

