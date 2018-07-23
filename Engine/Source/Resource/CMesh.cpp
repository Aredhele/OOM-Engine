/// \file       CMesh.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Resource
/// \author     Vincent STEHLY--CALISTO

#include "Resource/CMesh.hpp"

namespace Oom
{

bool CMesh::HasUVs() const
{ return !m_uvs.empty();      }

bool CMesh::HasColor() const
{ return !m_colors.empty();   }

bool CMesh::HasNormals() const
{ return !m_normals.empty();  }

bool CMesh::HasVertices() const
{ return !m_vertices.empty(); }

bool CMesh::HasIndices() const
{ return !m_indices.empty();  }

void CMesh::SetVertices(const float* p_vertices, uint32_t count)
{
    m_vertices.clear();
    for(uint32_t i = 0; i < count; i += 3)
    {
        m_vertices.emplace_back(p_vertices[i + 0],
                                p_vertices[i + 1],
                                p_vertices[i + 2]);
    }
}

void CMesh::SetVertices(const std::vector<glm::vec3>& vertices)
{
    m_vertices.clear();
    m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
}

void CMesh::SetVertices(std::vector<glm::vec3>&& vertices)
{
    m_vertices.clear();
    m_vertices = static_cast<std::vector<glm::vec3>&&>(vertices);
}

void CMesh::SetNormals(const float* p_normals, uint32_t count)
{
    m_normals.clear();
    for(uint32_t i = 0; i < count; i += 3)
    {
        m_normals.emplace_back(p_normals[i + 0],
                               p_normals[i + 1],
                               p_normals[i + 2]);
    }
}

void CMesh::SetNormals(const std::vector<glm::vec3>& normals)
{
    m_normals.clear();
    m_normals.insert(m_normals.end(), normals.begin(), normals.end());
}

void CMesh::SetNormals(std::vector<glm::vec3>&& normals)
{
    m_normals.clear();
    m_normals = static_cast<std::vector<glm::vec3>&&>(normals);
}

void CMesh::SetColors(const float* p_colors, uint32_t count)
{
    m_colors.clear();
    for(uint32_t i = 0; i < count; i += 3)
    {
        m_colors.emplace_back(p_colors[i + 0],
                              p_colors[i + 1],
                              p_colors[i + 2]);
    }
}

void CMesh::SetColors(const std::vector<glm::vec3>& colors)
{
    m_colors.clear();
    m_colors.insert(m_colors.end(), colors.begin(), colors.end());
}

void CMesh::SetColors(std::vector<glm::vec3>&& colors)
{
    m_colors.clear();
    m_colors = static_cast<std::vector<glm::vec3>&&>(colors);
}

void CMesh::SetUVs(const float* p_uvs, uint32_t count)
{
    m_uvs.clear();
    for(uint32_t i = 0; i < count; i += 2)
        m_uvs.emplace_back(p_uvs[i + 0], p_uvs[i + 1]);
}

void CMesh::SetUVs(const std::vector<glm::vec2>& uvs)
{
    m_uvs.clear();
    m_uvs.insert(m_uvs.end(), uvs.begin(), uvs.end());
}

void CMesh::SetUVs(std::vector<glm::vec2>&& uvs)
{
    m_uvs.clear();
    m_uvs = static_cast<std::vector<glm::vec2>&&>(uvs);
}

void CMesh::SetIndices(const uint32_t* p_indices, uint32_t count)
{
    m_indices.clear();
    for(uint32_t i = 0; i < count; ++i)
        m_indices.push_back(p_indices[i]);
}

void CMesh::SetIndices(const std::vector<uint32_t>& indices)
{
    m_indices.clear();
    m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

void CMesh::SetIndices(std::vector<uint32_t>&& indices)
{
    m_indices.clear();
    m_indices = static_cast<std::vector<uint32_t>&&>(indices);
}

void CMesh::ComputeBounds()
{
    // TODO
}

void CMesh::ComputeNormals()
{
    // TODO
}

}