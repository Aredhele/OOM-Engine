/// \file       CMesh.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Mesh
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MESH_HPP__
#define OOM_ENGINE_C_MESH_HPP__

#include <vector>
#include <GLM/glm.hpp>
#include "Util/CBound.hpp"

namespace Oom
{

class CMesh
{
public:

    bool HasUVs     ()  const;
    bool HasColor   ()  const;
    bool HasNormals ()  const;
    bool HasVertices()  const;
    bool HasIndices ()  const;

public:

    void SetVertices    (const float* p_vertices, uint32_t count);
    void SetVertices    (const std::vector<glm::vec3>& vertices);
    void SetVertices    (std::vector<glm::vec3>&& vertices);
    void SetNormals     (const float* p_normals, uint32_t count);
    void SetNormals     (const std::vector<glm::vec3>& normals);
    void SetNormals     (std::vector<glm::vec3>&& normals);
    void SetColors      (const float* p_colors, uint32_t count);
    void SetColors      (const std::vector<glm::vec3>& colors);
    void SetColors      (std::vector<glm::vec3>&& colors);
    void SetUVs         (const float* p_uvs, uint32_t count);
    void SetUVs         (const std::vector<glm::vec2>& uvs);
    void SetUVs         (std::vector<glm::vec2>&& uvs);
    void SetIndices     (const uint32_t* p_indices, uint32_t count);
    void SetIndices     (const std::vector<uint32_t>& indices);
    void SetIndices      (std::vector<uint32_t>&& indices);

public:

    void ComputeBounds  ();
    void ComputeNormals ();

private:

    CBound mp_bounds;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec3> m_colors;
    std::vector<glm::vec2> m_uvs;
    std::vector<uint32_t>  m_indices;
};

}

#endif // !OOM_ENGINE_C_MESH_HPP__