/// \file       CGizmosManager.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Render/Shader/SShaderManager.hpp"
#include "Render/Gizmos/CGizmosManager.hpp"

namespace Oom
{

/* static */ CGizmosManager * CGizmosManager::s_pInstance = nullptr;

CGizmosManager::CGizmosManager()
{
    m_vao         = 0;
    m_vbo         = 0;
    m_cbo         = 0;
    m_matrixID    = 0;
    m_shaderID    = 0;
    m_vertexCount = 0;

    // Getting color shader
    m_shaderID = SShaderManager::GetProgram(SShaderManager::EShaderType::UnlitColor);
    m_matrixID = glGetUniformLocation(m_shaderID, "MVP");

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers          (1, &m_vbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_vbo);
    glBufferData          (GL_ARRAY_BUFFER, 5000 * sizeof(glm::vec3), &m_vertices[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glGenBuffers          (1, &m_cbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_cbo);
    glBufferData          (GL_ARRAY_BUFFER, 5000 * sizeof(glm::vec3), &m_colors[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // Filling map
    m_array_map.push_back({EGizmo::Box,  false});
    m_array_map.push_back({EGizmo::Ray,  false});
    m_array_map.push_back({EGizmo::Line, false});
    m_array_map.push_back({EGizmo::Axis, false});
    m_array_map.push_back({EGizmo::Grid, false});
    m_array_map.push_back({EGizmo::Cone, false});
	m_array_map.push_back({EGizmo::Collider,         false});
    m_array_map.push_back({EGizmo::Transform,        false});
    m_array_map.push_back({EGizmo::PointLight,       false});
	m_array_map.push_back({EGizmo::AudioSource,      false});
    m_array_map.push_back({EGizmo::DirectionalLight, false});

    // Initializes the grid
    m_grid.Initialize(50, 1.0f, glm::vec3(0.4f, 0.4f, 0.4f));
}

CGizmosManager::~CGizmosManager() // NOLINT
{
    // TODO
}

/* static */ void CGizmosManager::AddLine(const glm::vec3 &start,
                                          const glm::vec3 &end,
                                          const glm::vec3 &color)
{
    if(s_pInstance->m_vertexCount + 2 >= 5000)
    {
        // Too many debug lines, ignoring current line
        return;
    }

    s_pInstance->m_vertices[s_pInstance->m_vertexCount + 0] = start;
    s_pInstance->m_vertices[s_pInstance->m_vertexCount + 1] = end;
    s_pInstance->m_colors  [s_pInstance->m_vertexCount + 0] = color;
    s_pInstance->m_colors  [s_pInstance->m_vertexCount + 1] = color;

    s_pInstance->m_vertexCount += 2;
}

/* static */ void CGizmosManager::Initialize()
{
    if(CGizmosManager::s_pInstance == nullptr)
    {
        CGizmosManager::s_pInstance = new CGizmosManager();
        SLogger::LogInfo("Debug manager successfully initialized.");
    }
    else
    {
        SLogger::LogWaring("The debug manager is already initialized.");
    }
}

/* static */ void CGizmosManager::Shutdown()
{
    if(CGizmosManager::s_pInstance != nullptr)
    {
        delete CGizmosManager::s_pInstance;
        CGizmosManager::s_pInstance = nullptr;

        SLogger::LogInfo("Debug manager successfully destroyed.");
    }
    else
    {
        SLogger::LogWaring("The debug manager is already destroyed.");
    }
}

/* static */ void CGizmosManager::Clear()
{
    CGizmosManager::s_pInstance->m_vertexCount = 0;
}

/// \brief Updates buffers and setup the shader
/* static */ void CGizmosManager::Draw(glm::mat4 const& PV)
{
    if(CGizmosManager::IsGizmoEnabled(EGizmo::Axis))
    {
        AddLine(glm::vec3(0.0f, 0.0f, 0.01f), glm::vec3(1000.0f, 0.0f,    0.01f), glm::vec3(1.0f, 0.0f, 0.0f));
        AddLine(glm::vec3(0.0f, 0.0f, 0.01f), glm::vec3(0.0f, 1000.0f,    0.01f), glm::vec3(0.0f, 1.0f, 0.0f));
        AddLine(glm::vec3(0.0f, 0.0f, 0.01f), glm::vec3(0.0f,   0.0f,   1000.0f),  glm::vec3(0.0f, 0.0f, 1.0f));
    }

	if (CGizmosManager::IsGizmoEnabled(EGizmo::Grid))
	{
		s_pInstance->m_grid.Draw(PV);
	}

    if(s_pInstance->m_vertexCount == 0)
    {
        // There's nothing to draw
        return;
    }

    // Computes MVP matrix
    glm::mat4 MVP = PV * glm::mat4(1.0f);

    glBindBuffer   (GL_ARRAY_BUFFER, s_pInstance->m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_pInstance->m_vertexCount * sizeof(glm::vec3), s_pInstance->m_vertices);

    glBindBuffer   (GL_ARRAY_BUFFER, s_pInstance->m_cbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_pInstance->m_vertexCount * sizeof(glm::vec3), s_pInstance->m_colors);

    // Sets up shader
    glUseProgram      (s_pInstance->m_shaderID);
    glUniformMatrix4fv(s_pInstance->m_matrixID, 1, GL_FALSE, &MVP[0][0]);

    // Draws all lines
    glBindVertexArray(CGizmosManager::s_pInstance->m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, s_pInstance->m_vertexCount);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

/* static */ void CGizmosManager::EnableGizmo(EGizmo type)
{
    for(auto& pair : s_pInstance->m_array_map)
        if(pair.gizmo == type)
            pair.activated = true;
}

/* static */void CGizmosManager::DisableGizmo(EGizmo type)
{
    for(auto& pair : s_pInstance->m_array_map)
        if(pair.gizmo == type)
            pair.activated = false;
}

/* static */ bool CGizmosManager::IsGizmoEnabled(EGizmo type)
{
    for(auto& pair : s_pInstance->m_array_map)
        if(pair.gizmo == type)
            return pair.activated;

    return false;
}

} // !namespace