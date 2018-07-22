/// \file       S_CameraController.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_CAMERA_CONTROLLER_HPP__
#define OOM_ENGINE_S_CAMERA_CONTROLLER_HPP__

#include <GLM/glm.hpp>
#include "Composite/Component/CBehavior.hpp"

class S_CameraController : public Oom::CBehavior
{
public:

    // Behavior
    void Start()  override;
    void Update() override;

public:

    float GetSpeed              ()   const;
    float GetSensitivirt        ()   const;
    float GetRunSpeedMultiplier ()   const;

    void SetSpeed               (float speed);
    void SetSensitivity         (float sensitivity);
    void SetRunSpeedMultiplier  (float multiplier);

private:

    float              m_speed;
    float              m_sensitivity;
    float              m_run_speed_multiplier;
    glm::tvec3<double> m_last_mouse_position;
};

#endif // !OOM_ENGINE_S_CAMERA_CONTROLLER_HPP__