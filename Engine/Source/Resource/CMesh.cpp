/// \file       CMesh.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Resource
/// \author     Vincent STEHLY--CALISTO

#include "Resource/CMesh.hpp"

namespace Oom
{

CMesh::CMesh()
{
    m_vao        = 0;
    m_vbo_uv     = 0;
    m_vbo_index  = 0;
    m_vbo_color  = 0;
    m_vbo_normal = 0;

    glGenVertexArrays(1, &m_vao);
}

CMesh::~CMesh()
{
    glBindVertexArray(m_vao);

    glDeleteBuffers(1, &m_vbo_uv);
    glDeleteBuffers(1, &m_vbo_color);
    glDeleteBuffers(1, &m_vbo_index);
    glDeleteBuffers(1, &m_vbo_normal);
    glDeleteBuffers(1, &m_vbo_vertex);
    glDeleteVertexArrays(1, &m_vao);

    glBindVertexArray(0);
}

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

GLuint CMesh::GetVAO() const
{ return m_vao; }

uint32_t CMesh::GetVerticesCount() const
{ return static_cast<uint32_t>(m_vertices.size()); }

void CMesh::SetVertices(const float* p_vertices, uint32_t count)
{
    m_vertices.clear();
    for(uint32_t i = 0; i < count; i += 3)
    {
        m_vertices.emplace_back(p_vertices[i + 0],
                                p_vertices[i + 1],
                                p_vertices[i + 2]);
    }

    UploadVertices();
}

void CMesh::SetVertices(const std::vector<glm::vec3>& vertices)
{
    m_vertices.clear();
    m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
    UploadVertices();
}

void CMesh::SetVertices(std::vector<glm::vec3>&& vertices)
{
    m_vertices.clear();
    m_vertices = static_cast<std::vector<glm::vec3>&&>(vertices);
    UploadVertices();
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
    UploadNormals();
}

void CMesh::SetNormals(const std::vector<glm::vec3>& normals)
{
    m_normals.clear();
    m_normals.insert(m_normals.end(), normals.begin(), normals.end());
    UploadNormals();
}

void CMesh::SetNormals(std::vector<glm::vec3>&& normals)
{
    m_normals.clear();
    m_normals = static_cast<std::vector<glm::vec3>&&>(normals);
    UploadNormals();
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
    UploadColors();
}

void CMesh::SetColors(const std::vector<glm::vec3>& colors)
{
    m_colors.clear();
    m_colors.insert(m_colors.end(), colors.begin(), colors.end());
    UploadColors();
}

void CMesh::SetColors(std::vector<glm::vec3>&& colors)
{
    m_colors.clear();
    m_colors = static_cast<std::vector<glm::vec3>&&>(colors);
    UploadColors();
}

void CMesh::SetUVs(const float* p_uvs, uint32_t count)
{
    m_uvs.clear();
    for(uint32_t i = 0; i < count; i += 2)
        m_uvs.emplace_back(p_uvs[i + 0], p_uvs[i + 1]);
    UploadUVs();
}

void CMesh::SetUVs(const std::vector<glm::vec2>& uvs)
{
    m_uvs.clear();
    m_uvs.insert(m_uvs.end(), uvs.begin(), uvs.end());
    UploadUVs();
}

void CMesh::SetUVs(std::vector<glm::vec2>&& uvs)
{
    m_uvs.clear();
    m_uvs = static_cast<std::vector<glm::vec2>&&>(uvs);
    UploadUVs();
}

void CMesh::SetIndices(const uint32_t* p_indices, uint32_t count)
{
    m_indices.clear();
    for(uint32_t i = 0; i < count; ++i)
        m_indices.push_back(p_indices[i]);
    UploadIndices();
}

void CMesh::SetIndices(const std::vector<uint32_t>& indices)
{
    m_indices.clear();
    m_indices.insert(m_indices.end(), indices.begin(), indices.end());
    UploadIndices();
}

void CMesh::SetIndices(std::vector<uint32_t>&& indices)
{
    m_indices.clear();
    m_indices = static_cast<std::vector<uint32_t>&&>(indices);
    UploadIndices();
}

void CMesh::ComputeBounds()
{
    // TODO
}

void CMesh::ComputeNormals()
{
    // TODO
}

void CMesh::UploadVertices()
{
    glBindVertexArray(m_vao);

    if(m_vbo_vertex != 0)
    {
        glDeleteBuffers(1, &m_vbo_vertex);
        m_vbo_vertex = 0;
    }

    glGenBuffers(1, &m_vbo_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertex);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glBindVertexArray(0);
}

void CMesh::UploadNormals()
{
   /* glBindVertexArray(m_vao);

    if(m_vbo_normal != 0)
    {
        glDeleteBuffers(1, &m_vbo_normal);
        m_vbo_normal = 0;
    }

    glGenBuffers(1, &m_vbo_normal);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glBindVertexArray(0);*/
}

void CMesh::UploadColors()
{
    glBindVertexArray(m_vao);

    if(m_vbo_color != 0)
    {
        glDeleteBuffers(1, &m_vbo_color);
        m_vbo_color = 0;
    }

    glGenBuffers(1, &m_vbo_color);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_color);
    glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(glm::vec3), &m_colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glBindVertexArray(0);
}

void CMesh::UploadUVs()
{
    glBindVertexArray(m_vao);

    if(m_vbo_uv != 0)
    {
        glDeleteBuffers(1, &m_vbo_uv);
        m_vbo_uv = 0;
    }

    glGenBuffers(1, &m_vbo_uv);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), m_uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glBindVertexArray(0);
}

void CMesh::UploadIndices()
{
    glBindVertexArray(m_vao);

    if(m_vbo_index != 0)
    {
        glDeleteBuffers(1, &m_vbo_index);
        m_vbo_index = 0;
    }

    glGenBuffers(1, &m_vbo_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

}