/// \file       S_Text.cpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO


#include "Resource/CMesh.hpp"
#include "Core/Debug/SLogger.hpp"
#include "Composite/CGameObject.hpp"
#include "Built-in/Script/S_Text.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"

/* virtual */ void S_Text::Start()
{
   // None
}

/* virtual */ void S_Text::Update()
{
    // None
}

void S_Text::SetText(const Oom::CString& text)
{
    m_text = text;
    UpdateText();
}

void S_Text::UpdateText()
{
    auto* p_game_object = GetGameObject();
    auto* p_mesh_filter = p_game_object->GetComponent<Oom::CMeshFilter>();

    if(!p_mesh_filter)
    {
        Oom::SLogger::LogError("No mesh filter attached to the text go.");
        return;
    }

    uint32_t length  = m_text.Size();
    Oom::CMesh& mesh = p_mesh_filter->GetMesh();

    // Fill buffers
    std::vector<glm::vec2> UVs;
    std::vector<glm::vec3> vertices;

    float charShift = 0.0f;
    for (size_t i = 0; i < length; i++)
    {
        glm::vec2 vertex_up_left    = glm::vec2(i,     1);
        glm::vec2 vertex_up_right   = glm::vec2(i + 1, 1);
        glm::vec2 vertex_down_right = glm::vec2(i + 1, 0);
        glm::vec2 vertex_down_left  = glm::vec2(i,     0);

        if(i != 0)
        {
            vertex_up_left.x    -= 0.5f * i + charShift;
            vertex_up_right.x   -= 0.5f * i + charShift;
            vertex_down_right.x -= 0.5f * i + charShift;
            vertex_down_left.x  -= 0.5f * i + charShift;
        }

        // if     (m_text[i] == 'i') charShift += (m_size / 5.0f);
        // else if(m_text[i] == '.') charShift += (m_size / 5.0f);
        // else if(m_text[i] == 'm') charShift -= (m_size / 8.0f);
        // else if(m_text[i] == 'r') charShift += (m_size / 8.0f);

        vertices.emplace_back(vertex_up_left.x,    vertex_up_left.y,    0.0f);
        vertices.emplace_back(vertex_down_left.x,  vertex_down_left.y,  0.0f);
        vertices.emplace_back(vertex_up_right.x,   vertex_up_right.y,   0.0f);

        vertices.emplace_back(vertex_down_right.x, vertex_down_right.y, 0.0f);
        vertices.emplace_back(vertex_up_right.x,   vertex_up_right.y,   0.0f);
        vertices.emplace_back(vertex_down_left.x,  vertex_down_left.y,  0.0f);

        char character = m_text[i];
        float uv_x = (character % 16) / 16.0f;
        float uv_y = (character / 16) / 16.0f;

        glm::vec2 uv_up_left    = glm::vec2(uv_x,                 uv_y);
        glm::vec2 uv_up_right   = glm::vec2(uv_x + 1.0f / 16.0f,  uv_y);
        glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
        glm::vec2 uv_down_left  = glm::vec2(uv_x ,               (uv_y + 1.0f / 16.0f));

        UVs.push_back(uv_up_left  );
        UVs.push_back(uv_down_left);
        UVs.push_back(uv_up_right );

        UVs.push_back(uv_down_right);
        UVs.push_back(uv_up_right  );
        UVs.push_back(uv_down_left );
    }

    mesh.SetUVs(std::move(UVs));
    mesh.SetVerticesNoOffset(std::move(vertices));
}
