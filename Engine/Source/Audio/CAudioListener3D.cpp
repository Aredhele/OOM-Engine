/// \file       CAudioListener3D.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO


#include "Audio/CAudioEngine.hpp"
#include "Audio/CAudioListener3D.hpp"

#include <GLM/glm.hpp>
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CTransform.hpp"


namespace Oom
{

void CAudioListener3D::OnEnable()
{

}

void CAudioListener3D::OnDisable()
{

}

void CAudioListener3D::OnDestroy()
{

}

void CAudioListener3D::_Register()
{
    const glm::vec3 position = GetGameObject()->GetTransform().GetLocalPosition();

	mp_listener = CAudioEngine::Allocate3DListener();
	mp_listener->SetPosition(position.x, position.y, position.z, DS3D_IMMEDIATE);
}

void CAudioListener3D::_Destroy()
{
	if(mp_listener)
	{
		mp_listener->Release();
		mp_listener = nullptr;
	}
}

}
