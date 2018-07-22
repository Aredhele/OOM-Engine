/// \file       S_Camera.hpp
/// \date       22/07/2018 
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_CAMERA_HPP__
#define OOM_ENGINE_S_CAMERA_HPP__

#include <GLM/glm.hpp>
#include "Composite/Component/CBehavior.hpp"

class S_Camera : public Oom::CBehavior
{
public:

    // Behavior
    void Start()  override;
    void Update() override;

public:

    enum EProjectionMode
    {
        Perspective,
        Orthographic
    };

    const glm::vec3& GetClearColor        () const;
    EProjectionMode  GetProjectionMode    () const;
    float            GetFieldOfView       () const;
    float            GetClippingPlaneNear () const;
    float            GetClipplingPlaneFar () const;
    const glm::mat4& GetProjectionMatrix  () const;
    const glm::mat4& GetViewMatrix        ();
    void             SetClearColor        (const glm::vec3& color);
    void             SetProjectionMode    (EProjectionMode mode);
    void             SetFieldOfView       (float field_of_view);
    void             SetClippingPlaneNear (float near);
    void             SetClippingPlaneFar  (float far);

private:

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

private:

    glm::vec3       m_clear_color;
    EProjectionMode m_projection_mode;
    float           m_field_of_view;
    float           m_clipping_plane_near;
    float           m_clipping_plane_far;

    glm::mat4       m_view_matrix;
    glm::mat4       m_projection_matrix;
};

#endif // !OOM_ENGINE_S_CAMERA_HPP__