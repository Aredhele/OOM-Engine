/// \file       S_CameraRotator.cpp
/// \date       04/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
#include "Game/S_CameraRotator.hpp"

/* virtual */ void S_CameraRotator::Start()
{
	GetTransform()->LookAt(0.0f, 0.0f, 0.0f);
	GetTransform()->SetLocalPosition(5.0f, 5.0f, 3.0f);
}

/* virtual */ void S_CameraRotator::Update()
{
	GetTransform()->LookAt(0.0f, 0.0f, 0.0f);
	GetTransform()->Translate(GetTransform()->GetRight() * -1.0f * 0.016f * 3.5f);
	
}