/// \file       CGizmosManager.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_MANAGER_HPP__
#define OOM_ENGINE_C_GIZMOS_MANAGER_HPP__

#include <vector>
#include <GLM/glm.hpp>
#include "Render/Config.hpp"
#include "Render/Gizmos/CDebugGrid.hpp"

namespace Oom
{

class CGizmosManager
{
public:

	enum EGizmo
	{
		Box,
		Ray,
		Line,
		Axis,
		Grid,
		Cone,

		Collider,
		Transform,
		PointLight,
		AudioSource,
		AudioListener,
		DirectionalLight,

		AllColliders,
		AllTransforms,
		AllPointLights,
		AllAudioSources,
		AllAudioListeners,
		AllDirectionalLights
    };

    struct SPair
    {
        EGizmo gizmo;
        bool   activated;
    };

    static void AddLine       (glm::vec3 const& start, glm::vec3 const& end, glm::vec3 const& color);
    static void EnableGizmo   (EGizmo type);
    static void DisableGizmo  (EGizmo type);
    static bool IsGizmoEnabled(EGizmo type);

private:

    friend class CRenderer;

    CGizmosManager ();
    ~CGizmosManager();

    static void Initialize();
    static void Shutdown  ();

    static void Clear();
    static void Draw (glm::mat4 const& PV);

    uint32_t   m_vertexCount;
    glm::vec3 m_vertices[5000];
    glm::vec3 m_colors  [5000];

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_cbo;
    GLint m_matrixID;
    GLuint m_shaderID;

    CDebugGrid                          m_grid;
    std::vector<SPair>                  m_array_map;

private:

    static CGizmosManager * s_pInstance;
};

}

#endif // !OOM_ENGINE_C_GIZMOS_MANAGER_HPP__