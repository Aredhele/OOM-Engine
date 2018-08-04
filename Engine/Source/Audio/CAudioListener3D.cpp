/// \file       CAudioListener3D.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include "Core/Debug/SLogger.hpp"
#include "Audio/CAudioEngine.hpp"
#include "Audio/CAudioListener3D.hpp"

#include <GLM/glm.hpp>
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

void CAudioListener3D::OnEnable()
{
	// TODO
}

void CAudioListener3D::OnDisable()
{
	// TODO
}

void CAudioListener3D::OnDestroy()
{
	// TODO
}

void CAudioListener3D::_Register()
{
	// Obtain a listener interface.
	HRESULT result = CAudioEngine::GetPrimaryBuffer()->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&mp_listener);

	if (FAILED(result))
	{
		SLogger::LogError("Failed to create the listener");
		return;
	}

    const glm::vec3 position = GetGameObject()->GetTransform().GetLocalPosition();
	mp_listener->SetPosition(position.x, position.y, position.z, DS3D_IMMEDIATE);

	CAudioEngine::RegisterCAudioListener3D(this);
}

void CAudioListener3D::_Destroy()
{
	if(mp_listener)
	{
		mp_listener->Release();
		mp_listener = nullptr;
	}

	CAudioEngine::UnregisterCAudioListener3D(this);
}

}
