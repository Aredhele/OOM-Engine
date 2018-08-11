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
	void Awake() override;
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

	// TMP
	void				LookAt      (float x, float y, float z);
	void				LookAt      (const glm::vec3& target);
	void                Rotate      (float x, float y, float z);
	void                Rotate      (const glm::vec3& point);
	void                RotateAround(const glm::vec3& point, const glm::vec3& axis, float angle);
	void                Translate   (float x, float y, float z);
	void                Translate   (const glm::vec3& translation);
	const glm::vec3&    GetUp() const;
	const glm::vec3&    GetRight() const;
	const glm::vec3&    GetForward() const;
	const glm::vec3&    GetPosition() const;
	const glm::vec3&    GetScale() const;
	const glm::vec3&    GetOrientation() const;

private:

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

	// Update vector
	void UpdateVector();

private:

    glm::vec3       m_clear_color;
    EProjectionMode m_projection_mode;
    float           m_field_of_view;
    float           m_clipping_plane_near;
    float           m_clipping_plane_far;

    glm::mat4       m_view_matrix;
    glm::mat4       m_projection_matrix;

	// TMP
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_orientation;
	glm::vec3 m_test;

	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_forward;
};

#endif // !OOM_ENGINE_S_CAMERA_HPP__