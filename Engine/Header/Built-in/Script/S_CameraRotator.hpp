/// \file       S_CameraRotator.hpp
/// \date       04/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_CAMERA_ROTATOR_HPP__
#define OOM_ENGINE_S_CAMERA_ROTATOR_HPP__

#include "Composite/Component/CBehavior.hpp"

class S_CameraRotator : public Oom::CBehavior
{
public:

	// Behavior
	void Start () override;
	void Update() override;
};

#endif // !OOM_ENGINE_S_CAMERA_ROTATOR_HPP__