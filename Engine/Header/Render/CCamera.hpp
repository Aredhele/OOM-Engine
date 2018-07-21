/// \file       Camera.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_CAMERA_HPP__
#define OOM_ENGINE_CAMERA_HPP__

#include <GLM/glm.hpp>
#include "Render/Config.hpp"

namespace Oom
{

class CCamera
{
public:

    explicit         CCamera            ();
    void             LookAt             (const glm::vec3& target);
    void             Translate          (const glm::vec3& translation);
    void             Rotate             (float angle);
    void             RotateUp           (float angle);
    void             RotateAround       (float angle);
    void             RotateUpAround     (float angle);
    void             SetPosition        (const glm::vec3& position);
    void             SetDirection       (const glm::vec3& direction);

    const glm::vec3& GetPosition        () const;
    const glm::vec3& GetDirection       () const;
    const glm::vec3& GetRight           () const;
    const glm::vec3& GetUp              () const;
    const glm::mat4& GetViewMatrix      () const;
    const glm::mat4& GetProjectionMatrix() const;

private:

    void             UpdateVectors      ();

private:

    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_look_at;

    glm::vec3 m_position;
    glm::vec3 m_direction;

    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
};

}

#endif // !OOM_ENGINE_CAMERA_HPP__