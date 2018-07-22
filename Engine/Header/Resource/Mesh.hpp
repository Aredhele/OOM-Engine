/// \file       Mesh.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Mesh
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_MESH_HPP__
#define OOM_ENGINE_MESH_HPP__

#include <GLM/glm.hpp>

namespace Oom
{

class Mesh
{
public:

private:


    glm::vec3* p_vertices = nullptr;
    glm::vec3* p_normals  = nullptr;
    glm::vec3* p_colors   = nullptr;
    glm::vec2* p_uvs      = nullptr;
};

}

#endif // !OOM_ENGINE_MESH_HPP__